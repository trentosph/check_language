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

Uso:
  python tools/check_language_arrays.py
  python tools/check_language_arrays.py --warnings-as-errors

Exit code 0 = OK, 1 = errori (o warning se --warnings-as-errors).
"""

from __future__ import annotations

import argparse
import re
import sys
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


def c_string_byte_len(literal: str) -> int:
    """Lunghezza in byte del contenuto di \"...\" (ogni escape = 1 byte u8)."""
    inner = literal[1:-1]
    length = 0
    i = 0
    while i < len(inner):
        if inner[i] != "\\":
            length += 1
            i += 1
            continue
        m = RE_HEX_ESC.match(inner, i)
        if m:
            length += 1
            i = m.end()
            continue
        m = RE_OCT_ESC.match(inner, i)
        if m:
            length += 1
            i = m.end()
            continue
        # Escape semplice: \n, \t, oppure backslash + un carattere
        length += 1
        i += 2 if i + 1 < len(inner) else 1
    return length


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
class _BranchFrame:
    """Frame dello stack preprocessore durante il conteggio bilanciato."""

    kind: str  # if / ifdef / ifndef
    condition: str
    # Conteggio elementi accumulato nel ramo corrente
    counts: list[int] = field(default_factory=lambda: [0])
    # Indice del ramo attivo in counts
    active: int = 0
    line: int = 0


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


RE_INDEX_COMMENT = re.compile(
    r"/\*\s*(?:"
    r"(?:MSA|MSP|MSAP)\s*n\.\s*(\d+)"  # /* MSA n. 12 */
    r"|n\.\s*(\d+)"  # /* n. 12 */
    r"|(\d+)"  # /* 12 */ oppure /* 01 */
    r")\s*\*/",
    re.IGNORECASE,
)


def extract_index_comments(body: str) -> list[int]:
    """Estrae gli indici numerici dai commenti tipo /* MSA n. 3 */ o /* 01 */."""
    idxs: list[int] = []
    for m in RE_INDEX_COMMENT.finditer(body):
        for g in m.groups():
            if g is not None:
                idxs.append(int(g))
                break
    return idxs


def analyze_body(
    body: str,
    base_line: int,
    width: Optional[int],
    is_one_d: bool,
    array_name: str,
    file_name: str,
    issues: list[Issue],
) -> tuple[int, list[str]]:
    """
    Analizza il corpo di un array.

    Restituisce (row_count, ifdef_signature).

    Strategia conteggio con #ifdef:
    - ogni elemento (stringhe concatenate fino alla virgola, oppure solo-identificatori)
      incrementa il contatore del ramo attivo
    - in un #if/#else/#elif i rami sono alternative: a chiusura #endif si prende
      il conteggio di UN ramo (devono essere uguali; altrimenti errore)
    - il totale del parent aumenta di quel valore

    Per la lunghezza: ogni elemento deve sommare width byte (se width nota),
    salvo elementi fatti solo di macro esterne (NOME_MACCHINA_1, ...).
    """
    clean = _blank_comments(body)
    lines = clean.splitlines(keepends=True)

    # Stack di frame condizionali; counts[0] del frame root = totale
    root = _BranchFrame(kind="root", condition="", counts=[0], active=0, line=base_line)
    stack: list[_BranchFrame] = [root]
    ifdef_sig: list[str] = []

    # Accumulo token dell'elemento corrente
    cur_strings: list[str] = []
    cur_idents: list[str] = []
    cur_line = base_line

    def active_frame() -> _BranchFrame:
        return stack[-1]

    def add_row(n: int = 1) -> None:
        fr = active_frame()
        fr.counts[fr.active] += n

    def flush_element() -> None:
        nonlocal cur_strings, cur_idents, cur_line
        if not cur_strings and not cur_idents:
            return

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
                preview = "".join(s[1:-1][:24] for s in cur_strings[:2])
                issues.append(
                    Issue(
                        "error",
                        file_name,
                        cur_line,
                        f"{array_name}: lunghezza elemento={total}, attesa={width} "
                        f'(anteprima: "{preview}")',
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
                    stack.append(
                        _BranchFrame(
                            kind=directive,
                            condition=cond,
                            counts=[0],
                            active=0,
                            line=abs_line,
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
                        indent = "  " * (len(stack) - 2)
                        elif_norm = _normalize_ifdef_cond(f"if {rest}")
                        ifdef_sig.append(f"{indent}ELIF({elif_norm})")
                        fr.counts.append(0)
                        fr.active = len(fr.counts) - 1
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
                        indent = "  " * (len(stack) - 2)
                        ifdef_sig.append(f"{indent}ELSE")
                        fr.counts.append(0)
                        fr.active = len(fr.counts) - 1
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
                        add_row(contributed)

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
        issues.append(
            Issue(
                "error",
                file_name,
                fr.line,
                f"{array_name}: #if non chiuso ('{fr.condition}')",
            )
        )
        contributed = max(fr.counts) if fr.counts else 0
        add_row(contributed)

    row_count = root.counts[0]

    # Array 1D: ci aspettiamo 1 elemento (una stringa), non 'rows_expr' elementi
    if is_one_d and row_count == 0 and cur_strings:
        row_count = 1

    return row_count, ifdef_sig


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

        row_count, sig = analyze_body(
            arr.body,
            arr.body_start_line,
            width,
            is_one_d,
            arr.name,
            rel,
            issues,
        )
        arr.ifdef_sig = sig

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
        description="Verifica dimensionamento e allineamento tabelle MES_LARHEA_*.c",
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
        "Nota: questo file elenca gli errori delle tabelle MES_LARHEA (dimensioni/allineamento).",
        "Se SourceTree rifiuta il push con GH013 / 'pull request' / 'status check',",
        "quello e' il ruleset GitHub (serve una PR), non necessariamente un errore di questo elenco.",
        "",
        "----------",
        "",
    ]
    path.write_text("\n".join(header + lines) + "\n", encoding="utf-8", errors="replace")


if __name__ == "__main__":
    sys.exit(main())
