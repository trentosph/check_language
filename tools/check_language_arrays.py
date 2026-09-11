#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Checker per le tabelle messaggi MES_LARHEA_GB.c / MES_LARHEA_ML.c.

Verifica:
1. Dimensionamento rispetto a LANG_DEF.h
   - numero di elementi (righe) dell'array
   - lunghezza in byte di ogni stringa/elemento rispetto alla larghezza dichiarata
2. Allineamento strutturale tra GB e ML
   - stesse tabelle, stesse dimensioni, stesse macro condizionali (#ifdef)
3. Placeholder (escape slot 0..15) a parità di indice reale nell'array
   - stesso numero e stessi slot (\\0..\\7, \\x08..\\x0F) tra GB e ML
   - stessi raggruppamenti in parametri (run consecutive separate da testo/§/…)
4. Placeholder duplicati nello stesso messaggio
   - lo stesso slot non può comparire più di una volta (anche non consecutivi:
     es. \\5\\5\\6\\7 e \\5\\6\\7\\5 sono entrambi errori)
5. ID messaggio ML (solo MES_LARHEA_ML.c; il codice commentato è già ignorato)
   - primi 5 caratteri: '@' + lettera A-Z (tabella) + 3 cifre (indice, es. 001)
   - ID unico su tutto il file (anche tra rami #ifdef diversi)
   - elementi fatti solo di macro (es. NOME_MACCHINA_1) esclusi dal controllo
   - eccezione: messaggio fisso "language:" / "Multilanguage" (senza @Xnnn)
6. Commento indice vs indice reale nell'array (GB e ML)
   - es. /* MSP n. 96 */ deve coincidere con la posizione reale nell'array (96)
   - indipendente dall'ID catalogo @Xnnn (es. @B124 su MSP n. 96 è ok)

Uso:
  python tools/check_language_arrays.py
  python tools/check_language_arrays.py --warnings-as-errors

Exit code 0 = OK, 1 = errori (o warning se --warnings-as-errors).
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional


# ---------------------------------------------------------------------------
# Metadati attesi (da commenti LANG_DEF.h / convenzione firmware)
# ---------------------------------------------------------------------------

# Larghezza colonna attesa per tabella 2D (None = dipende da #ifdef, es. EASY_PRESEL)
EXPECTED_WIDTHS: dict[str, Optional[int]] = {
    "MSA_1": 32,
    "MSAP_1": 32,
    "MS_NOME_SELEZ_1": 16,
    "MS_NOME_PRESEL_1": None,  # 16 con EASY_PRESEL, altrimenti 7
    "MS_PROG_NOME_PRESEL": 8,
    "MS_TIPO_SCHIUMA": 16,
    "MS_TIPO_FLUSSO_1": 8,
    "MS_NOME_GIORNO_1": 5,
    "MSG_LAV_GRUPPO": 32,
    "MES_ERRORI_AGGIUNTI": 32,
    "MSAP_ParGrEspresso": 32,
    "MSAP_PAR_MACINA_MOT": 32,
    "MS_TIPO_GRANULOMETRIA": 16,
    "MSAP_PAR_MAINTENANCE": 32,
    "MSAP_CAPPUCCINATORE": 32,
    "MS_TIPO_PALETTA": 16,
    "MS_MODULI_EST": 32,
}

# Macro di conteggio attesa (se si usa un letterale, deve coincidere col valore della macro)
EXPECTED_COUNT_MACROS: dict[str, str] = {
    "MSA_1": "MAX_MSA",
    "MSAP_1": "MAX_MSAP",
    "MS_NOME_SELEZ_1": "MAX_NOME_SELEZ",
    "MS_NOME_PRESEL_1": "MAX_NOME_PRESEL",
    "MS_PROG_NOME_PRESEL": "MAX_PROG_NOME_PRESEL",
    "MS_TIPO_SCHIUMA": "MAX_TIPO_SCHIUMA",
    "MS_TIPO_FLUSSO_1": "MAX_TIPO_FLUSSO",
    "MS_NOME_GIORNO_1": "MAX_NOME_GIORNO",
    "MSG_LAV_GRUPPO": "MAX_LAV_GRUPPO",
    "MES_ERRORI_AGGIUNTI": "MAX_MES_ERRORI_AGGIUNTI",
    "MSAP_ParGrEspresso": "MAX_ParGrEspresso",
    "MSAP_PAR_MACINA_MOT": "MAX_PAR_MACINA_MOT",
    "MS_TIPO_GRANULOMETRIA": "MAX_TIPO_GRANULOMETRIA",
    "MSAP_PAR_MAINTENANCE": "MAX_PAR_MAINTENANCE",
    "MSAP_CAPPUCCINATORE": "MAX_CAPPUCCINATORE",
    "MS_TIPO_PALETTA": "MAX_TIPO_PALETTA",
    "MS_MODULI_EST": "MAX_MSG_SLAVE",
}

# Array 1D: [WIDTH] = una sola stringa di WIDTH byte (non WIDTH elementi)
ONE_D_TABLES = {
    "MS_PROG_ESTESA",
    "MS_PROG_RIDOTTA",
    "MS_SI_1",
    "MS_NO_1",
}


@dataclass
class Issue:
    severity: str  # error | warning
    file: str
    line: int
    message: str

    def format(self) -> str:
        loc = f"{self.file}:{self.line}" if self.line else self.file
        return f"[{self.severity.upper()}] {loc}: {self.message}"


@dataclass
class MessageElement:
    """
    Un elemento dell'array messaggi (stringhe C concatenate fino alla virgola).

    logical_index è l'indice reale nell'array C: i rami #if/#else alternativi
    condividono gli stessi indici. I commenti /* MSA n. N */ non lo calcolano:
    vengono solo confrontati con logical_index (check coerenza commento).
    """

    logical_index: int
    line: int
    # Slot placeholder in ordine di apparizione (valori 0..15)
    placeholders: tuple[int, ...]
    # Parametri = run consecutive di slot, separate da testo/§/:/spazi/…
    # es. "ciao \1\2 \3\4" -> ((1,2), (3,4))
    param_groups: tuple[tuple[int, ...], ...]
    preview: str
    # Percorso del ramo preprocessore (per messaggi di errore più chiari)
    branch_path: str = ""
    # True se l'elemento è solo macro (NOME_MACCHINA_1, …): niente ID @Xnnn da controllare
    is_macro_only: bool = False
    # Primi 5 byte del messaggio (None se macro-only o stringa troppo corta)
    msg_id_prefix: Optional[str] = None
    # Numero letto dal commento indice sulla stessa riga (/* MSP n. 96 */, /* 09 */, …)
    # None se assente o riga commentata con //
    comment_index: Optional[int] = None

@dataclass
class ArrayDecl:
    """Dichiarazione di un array messaggi nel .c."""

    name: str
    base_name: str
    prefix: str  # GB | ML
    rows_expr: str
    cols_expr: Optional[str]  # None se 1D
    line: int
    outer_guards: list[str] = field(default_factory=list)
    body: str = ""
    body_start_line: int = 0
    # Compilati durante l'analisi
    row_count: int = 0
    ifdef_sig: list[str] = field(default_factory=list)
    # Elementi in ordine di visita nel corpo (tutti i rami #ifdef)
    elements: list[MessageElement] = field(default_factory=list)


# ---------------------------------------------------------------------------
# LANG_DEF.h
# ---------------------------------------------------------------------------

RE_DEFINE = re.compile(r"^\s*#\s*define\s+(MAX_\w+)\s+(\d+)", re.MULTILINE)


def parse_lang_def(path: Path) -> dict[str, list[int]]:
    """Estrae MAX_* (anche le alternative sotto #ifdef, es. MAX_CAPPUCCINATORE)."""
    text = path.read_text(encoding="utf-8", errors="replace")
    values: dict[str, list[int]] = {}
    for m in RE_DEFINE.finditer(text):
        name, num = m.group(1), int(m.group(2))
        values.setdefault(name, [])
        if num not in values[name]:
            values[name].append(num)
    return values


def resolve_dim(expr: str, macros: dict[str, list[int]]) -> list[int]:
    expr = expr.strip()
    if expr.isdigit():
        return [int(expr)]
    return list(macros.get(expr, []))


# ---------------------------------------------------------------------------
# Lunghezza letterale C
# ---------------------------------------------------------------------------

RE_C_STRING = re.compile(r'"(?:\\.|[^"\\])*"')
RE_HEX_ESC = re.compile(r"\\x[0-9A-Fa-f]{1,2}")
RE_OCT_ESC = re.compile(r"\\[0-7]{1,3}")


def _decode_c_string_bytes(literal: str, limit: Optional[int] = None) -> bytes:
    """
    Decodifica il contenuto di un letterale C \"...\" in byte u8.

    Stessa logica di lunghezza (ogni escape = 1 byte). Se limit è impostato,
    si ferma dopo quel numero di byte (utile per leggere solo i primi 5 dell'ID).
    """
    inner = literal[1:-1]
    out = bytearray()
    i = 0
    while i < len(inner):
        if limit is not None and len(out) >= limit:
            break
        if inner[i] != "\\":
            # Carattere letterale: un byte (Latin-1 / firmware u8)
            out.append(ord(inner[i]) & 0xFF)
            i += 1
            continue
        m = RE_HEX_ESC.match(inner, i)
        if m:
            out.append(int(m.group(0)[2:], 16) & 0xFF)
            i = m.end()
            continue
        m = RE_OCT_ESC.match(inner, i)
        if m:
            out.append(int(m.group(0)[1:], 8) & 0xFF)
            i = m.end()
            continue
        # Escape semplice: \n, \t, \\, … → un byte
        if i + 1 < len(inner):
            esc = inner[i + 1]
            simple = {"n": 10, "r": 13, "t": 9, "0": 0}.get(esc)
            out.append(simple if simple is not None else (ord(esc) & 0xFF))
            i += 2
        else:
            out.append(ord("\\") & 0xFF)
            i += 1
    return bytes(out)


def c_string_byte_len(literal: str) -> int:
    """Lunghezza in byte del contenuto di \"...\" (ogni escape = 1 byte u8)."""
    return len(_decode_c_string_bytes(literal))


def extract_msg_id_prefix(literals: list[str]) -> Optional[str]:
    """
    Estrae i primi 5 byte del messaggio dal primo letterale C.

    Contesto ML: l'ID catalogo sta sempre all'inizio della prima stringa
    (es. \"@A001§\\1...\"). Restituisce None se non ci sono stringhe
    (elemento solo-macro da saltare).
    """
    if not literals:
        return None
    raw = _decode_c_string_bytes(literals[0], limit=5)
    # Latin-1: ogni byte → un carattere, così il report resta leggibile
    return raw.decode("latin-1")


# Slot placeholder firmware: byte 0..15 scritti come escape ottale/hex
# (es. \1\2, \x08\x0A). Non conta \n/\t/% letterale.
PLACEHOLDER_MAX = 15


def extract_placeholder_slots(literal: str) -> list[int]:
    """
    Estrae gli slot placeholder (0..15) da un letterale C \"...\".

    Conta solo escape ottali/hex che producono un byte 0..15
    (\\0..\\7, \\10..\\17, \\x00..\\x0F). Gli altri escape (\\n, \\\\, …)
    non sono slot di inserimento firmware.
    """
    groups = extract_placeholder_groups([literal])
    return [s for g in groups for s in g]


def extract_placeholder_groups(
    literals: list[str],
) -> tuple[tuple[int, ...], ...]:
    """
    Estrae i parametri = run consecutive di slot placeholder.

    Un parametro è una sequenza ininterrotta di escape 0..15; qualsiasi altro
    contenuto (spazio, testo, '§', ':', escape non-slot, …) spezza il gruppo.

    Esempi:
      "ciao \\1\\2 \\3\\4"     -> ((1,2), (3,4))   lunghezze 2+2
      "@A123§\\1§\\2\\3\\4"   -> ((1,), (2,3,4))  lunghezze 1+3
      "ora \\5\\6:\\7\\x08"   -> ((5,6), (7,8))
    """
    groups: list[tuple[int, ...]] = []
    current: list[int] = []

    def flush() -> None:
        nonlocal current
        if current:
            groups.append(tuple(current))
            current = []

    for lit in literals:
        # lit è un letterale C completo "..."
        inner = lit[1:-1]
        i = 0
        while i < len(inner):
            if inner[i] == "\\":
                m = RE_HEX_ESC.match(inner, i)
                if m:
                    val = int(m.group(0)[2:], 16)
                    if 0 <= val <= PLACEHOLDER_MAX:
                        current.append(val)
                    else:
                        # Escape hex fuori range slot: spezza il parametro
                        flush()
                    i = m.end()
                    continue
                m = RE_OCT_ESC.match(inner, i)
                if m:
                    val = int(m.group(0)[1:], 8)
                    if 0 <= val <= PLACEHOLDER_MAX:
                        current.append(val)
                    else:
                        flush()
                    i = m.end()
                    continue
                # Escape non-slot (\n, \\, …): spezza il parametro
                flush()
                i += 2 if i + 1 < len(inner) else 1
                continue
            # Carattere normale (spazio, §, testo, …): spezza il parametro
            flush()
            i += 1
    flush()
    return tuple(groups)


def format_placeholders(slots: tuple[int, ...] | list[int]) -> str:
    """Rappresentazione leggibile degli slot: \\0,\\1,\\x08,…"""
    if not slots:
        return "(nessuno)"
    parts: list[str] = []
    for s in slots:
        if s <= 7:
            parts.append(f"\\{s}")
        else:
            parts.append(f"\\x{s:02X}")
    return ",".join(parts)


def format_param_groups(
    groups: tuple[tuple[int, ...], ...] | list[tuple[int, ...]],
) -> str:
    """
    Rappresentazione leggibile dei parametri con lunghezze.
    es. [2]=\\1\\2 + [2]=\\3\\4
    """
    if not groups:
        return "(nessun parametro)"
    parts: list[str] = []
    for g in groups:
        # Senza virgole tra slot dello stesso parametro: riflette i caratteri contigui
        body = "".join(
            f"\\{s}" if s <= 7 else f"\\x{s:02X}" for s in g
        )
        parts.append(f"[{len(g)}]={body}")
    return " + ".join(parts)


# ---------------------------------------------------------------------------
# Estrazione dichiarazioni
# ---------------------------------------------------------------------------

RE_ARRAY_DECL = re.compile(
    r"const\s+u8\s+__far\s+(GB_|ML_)(\w+)\s*"
    r"\[([^\]]+)\]"
    r"(?:\s*\[([^\]]+)\])?\s*=\s*"
    r"(?:(?://[^\n]*\n|/\*.*?\*/|\s)*)"  # commenti/spazi tra = e {
    r"\{",
    re.MULTILINE | re.DOTALL,
)


def _skip_c_string(text: str, i: int) -> int:
    """Avanza l'indice oltre un letterale C che inizia a text[i] == '\"'."""
    i += 1
    while i < len(text):
        if text[i] == "\\":
            i += 2
            continue
        if text[i] == '"':
            return i + 1
        i += 1
    return i


def _skip_c_comment(text: str, i: int) -> int:
    """Avanza oltre //... o /* ... */ che inizia a text[i] == '/'."""
    if i + 1 >= len(text):
        return i + 1
    if text[i + 1] == "/":
        # Commento fino a fine riga
        nl = text.find("\n", i)
        return len(text) if nl < 0 else nl
    if text[i + 1] == "*":
        end = text.find("*/", i + 2)
        return len(text) if end < 0 else end + 2
    return i + 1


def _find_matching_brace(text: str, body_start: int) -> int:
    """
    Trova la posizione subito dopo la '}' che chiude il '{' già consumato.
    Ignora graffe dentro stringhe e commenti (fondamentale in questi .c).
    """
    depth = 1
    i = body_start
    while i < len(text) and depth > 0:
        ch = text[i]
        if ch == '"':
            i = _skip_c_string(text, i)
            continue
        if ch == "/" and i + 1 < len(text) and text[i + 1] in "/*":
            i = _skip_c_comment(text, i)
            continue
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth -= 1
        i += 1
    return i


def extract_arrays(path: Path) -> list[ArrayDecl]:
    raw = path.read_text(encoding="utf-8", errors="replace")
    arrays: list[ArrayDecl] = []

    for m in RE_ARRAY_DECL.finditer(raw):
        prefix = m.group(1).rstrip("_")
        base = m.group(2)
        rows_expr = m.group(3).strip()
        cols_expr = m.group(4).strip() if m.group(4) else None
        decl_line = raw.count("\n", 0, m.start()) + 1

        # Guardie #if/#ifdef/#else immediatamente sopra la dichiarazione
        guards: list[str] = []
        for line in reversed(raw[: m.start()].splitlines()[-40:]):
            s = line.strip()
            if not s:
                continue
            if s.startswith("//") or s.startswith("/*") or s.startswith("*"):
                continue
            if s.startswith("#"):
                if re.match(r"#\s*(if|ifdef|ifndef|else|elif)\b", s):
                    guards.append(re.sub(r"\s+", " ", s))
                    continue
                break
            break
        guards.reverse()

        body_start = m.end()  # subito dopo '{'
        body_end = _find_matching_brace(raw, body_start)  # dopo '}'
        body = raw[body_start : body_end - 1]
        body_line = raw.count("\n", 0, body_start) + 1

        arrays.append(
            ArrayDecl(
                name=f"{prefix}_{base}",
                base_name=base,
                prefix=prefix,
                rows_expr=rows_expr,
                cols_expr=cols_expr,
                line=decl_line,
                outer_guards=guards,
                body=body,
                body_start_line=body_line,
            )
        )
    return arrays


# ---------------------------------------------------------------------------
# Parser corpo: approccio a stack su direttive + token
# ---------------------------------------------------------------------------

RE_PREPROC_LINE = re.compile(
    r"^[ \t]*#\s*(if|ifdef|ifndef|elif|else|endif)\b(.*)$"
)
RE_BLOCK_COMMENT = re.compile(r"/\*.*?\*/", re.DOTALL)
RE_LINE_COMMENT = re.compile(r"//.*?$", re.MULTILINE)
RE_IDENT = re.compile(r"[A-Za-z_]\w*")


def _blank_comments(text: str) -> str:
    """Rimuove commenti lasciando i newline (numeri di riga stabili)."""

    def blank(m: re.Match) -> str:
        return re.sub(r"[^\n]", " ", m.group(0))

    text = RE_BLOCK_COMMENT.sub(blank, text)
    text = RE_LINE_COMMENT.sub("", text)
    return text


@dataclass
class _PendingClosedIf:
    """
    #if/#ifdef chiuso ma non ancora sommato al parent.

    Serve per fondere come alternative:
    - condizioni complementari consecutive (defined(X) poi !defined(X))
    - blocchi distinti con la stessa sequenza di commenti indice
      (es. #ifdef MODELLO_ESPRESSO … #ifdef MODELLO_SOLUBILE entrambi /* n. 210 */)
    """

    condition: str
    base_index: int
    contributed: int
    comment_seq: tuple[int, ...]


@dataclass
class _BranchFrame:
    """Frame dello stack preprocessore durante il conteggio bilanciato."""

    kind: str  # if / ifdef / ifndef
    condition: str
    # Conteggio elementi accumulato nel ramo corrente
    counts: list[int] = field(default_factory=lambda: [0])
    # Indice del ramo attivo in counts
    active: int = 0
    line: int = 0
    # Indice reale di partenza di questo frame nell'array C
    # (i rami #else/#elif ripartono dallo stesso base_index)
    base_index: int = 0
    # Etichette dei rami per il path (ramo 0 = condizione, poi else/elif)
    branch_labels: list[str] = field(default_factory=list)
    # #if figlio appena chiuso in attesa di un eventuale complemento/alternativa
    pending_closed: Optional[_PendingClosedIf] = None
    # Commenti indice raccolti per ramo (per riconoscere alternative consecutive)
    comments_in_branch: list[list[int]] = field(default_factory=lambda: [[]])
    # Indice in `elements` all'apertura del frame (per rinumerare tutto il sottoalbero)
    elements_start: int = 0


def _normalize_ifdef_cond(cond: str) -> str:
    """
    Uniforma forme equivalenti così GB/ML non risultano diversi solo per lo stile:
      ifdef X          ~  if defined(X)
      ifndef X         ~  if !defined(X)
    """
    cond = re.sub(r"\s+", " ", cond).strip()
    m = re.match(r"ifdef (\w+)$", cond)
    if m:
        return f"if defined({m.group(1)})"
    m = re.match(r"ifndef (\w+)$", cond)
    if m:
        return f"if !defined({m.group(1)})"
    # if defined(X) / if !defined(X) già ok; normalizza spazi in defined ( X )
    cond = re.sub(r"defined\s*\(\s*(\w+)\s*\)", r"defined(\1)", cond)
    return cond


def _condition_predicate(cond: str) -> Optional[str]:
    """
    Estrae il predicato booleano normalizzato da una direttiva #if/#ifdef/#ifndef.

    Esempi:
      ifdef FOO              -> defined(FOO)
      ifndef FOO             -> !defined(FOO)
      if defined(FOO)        -> defined(FOO)
      if !defined(FOO)       -> !defined(FOO)
      if defined(A) && B     -> None (troppo complesso per il complemento automatico)
    """
    norm = _normalize_ifdef_cond(cond)
    # Toglie il prefisso "if "
    if norm.startswith("if "):
        pred = norm[3:].strip()
    else:
        pred = norm
    # Solo predicati semplici defined / !defined: niente && || …
    if re.fullmatch(r"!?defined\(\w+\)", pred):
        return pred
    return None


def _is_complement_condition(a: str, b: str) -> bool:
    """
    True se a e b sono negazioni l'una dell'altra (defined(X) vs !defined(X)).

    Contesto tabelle: spesso si scrive
      #if defined(FOO) … #endif
      #if !defined(FOO) … #endif
    invece di un unico #if/#else; i due blocchi condividono gli stessi indici array.
    """
    pa, pb = _condition_predicate(a), _condition_predicate(b)
    if pa is None or pb is None:
        return False
    if pa.startswith("!") and pa[1:] == pb:
        return True
    if pb.startswith("!") and pb[1:] == pa:
        return True
    return False


RE_INDEX_COMMENT = re.compile(
    r"/\*\s*(?:"
    r"(?:MSA|MSP|MSAP)\s*n\.\s*(\d+)"  # /* MSA n. 12 */
    r"|n\.\s*(\d+)"  # /* n. 12 */ oppure /*  n. 0   */
    r"|(\d+)"  # /* 12 */ oppure /* 01 */
    r")\s*\*/",
    re.IGNORECASE,
)


def _index_from_comment_match(m: re.Match) -> int:
    """Estrae l'intero dall'unico gruppo catturato di RE_INDEX_COMMENT."""
    for g in m.groups():
        if g is not None:
            return int(g)
    raise ValueError("RE_INDEX_COMMENT senza gruppo numerico")


def _is_block_comment_line_disabled(body: str, match_start: int) -> bool:
    """
    True se /* ... */ è disattivato da un // sulla stessa riga (es. ///* MSP n. 98 */).

    Contesto: nei .c spesso si lascia il vecchio messaggio come commento di riga;
    quel numero non deve entrare nel check né nel conteggio indici.
    """
    line_start = body.rfind("\n", 0, match_start) + 1
    before = body[line_start:match_start]
    return "//" in before


def extract_index_comments(body: str) -> list[int]:
    """Estrae gli indici numerici dai commenti tipo /* MSA n. 3 */ o /* 01 */."""
    idxs: list[int] = []
    for m in RE_INDEX_COMMENT.finditer(body):
        if _is_block_comment_line_disabled(body, m.start()):
            continue
        idxs.append(_index_from_comment_match(m))
    return idxs


def extract_index_comments_by_line(
    body: str, base_line: int
) -> dict[int, list[int]]:
    """
    Mappa riga assoluta del file -> lista di indici nei commenti su quella riga.

    Usata per associare /* MSP n. 96 */ all'elemento che inizia sulla stessa riga
    e confrontarlo con logical_index (non con @B124 / ID catalogo).
    """
    by_line: dict[int, list[int]] = {}
    for m in RE_INDEX_COMMENT.finditer(body):
        if _is_block_comment_line_disabled(body, m.start()):
            continue
        abs_line = base_line + body.count("\n", 0, m.start())
        by_line.setdefault(abs_line, []).append(_index_from_comment_match(m))
    return by_line

def analyze_body(
    body: str,
    base_line: int,
    width: Optional[int],
    is_one_d: bool,
    array_name: str,
    file_name: str,
    issues: list[Issue],
) -> tuple[int, list[str], list[MessageElement]]:
    """
    Analizza il corpo di un array.

    Restituisce (row_count, ifdef_signature, elements).

    Strategia conteggio con #ifdef:
    - ogni elemento (stringhe concatenate fino alla virgola, oppure solo-identificatori)
      incrementa il contatore del ramo attivo
    - in un #if/#else/#elif i rami sono alternative: a chiusura #endif si prende
      il conteggio di UN ramo (devono essere uguali; altrimenti errore)
    - il totale del parent aumenta di quel valore
    - logical_index: i rami alternativi condividono gli stessi indici array

    Per la lunghezza: ogni elemento deve sommare width byte (se width nota),
    salvo elementi fatti solo di macro esterne (NOME_MACCHINA_1, ...).

    Per i commenti indice: sul body grezzo si costruisce la mappa riga→numero
    (/* MSP n. 96 */, /* 09 */, …); a flush si confronta con logical_index.
    """
    # Commenti indice dal body grezzo (prima di blankare /* */), per riga assoluta
    comments_by_line = extract_index_comments_by_line(body, base_line)
    clean = _blank_comments(body)

    # Stack di frame condizionali; counts[0] del frame root = totale
    root = _BranchFrame(
        kind="root",
        condition="",
        counts=[0],
        active=0,
        line=base_line,
        base_index=0,
        branch_labels=["root"],
    )
    stack: list[_BranchFrame] = [root]
    ifdef_sig: list[str] = []
    elements: list[MessageElement] = []

    # Accumulo token dell'elemento corrente
    cur_strings: list[str] = []
    cur_idents: list[str] = []
    cur_line = base_line

    def active_frame() -> _BranchFrame:
        return stack[-1]

    def add_row(n: int = 1) -> None:
        fr = active_frame()
        fr.counts[fr.active] += n

    def current_branch_path() -> str:
        """Path leggibile del ramo preprocessore attivo (senza il root)."""
        parts: list[str] = []
        for fr in stack[1:]:
            labels = fr.branch_labels
            label = labels[fr.active] if fr.active < len(labels) else fr.condition
            parts.append(label)
        return " / ".join(parts)

    def flush_pending(fr: _BranchFrame) -> None:
        """Somma al ramo attivo un #if figlio tenuto in sospeso (niente complemento dopo)."""
        if fr.pending_closed is not None:
            fr.counts[fr.active] += fr.pending_closed.contributed
            fr.pending_closed = None

    def comment_seq_of(fr: _BranchFrame) -> tuple[int, ...]:
        """
        Sequenza commenti del ramo più ricco (o del primo a parità).

        Usata per riconoscere #ifdef consecutivi che ripetono gli stessi n.
        (tipicamente modelli mutualmente esclusivi scritti come ifdef separati).
        """
        if not fr.comments_in_branch:
            return ()
        # Preferisci un ramo che ha commenti; a parità prendi quello con più elementi
        best = max(
            range(len(fr.comments_in_branch)),
            key=lambda i: (
                len(fr.comments_in_branch[i]),
                fr.counts[i] if i < len(fr.counts) else 0,
            ),
        )
        return tuple(fr.comments_in_branch[best])

    def renumber_frame_elements(fr: _BranchFrame, delta: int) -> None:
        """Sposta gli logical_index di tutto il sottoalbero del frame di -delta."""
        if delta == 0:
            return
        # Dal push del frame a ora: tutti gli elementi (anche in #if annidati)
        for ei in range(fr.elements_start, len(elements)):
            elements[ei].logical_index -= delta

    def flush_element() -> None:
        nonlocal cur_strings, cur_idents, cur_line
        if not cur_strings and not cur_idents:
            return

        fr = active_frame()
        # Eventuale #if figlio sospeso non ha avuto complemento: consolidalo prima
        flush_pending(fr)
        # Indice reale nell'array: base del frame + elementi già visti in questo ramo
        logical_idx = fr.base_index + fr.counts[fr.active]

        # Parametri = run consecutive di slot; slot piatti = flatten dei gruppi
        param_groups = extract_placeholder_groups(cur_strings)
        slots = [s for g in param_groups for s in g]

        preview = "".join(s[1:-1][:20] for s in cur_strings[:2])
        if len(preview) > 40:
            preview = preview[:40]

        # Solo macro (es. NOME_MACCHINA_1): niente prefisso @Xnnn
        is_macro_only = bool(cur_idents) and not cur_strings
        # Primi 5 byte del messaggio (per il check ID solo su ML)
        msg_id_prefix = (
            None if is_macro_only else extract_msg_id_prefix(cur_strings)
        )

        # Commento indice sulla stessa riga dell'inizio elemento (/* MSP n. 96 */)
        # Non è l'ID @Xnnn: il confronto col logical_index avviene a fine analisi
        # (dopo eventuali rinumerazioni per #ifdef complementari/alternativi).
        comment_idxs = comments_by_line.get(cur_line, [])
        comment_index = comment_idxs[0] if comment_idxs else None

        branch = current_branch_path()
        branch_txt = f" ramo='{branch}'" if branch else ""

        # Stesso slot più di una volta nello stesso messaggio = errore
        # (vale anche se non consecutivi: \5\6\7\5)
        slot_counts = Counter(slots)
        duplicated = sorted(s for s, n in slot_counts.items() if n > 1)
        if duplicated:
            dup_detail = ", ".join(
                f"{format_placeholders([s])} x{slot_counts[s]}" for s in duplicated
            )
            issues.append(
                Issue(
                    "error",
                    file_name,
                    cur_line,
                    f"{array_name}[{logical_idx}]: placeholder duplicati{branch_txt}: "
                    f"{dup_detail} in {format_placeholders(slots)} "
                    f'(anteprima: "{preview}")',
                )
            )

        elements.append(
            MessageElement(
                logical_index=logical_idx,
                line=cur_line,
                placeholders=tuple(slots),
                param_groups=param_groups,
                preview=preview,
                branch_path=branch,
                is_macro_only=is_macro_only,
                msg_id_prefix=msg_id_prefix,
                comment_index=comment_index,
            )
        )

        # Traccia commenti del ramo attivo (per fondere #ifdef alternativi)
        if comment_index is not None:
            fr.comments_in_branch[fr.active].append(comment_index)

        add_row(1)

        # Check lunghezza (solo se abbiamo stringhe e width nota)
        if width is not None and cur_strings:
            total = sum(c_string_byte_len(s) for s in cur_strings)
            if cur_idents:
                # Macro + stringhe: segnala solo overflow
                if total > width:
                    issues.append(
                        Issue(
                            "error",
                            file_name,
                            cur_line,
                            f"{array_name}: stringhe len={total} > larghezza {width}",
                        )
                    )
            elif total != width:
                preview_len = "".join(s[1:-1][:24] for s in cur_strings[:2])
                issues.append(
                    Issue(
                        "error",
                        file_name,
                        cur_line,
                        f"{array_name}: lunghezza elemento={total}, attesa={width} "
                        f'(anteprima: "{preview_len}")',
                    )
                )

        cur_strings = []
        cur_idents = []

    # Tokenizza l'intero corpo (già senza commenti) carattere per carattere,
    # ma gestisce le direttive quando compaiono a inizio riga.
    pos = 0
    text = clean
    text_len = len(text)

    while pos < text_len:
        # Inizio riga?
        if pos == 0 or text[pos - 1] == "\n":
            # Leggi la riga
            nl = text.find("\n", pos)
            line_text = text[pos:] if nl < 0 else text[pos:nl]
            abs_line = base_line + text.count("\n", 0, pos)
            pm = RE_PREPROC_LINE.match(line_text)
            if pm:
                flush_element()
                directive = pm.group(1)
                rest = pm.group(2).strip()
                # Rimuovi eventuale commento residuo tipo //...
                rest = re.split(r"//|/\*", rest)[0].strip()
                cond = f"{directive} {rest}".strip()

                if directive in ("if", "ifdef", "ifndef"):
                    indent = "  " * (len(stack) - 1)
                    norm = _normalize_ifdef_cond(cond)
                    ifdef_sig.append(f"{indent}IF({norm})")
                    parent = active_frame()
                    # Complemento formale del #if sospeso: stessi indici (come #else)
                    if parent.pending_closed and _is_complement_condition(
                        parent.pending_closed.condition, cond
                    ):
                        child_base = parent.pending_closed.base_index
                    elif parent.pending_closed:
                        # Ipotesi sequenziale: parte dopo il blocco sospeso.
                        # Se a #endif i commenti coincidono, rinumeriamo come alternativa.
                        child_base = (
                            parent.pending_closed.base_index
                            + parent.pending_closed.contributed
                        )
                    else:
                        child_base = parent.base_index + parent.counts[parent.active]
                    stack.append(
                        _BranchFrame(
                            kind=directive,
                            condition=cond,
                            counts=[0],
                            active=0,
                            line=abs_line,
                            base_index=child_base,
                            branch_labels=[norm],
                            elements_start=len(elements),
                        )
                    )
                elif directive == "elif":
                    fr = active_frame()
                    if fr.kind == "root":
                        issues.append(
                            Issue(
                                "error",
                                file_name,
                                abs_line,
                                f"{array_name}: #elif senza #if aperto",
                            )
                        )
                    else:
                        flush_pending(fr)
                        indent = "  " * (len(stack) - 2)
                        elif_norm = _normalize_ifdef_cond(f"if {rest}")
                        ifdef_sig.append(f"{indent}ELIF({elif_norm})")
                        fr.counts.append(0)
                        fr.active = len(fr.counts) - 1
                        fr.branch_labels.append(f"ELIF({elif_norm})")
                        fr.comments_in_branch.append([])
                elif directive == "else":
                    fr = active_frame()
                    if fr.kind == "root":
                        issues.append(
                            Issue(
                                "error",
                                file_name,
                                abs_line,
                                f"{array_name}: #else senza #if aperto",
                            )
                        )
                    else:
                        flush_pending(fr)
                        indent = "  " * (len(stack) - 2)
                        ifdef_sig.append(f"{indent}ELSE")
                        fr.counts.append(0)
                        fr.active = len(fr.counts) - 1
                        fr.branch_labels.append(f"ELSE({fr.condition})")
                        fr.comments_in_branch.append([])
                elif directive == "endif":
                    fr = stack.pop()
                    if fr.kind == "root":
                        stack.append(fr)  # non dovrebbe succedere
                        issues.append(
                            Issue(
                                "error",
                                file_name,
                                abs_line,
                                f"{array_name}: #endif in eccesso",
                            )
                        )
                    else:
                        flush_pending(fr)
                        indent = "  " * (len(stack) - 1)
                        ifdef_sig.append(f"{indent}ENDIF")
                        # Tutti i rami devono avere lo stesso numero di elementi
                        if len(fr.counts) > 1:
                            first = fr.counts[0]
                            for idx, c in enumerate(fr.counts[1:], start=1):
                                if c != first:
                                    issues.append(
                                        Issue(
                                            "error",
                                            file_name,
                                            fr.line,
                                            f"{array_name}: rami #if disallineati "
                                            f"sotto '{fr.condition}': "
                                            f"ramo0={first}, ramo{idx}={c}",
                                        )
                                    )
                        contributed = max(fr.counts) if fr.counts else 0
                        seq = comment_seq_of(fr)
                        parent = active_frame()
                        pending = parent.pending_closed

                        if pending and _is_complement_condition(
                            pending.condition, fr.condition
                        ):
                            # defined(X) / !defined(X): stessa base, max contributi
                            parent.pending_closed = _PendingClosedIf(
                                condition=pending.condition,
                                base_index=pending.base_index,
                                contributed=max(pending.contributed, contributed),
                                comment_seq=pending.comment_seq or seq,
                            )
                        elif (
                            pending
                            and seq
                            and pending.comment_seq
                            and seq == pending.comment_seq
                        ):
                            # Stessa sequenza di commenti: alternativa (es. ESPRESSO/SOLUBILE).
                            # Gli elementi erano numerati in sequenza → riporta alla base comune.
                            overshoot = fr.base_index - pending.base_index
                            renumber_frame_elements(fr, overshoot)
                            parent.pending_closed = _PendingClosedIf(
                                condition=pending.condition,
                                base_index=pending.base_index,
                                contributed=max(pending.contributed, contributed),
                                comment_seq=pending.comment_seq,
                            )
                        else:
                            # Blocco indipendente: consolida l'eventuale pending precedente
                            if pending is not None:
                                parent.counts[parent.active] += pending.contributed
                            parent.pending_closed = _PendingClosedIf(
                                condition=fr.condition,
                                base_index=fr.base_index,
                                contributed=contributed,
                                comment_seq=seq,
                            )

                pos = (nl + 1) if nl >= 0 else text_len
                continue

        ch = text[pos]

        if ch in " \t\r\n":
            pos += 1
            continue

        if ch == '"':
            m = RE_C_STRING.match(text, pos)
            if not m:
                pos += 1
                continue
            if not cur_strings and not cur_idents:
                cur_line = base_line + text.count("\n", 0, pos)
            cur_strings.append(m.group(0))
            pos = m.end()
            continue

        if ch.isalpha() or ch == "_":
            m = RE_IDENT.match(text, pos)
            if not m:
                pos += 1
                continue
            # Parole chiave preprocessore residue non dovrebbero arrivare qui
            ident = m.group(0)
            if not cur_strings and not cur_idents:
                cur_line = base_line + text.count("\n", 0, pos)
            cur_idents.append(ident)
            pos = m.end()
            continue

        if ch == ",":
            flush_element()
            pos += 1
            continue

        # Ignora altro (es. ';' fuori posto)
        pos += 1

    flush_element()

    # Chiudi eventuali #if rimasti aperti (file malformato)
    while len(stack) > 1:
        fr = stack.pop()
        flush_pending(fr)
        issues.append(
            Issue(
                "error",
                file_name,
                fr.line,
                f"{array_name}: #if non chiuso ('{fr.condition}')",
            )
        )
        contributed = max(fr.counts) if fr.counts else 0
        parent = active_frame()
        if parent.pending_closed is not None:
            parent.counts[parent.active] += parent.pending_closed.contributed
            parent.pending_closed = None
        add_row(contributed)

    flush_pending(root)

    row_count = root.counts[0]

    # Array 1D: ci aspettiamo 1 elemento (una stringa), non 'rows_expr' elementi
    if is_one_d and row_count == 0 and cur_strings:
        row_count = 1

    # Dopo rinumerazioni: commento /* MSP n. N */ deve coincidere con logical_index
    _check_comment_vs_logical_index(
        elements,
        comments_by_line,
        is_one_d,
        array_name,
        file_name,
        issues,
    )

    return row_count, ifdef_sig, elements


def _check_comment_vs_logical_index(
    elements: list[MessageElement],
    comments_by_line: dict[int, list[int]],
    is_one_d: bool,
    array_name: str,
    file_name: str,
    issues: list[Issue],
) -> None:
    """
    Verifica che /* MSP n. 96 */ (o /* 09 */, /* n. 3 */, …) == indice reale array.

    Indipendente dall'ID catalogo @Xnnn: @B124 su MSP n. 96 è corretto.
    """
    if is_one_d:
        return

    for el in elements:
        branch_txt = f" ramo='{el.branch_path}'" if el.branch_path else ""
        if el.comment_index is not None and el.comment_index != el.logical_index:
            issues.append(
                Issue(
                    "error",
                    file_name,
                    el.line,
                    f"{array_name}[{el.logical_index}]: commento indice={el.comment_index} "
                    f"!= indice reale={el.logical_index}{branch_txt} "
                    f'(anteprima: "{el.preview}")',
                )
            )
        elif el.comment_index is None and comments_by_line:
            issues.append(
                Issue(
                    "warning",
                    file_name,
                    el.line,
                    f"{array_name}[{el.logical_index}]: manca commento indice "
                    f"(atteso n. {el.logical_index}){branch_txt} "
                    f'(anteprima: "{el.preview}")',
                )
            )

# ---------------------------------------------------------------------------
# Analisi file / allineamento
# ---------------------------------------------------------------------------

def analyze_file(
    path: Path,
    macros: dict[str, list[int]],
    issues: list[Issue],
) -> list[ArrayDecl]:
    rel = path.name
    arrays = extract_arrays(path)

    for arr in arrays:
        is_one_d = arr.cols_expr is None
        # Per i 1D noti, [N] è la larghezza della stringa, non il conteggio
        if arr.base_name in ONE_D_TABLES:
            is_one_d = True

        expected_macro = EXPECTED_COUNT_MACROS.get(arr.base_name)

        if not is_one_d:
            # Letterale al posto della macro LANG_DEF
            if expected_macro and arr.rows_expr.isdigit():
                lit = int(arr.rows_expr)
                macro_vals = macros.get(expected_macro, [])
                if macro_vals and lit not in macro_vals:
                    issues.append(
                        Issue(
                            "error",
                            rel,
                            arr.line,
                            f"{arr.name}: letterale [{lit}] != {expected_macro}={macro_vals}",
                        )
                    )
                else:
                    issues.append(
                        Issue(
                            "warning",
                            rel,
                            arr.line,
                            f"{arr.name}: usa letterale [{lit}] al posto di {expected_macro}",
                        )
                    )
            elif expected_macro and arr.rows_expr != expected_macro:
                if arr.rows_expr not in macros:
                    issues.append(
                        Issue(
                            "error",
                            rel,
                            arr.line,
                            f"{arr.name}: dimensione '{arr.rows_expr}' sconosciuta "
                            f"(attesa {expected_macro})",
                        )
                    )

            expected_w = EXPECTED_WIDTHS.get(arr.base_name)
            if (
                expected_w is not None
                and arr.cols_expr
                and arr.cols_expr.isdigit()
                and int(arr.cols_expr) != expected_w
            ):
                issues.append(
                    Issue(
                        "error",
                        rel,
                        arr.line,
                        f"{arr.name}: larghezza [{arr.cols_expr}] != attesa {expected_w}",
                    )
                )

        # Larghezza per il check stringhe
        if is_one_d:
            width = int(arr.rows_expr) if arr.rows_expr.isdigit() else None
        else:
            width = int(arr.cols_expr) if arr.cols_expr and arr.cols_expr.isdigit() else None

        row_count, sig, elements = analyze_body(
            arr.body,
            arr.body_start_line,
            width,
            is_one_d,
            arr.name,
            rel,
            issues,
        )
        arr.ifdef_sig = sig
        arr.elements = elements

        # Conteggio preferito: commenti indice (/* MSA n. N */) se presenti.
        # I branch #ifdef spesso sono alternative sullo STESSO indice, quindi il
        # conteggio bilanciato può risultare > MAX_* anche quando è corretto.
        # I commenti indice riflettono lo schema reale 0..MAX-1.
        indices = extract_index_comments(arr.body)
        if indices and not is_one_d:
            max_idx = max(indices)
            unique = sorted(set(indices))
            count_from_idx = max_idx + 1
            # Segnala buchi nella numerazione (es. manca n. 5)
            expected_set = list(range(max_idx + 1))
            # Alcune tabelle numerano da 1 (/* 01 */) invece che da 0
            if unique and unique[0] >= 1 and 0 not in unique:
                expected_set = list(range(1, max_idx + 1))
                count_from_idx = max_idx  # 1..N => N elementi
                if unique[0] == 1:
                    missing = [i for i in expected_set if i not in unique]
                else:
                    missing = []
            else:
                missing = [i for i in expected_set if i not in unique]

            arr.row_count = count_from_idx
            if missing:
                preview = missing[:12]
                more = "..." if len(missing) > 12 else ""
                issues.append(
                    Issue(
                        "warning",
                        rel,
                        arr.line,
                        f"{arr.name}: indici mancanti nei commenti: {preview}{more} "
                        f"(tot. mancanti={len(missing)})",
                    )
                )
        else:
            arr.row_count = row_count

        if is_one_d:
            # 1 elemento; lunghezza già verificata in analyze_body
            if row_count != 1:
                issues.append(
                    Issue(
                        "error",
                        rel,
                        arr.line,
                        f"{arr.name}: array 1D dovrebbe avere 1 stringa, trovate {row_count}",
                    )
                )
        else:
            row_values = resolve_dim(arr.rows_expr, macros)
            if row_values and arr.row_count not in row_values:
                issues.append(
                    Issue(
                        "error",
                        rel,
                        arr.line,
                        f"{arr.name}: dichiarati {arr.rows_expr}={row_values} elementi, "
                        f"corpo ne indica {arr.row_count}"
                        + (
                            " (da commenti indice)"
                            if indices
                            else " (conteggio bilanciato #ifdef)"
                        ),
                    )
                )
            elif not row_values and not arr.rows_expr.isdigit():
                issues.append(
                    Issue(
                        "warning",
                        rel,
                        arr.line,
                        f"{arr.name}: '{arr.rows_expr}' non risolto in LANG_DEF.h "
                        f"(corpo: {arr.row_count} elementi)",
                    )
                )

    return arrays


def _norm_guards(guards: list[str]) -> list[str]:
    """Normalizza guardie esterne ignorando LANGUAGE_GB vs LANGUAGE_ML2."""
    out = []
    for g in guards:
        g2 = re.sub(r"LANGUAGE_(GB|ML2)", "LANGUAGE_XX", g)
        g2 = re.sub(r"\s+", " ", g2)
        out.append(g2)
    return out


def compare_alignment(
    gb_arrays: list[ArrayDecl],
    ml_arrays: list[ArrayDecl],
    macros: dict[str, list[int]],
    issues: list[Issue],
) -> None:
    def by_base(arrs: list[ArrayDecl]) -> dict[str, list[ArrayDecl]]:
        d: dict[str, list[ArrayDecl]] = {}
        for a in arrs:
            d.setdefault(a.base_name, []).append(a)
        return d

    gb_map = by_base(gb_arrays)
    ml_map = by_base(ml_arrays)

    for base in sorted(set(gb_map) | set(ml_map)):
        gb_list = gb_map.get(base, [])
        ml_list = ml_map.get(base, [])

        if not gb_list:
            for a in ml_list:
                issues.append(
                    Issue(
                        "error",
                        "MES_LARHEA_ML.c",
                        a.line,
                        f"tabella {a.name} in ML ma assente in GB",
                    )
                )
            continue
        if not ml_list:
            for a in gb_list:
                issues.append(
                    Issue(
                        "error",
                        "MES_LARHEA_GB.c",
                        a.line,
                        f"tabella {a.name} in GB ma assente in ML",
                    )
                )
            continue

        if len(gb_list) != len(ml_list):
            issues.append(
                Issue(
                    "error",
                    "alignment",
                    gb_list[0].line,
                    f"{base}: varianti diverse GB={len(gb_list)} ML={len(ml_list)} "
                    f"(#ifdef di dichiarazione non allineati)",
                )
            )

        for gb_a, ml_a in zip(gb_list, ml_list):
            if gb_a.cols_expr != ml_a.cols_expr:
                issues.append(
                    Issue(
                        "error",
                        "alignment",
                        ml_a.line,
                        f"{base}: larghezza GB[{gb_a.cols_expr}] vs ML[{ml_a.cols_expr}]",
                    )
                )

            gb_rows = resolve_dim(gb_a.rows_expr, macros)
            ml_rows = resolve_dim(ml_a.rows_expr, macros)
            if gb_rows and ml_rows and set(gb_rows).isdisjoint(ml_rows):
                issues.append(
                    Issue(
                        "error",
                        "alignment",
                        ml_a.line,
                        f"{base}: righe GB {gb_a.rows_expr}={gb_rows} vs "
                        f"ML {ml_a.rows_expr}={ml_rows}",
                    )
                )
            elif gb_a.rows_expr != ml_a.rows_expr:
                issues.append(
                    Issue(
                        "warning",
                        "alignment",
                        ml_a.line,
                        f"{base}: espressione diversa GB[{gb_a.rows_expr}] "
                        f"vs ML[{ml_a.rows_expr}] (risolti GB={gb_rows} ML={ml_rows})",
                    )
                )

            if gb_a.row_count != ml_a.row_count:
                issues.append(
                    Issue(
                        "error",
                        "alignment",
                        ml_a.line,
                        f"{base}: elementi corpo GB={gb_a.row_count} vs ML={ml_a.row_count}",
                    )
                )

            if gb_a.ifdef_sig != ml_a.ifdef_sig:
                diff_at = next(
                    (
                        i
                        for i, (g, m) in enumerate(zip(gb_a.ifdef_sig, ml_a.ifdef_sig))
                        if g != m
                    ),
                    min(len(gb_a.ifdef_sig), len(ml_a.ifdef_sig)),
                )
                gb_bit = (
                    gb_a.ifdef_sig[diff_at]
                    if diff_at < len(gb_a.ifdef_sig)
                    else "<fine>"
                )
                ml_bit = (
                    ml_a.ifdef_sig[diff_at]
                    if diff_at < len(ml_a.ifdef_sig)
                    else "<fine>"
                )
                issues.append(
                    Issue(
                        "error",
                        "alignment",
                        ml_a.line,
                        f"{base}: struttura #ifdef diversa @idx {diff_at}: "
                        f"GB='{gb_bit.strip()}' ML='{ml_bit.strip()}'",
                    )
                )

            if _norm_guards(gb_a.outer_guards) != _norm_guards(ml_a.outer_guards):
                issues.append(
                    Issue(
                        "warning",
                        "alignment",
                        ml_a.line,
                        f"{base}: guardie esterne diverse "
                        f"GB={gb_a.outer_guards} ML={ml_a.outer_guards}",
                    )
                )

            # Placeholder: stesso numero e stessi slot (0..15) a parità di
            # posizione strutturale / indice reale nell'array (non dai commenti).
            _compare_placeholders(base, gb_a, ml_a, issues)


def _compare_placeholders(
    base: str,
    gb_a: ArrayDecl,
    ml_a: ArrayDecl,
    issues: list[Issue],
) -> None:
    """
    Confronta placeholder e raggruppamento in parametri tra GB e ML.

    L'abbinamento è per ordine di visita nel corpo (struttura #ifdef identica)
    e l'indice riportato è logical_index = indice reale nell'array C.

    Controlli:
    1. stessi slot (quantità + sequenza)
    2. stessi parametri = stesse run consecutive di slot
       (es. GB \\1\\2 + \\3\\4  vs  ML \\1 + \\2\\3\\4 → errore sulle lunghezze)
    """
    gb_elems = gb_a.elements
    ml_elems = ml_a.elements

    if len(gb_elems) != len(ml_elems):
        # Di solito già coperto da row_count / ifdef; resta un errore esplicito
        issues.append(
            Issue(
                "error",
                "alignment",
                ml_a.line,
                f"{base}: elementi visitati GB={len(gb_elems)} vs ML={len(ml_elems)} "
                f"(impossibile confrontare i placeholder)",
            )
        )
        return

    for gb_el, ml_el in zip(gb_elems, ml_elems):
        # Con struttura allineata gli indici logici devono coincidere
        if gb_el.logical_index != ml_el.logical_index:
            issues.append(
                Issue(
                    "error",
                    "alignment",
                    ml_el.line,
                    f"{base}: indice reale disallineato in visita "
                    f"GB[{gb_el.logical_index}] (riga {gb_el.line}) vs "
                    f"ML[{ml_el.logical_index}] (riga {ml_el.line})",
                )
            )
            continue

        branch = ""
        if gb_el.branch_path or ml_el.branch_path:
            branch = f" ramo='{gb_el.branch_path or ml_el.branch_path}'"
        loc = (
            f'(GB riga {gb_el.line} "{gb_el.preview}" / '
            f'ML "{ml_el.preview}")'
        )

        # 1) Slot piatti: quantità e quali
        if gb_el.placeholders != ml_el.placeholders:
            gb_cnt = Counter(gb_el.placeholders)
            ml_cnt = Counter(ml_el.placeholders)
            issues.append(
                Issue(
                    "error",
                    "alignment",
                    ml_el.line,
                    f"{base}[{gb_el.logical_index}]: placeholder diversi{branch}: "
                    f"GB({len(gb_el.placeholders)})={format_placeholders(gb_el.placeholders)} "
                    f"vs ML({len(ml_el.placeholders)})={format_placeholders(ml_el.placeholders)} "
                    f"{loc}"
                    + (
                        ""
                        if gb_cnt == ml_cnt
                        else f" [multiset GB={dict(gb_cnt)} ML={dict(ml_cnt)}]"
                    ),
                )
            )
            # Se gli slot già differiscono, il raggruppamento è secondario
            continue

        # 2) Parametri: stesse run (lunghezze e contenuto dei gruppi)
        #    Cattura es. GB [2]+[2] vs ML [1]+[3] a parità di slot totali.
        if gb_el.param_groups == ml_el.param_groups:
            continue

        gb_lens = [len(g) for g in gb_el.param_groups]
        ml_lens = [len(g) for g in ml_el.param_groups]
        issues.append(
            Issue(
                "error",
                "alignment",
                ml_el.line,
                f"{base}[{gb_el.logical_index}]: parametri diversi{branch}: "
                f"GB lunghezze={gb_lens} ({format_param_groups(gb_el.param_groups)}) "
                f"vs ML lunghezze={ml_lens} ({format_param_groups(ml_el.param_groups)}) "
                f"{loc}",
            )
        )


# Formato ID catalogo ML: @ + tabella A-Z + indice a 3 cifre (es. @A001)
RE_ML_MSG_ID = re.compile(r"^@[A-Z]\d{3}$")


def _describe_ml_id_format_error(prefix: str) -> str:
    """
    Spiega perché un prefisso non rispetta @ + A-Z + 3 cifre.
    Usato nei messaggi di errore per orientare la correzione.
    """
    if len(prefix) < 5:
        return f"lunghezza={len(prefix)} (servono 5 caratteri)"
    reasons: list[str] = []
    if prefix[0] != "@":
        reasons.append(f"1° carattere {prefix[0]!r} != '@'")
    if not ("A" <= prefix[1] <= "Z"):
        reasons.append(f"2° carattere {prefix[1]!r} non è A-Z maiuscolo")
    if not prefix[2:5].isdigit():
        reasons.append(f"cifre {prefix[2:5]!r} non sono 3 digit numerici")
    return "; ".join(reasons) if reasons else "formato non valido"


def _is_exempt_from_ml_id_check(el: MessageElement) -> bool:
    """
    Messaggi ML ammessi senza ID @Xnnn.

    Caso noto: MSP "language:" + "Multilanguage" (testo fisso a display,
    non voce di catalogo). Il codice commentato non arriva qui: il parser
    del corpo azzera già // e /* */ prima di estrarre gli elementi.
    """
    text = (el.preview or "").lower()
    # Accetta anche varianti di spaziatura / capitalizzazione
    return "language:" in text and "multilanguage" in text


def check_ml_message_ids(ml_arrays: list[ArrayDecl], issues: list[Issue]) -> None:
    """
    Controlli specifici di MES_LARHEA_ML.c sugli ID catalogo.

    Regole (confermate):
    - solo file ML (non GB); stringhe in commento ignorate dal parser
    - primi 5 caratteri: '@' + A-Z + 3 cifre zero-padded
    - stesso ID non può ripetersi su tutto il file (anche tra #ifdef diversi)
    - elementi solo-macro (senza stringhe) saltati
    - eccezione: "language:" / "Multilanguage" senza @Xnnn
    """
    # id -> prima occorrenza (array, riga, indice logico, ramo)
    seen: dict[str, tuple[str, int, int, str]] = {}

    for arr in ml_arrays:
        # Difesa: in teoria qui arrivano solo array ML_*
        if arr.prefix != "ML":
            continue
        for el in arr.elements:
            if el.is_macro_only:
                continue
            # Testo fisso "language / Multilanguage": fuori dal catalogo @Xnnn
            if _is_exempt_from_ml_id_check(el):
                continue

            branch = f" ramo='{el.branch_path}'" if el.branch_path else ""
            prefix = el.msg_id_prefix or ""

            if len(prefix) < 5 or not RE_ML_MSG_ID.match(prefix):
                issues.append(
                    Issue(
                        "error",
                        "MES_LARHEA_ML.c",
                        el.line,
                        f"{arr.name}[{el.logical_index}]: ID messaggio non valido"
                        f"{branch}: prefisso={prefix!r} "
                        f"({_describe_ml_id_format_error(prefix)}) "
                        f'(anteprima: "{el.preview}")',
                    )
                )
                continue

            prev = seen.get(prefix)
            if prev is not None:
                prev_arr, prev_line, prev_idx, prev_branch = prev
                prev_branch_txt = f" ramo='{prev_branch}'" if prev_branch else ""
                issues.append(
                    Issue(
                        "error",
                        "MES_LARHEA_ML.c",
                        el.line,
                        f"{arr.name}[{el.logical_index}]: ID duplicato {prefix}"
                        f"{branch}: già usato in {prev_arr}[{prev_idx}] "
                        f"(riga {prev_line}{prev_branch_txt})",
                    )
                )
                continue

            seen[prefix] = (arr.name, el.line, el.logical_index, el.branch_path)


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def find_repo_root(start: Path) -> Path:
    cur = start.resolve()
    for p in [cur, *cur.parents]:
        if (p / "MES_LARHEA_GB.c").exists() and (p / "LANG_DEF.h").exists():
            return p
    return start.resolve()


def main(argv: Optional[list[str]] = None) -> int:
    # Evita crash su Windows con caratteri non-cp1252 nei report
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
        sys.stderr.reconfigure(encoding="utf-8", errors="replace")

    parser = argparse.ArgumentParser(
        description=(
            "Verifica dimensionamento, allineamento, placeholder "
            "(\\0..\\x0F), ID messaggio ML (@ + A-Z + 3 cifre) "
            "e coerenza commento indice (/* MSP n. N */) vs indice reale "
            "delle tabelle MES_LARHEA_*.c"
        ),
    )
    parser.add_argument("--root", type=Path, default=None)
    parser.add_argument(
        "--warnings-as-errors",
        action="store_true",
        help="Fallisce anche in presenza di soli warning",
    )
    parser.add_argument(
        "--report",
        type=Path,
        default=None,
        help="Percorso del report .txt (default: <root>/check_language_report.txt)",
    )
    parser.add_argument(
        "--no-report",
        action="store_true",
        help="Non scrivere il file di report",
    )
    args = parser.parse_args(argv)

    root = args.root or find_repo_root(Path(__file__).parent)
    lang_def = root / "LANG_DEF.h"
    gb_path = root / "MES_LARHEA_GB.c"
    ml_path = root / "MES_LARHEA_ML.c"
    report_path = args.report or (root / "check_language_report.txt")

    lines: list[str] = []

    def out(msg: str = "") -> None:
        """Stampa a console e accumula per il file di report."""
        print(msg)
        lines.append(msg)

    missing = [p for p in (lang_def, gb_path, ml_path) if not p.exists()]
    if missing:
        for p in missing:
            msg = f"[ERROR] file mancante: {p}"
            print(msg, file=sys.stderr)
            lines.append(msg)
        if not args.no_report:
            _write_report(report_path, lines, failed=True)
        return 1

    out(f"Root: {root}")
    out(f"File: {lang_def.name}, {gb_path.name}, {ml_path.name}")
    out()

    macros = parse_lang_def(lang_def)
    out(f"Macro MAX_* ({len(macros)}):")
    for k in sorted(macros):
        out(f"  {k} = {macros[k]}")
    out()

    issues: list[Issue] = []
    gb_arrays = analyze_file(gb_path, macros, issues)
    ml_arrays = analyze_file(ml_path, macros, issues)
    compare_alignment(gb_arrays, ml_arrays, macros, issues)
    # Solo ML: formato e unicità degli ID @A001, @B012, …
    check_ml_message_ids(ml_arrays, issues)

    errors = [i for i in issues if i.severity == "error"]
    warnings = [i for i in issues if i.severity == "warning"]

    for i in issues:
        out(i.format())

    out()
    out(
        f"Riepilogo: {len(errors)} errori, {len(warnings)} warning "
        f"(array GB={len(gb_arrays)}, ML={len(ml_arrays)})"
    )

    failed = bool(errors or (args.warnings_as_errors and warnings))
    out("FAIL" if failed else "OK")

    if not args.no_report:
        _write_report(report_path, lines, failed=failed)
        print(f"\nReport scritto in: {report_path}")

    return 1 if failed else 0


def _write_report(path: Path, lines: list[str], failed: bool) -> None:
    """
    Scrive check_language_report.txt nella root del progetto.
    Così in SourceTree/Explorer si aprono gli errori senza rilanciare a mano il tool.
    """
    from datetime import datetime, timezone

    header = [
        "=== check_language report ===",
        f"Data (UTC): {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M:%S')}",
        f"Esito: {'FAIL' if failed else 'OK'}",
        "",
        "Nota: questo file elenca gli errori delle tabelle MES_LARHEA "
        "(dimensioni/allineamento/placeholder/ID ML @Xnnn/"
        "commento indice vs indice reale).",
        "Se SourceTree rifiuta il push con GH013 / 'pull request' / 'status check',",
        "quello e' il ruleset GitHub (serve una PR), non necessariamente un errore di questo elenco.",
        "",
        "----------",
        "",
    ]
    path.write_text("\n".join(header + lines) + "\n", encoding="utf-8", errors="replace")


if __name__ == "__main__":
    sys.exit(main())
