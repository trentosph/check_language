#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Checker per i file CSV multilingua in MSG/ (regole MultiLanguage Tool)
e cross-check verso MES_LARHEA_ML.c.

Livelli (come ErrorCsv.cs / ErrorManager.cs):
  1. Cartella  — ML presente, lingue/tabelle note, matrice lingua×tabella
  2. File      — sintassi, indici, placeholder §, size, INFO ML
  3. Confronto — lingue vs ML (righe + placeholder)
  4. Extra     — ogni @Xnnn in MES_LARHEA_ML.c deve esistere in ML-MSGX.csv
                 con stessi parametri (lunghezze INFO == gruppi escape nel .c).
                 Il CSV può avere indici non usati nel .c.
                 Tabella Z obbligatoria nella matrice solo se referenziata nel .c.

Uso:
  python tools/check_msg_csv.py
  python tools/check_msg_csv.py --root .
  python tools/check_msg_csv.py --no-report

Exit code 0 = OK, 1 = errori.
"""
from __future__ import annotations

import argparse
import re
import sys
from collections import defaultdict
from dataclasses import dataclass, field
from pathlib import Path
from typing import Optional


# ---------------------------------------------------------------------------
# Costanti (dizionari del MultiLanguage Tool)
# ---------------------------------------------------------------------------

# Lingue riconosciute (ML = riferimento strutturale)
KNOWN_LANGS = frozenset(
    {
        "BG",
        "CN",
        "CZ",
        "DE",
        "ES",
        "FR",
        "GB",
        "HR",
        "HU",
        "IT",
        "JP",
        "ML",
        "NL",
        "PL",
        "PT",
        "RO",
        "RU",
        "UA",
    }
)

# Tabelle sempre riconosciute a livello cartella (Z gestita a parte, vedi sotto)
KNOWN_TABLES_CORE = frozenset("ABCDEFGHILMNOPQRSTUV")
# Z è valida per naming/size; obbligatoria in matrice solo se presente in MES_LARHEA_ML.c
TABLE_Z = "Z"

# Lunghezza massima per riga di messaggio (MSG_ROW_1 / MSG_ROW_2)
MAX_LEN_BY_TABLE: dict[str, int] = {
    **{t: 16 for t in "ABCDEMNOPQRSTUV"},
    "F": 8,
    "G": 8,
    "H": 5,
    "I": 5,
    "L": 5,
    "Z": 16,  # riconosciuta nel controllo dimensione
}

# Segnaposto CSV (SECTION SIGN U+00A7)
SECTION = "\u00a7"
RE_PLACEHOLDER = re.compile(re.escape(SECTION) + r"([1-8])")
# INFO: "parametro N: K caratteri/carattere" (anche con spazi irregolari)
RE_INFO_PARAM = re.compile(
    r"parametro\s+(\d+)\s*:\s*(\d+)\s*caratter",
    re.IGNORECASE,
)
RE_INFO_COLON_WIDTH = re.compile(r":\s*([1-9]|1[0-6])\s")
RE_MSG_FILE = re.compile(
    r"^(?P<lang>[A-Za-z]{2})-MSG(?P<table>[A-Za-z])(?P<uni>-uni)?\.csv$",
    re.IGNORECASE,
)
RE_ML_ID = re.compile(r"^@([A-Z])(\d{3})$")


@dataclass
class Issue:
    """Singolo errore/warning del checker CSV."""

    severity: str  # "error" | "warning"
    where: str
    message: str
    line: Optional[int] = None

    def format(self) -> str:
        loc = f"{self.where}"
        if self.line is not None:
            loc += f":{self.line}"
        return f"[{self.severity.upper()}] {loc}: {self.message}"


@dataclass
class CsvRow:
    """Una riga messaggio già splittata in campi logici."""

    index: str
    row1: str
    row2: str
    info: str
    raw: str
    line_no: int  # 1-based nel file


@dataclass
class CsvTable:
    """Contenuto di un file <Lang>-MSG<Tab>[-uni].csv."""

    path: Path
    lang: str
    table: str
    rows: list[CsvRow] = field(default_factory=list)


@dataclass
class CMsgRef:
    """Riferimento a un ID @Xnnn estratto da MES_LARHEA_ML.c."""

    msg_id: str
    table: str
    index: int
    param_lens: tuple[int, ...]
    array_name: str
    line: int
    branch_path: str


# ---------------------------------------------------------------------------
# I/O CSV (UTF-16 LE con BOM, tipico export MultiLanguage Tool)
# ---------------------------------------------------------------------------

def read_text_auto(path: Path) -> str:
    """
    Legge un CSV MSG riconoscendo UTF-16 (BOM FF FE / FE FF) o UTF-8.

    Contesto: gli export del tool Windows sono UTF-16 LE; teniamo fallback
    UTF-8 per eventuali file convertiti a mano.
    """
    raw = path.read_bytes()
    if raw.startswith(b"\xff\xfe") or raw.startswith(b"\xfe\xff"):
        return raw.decode("utf-16")
    if raw.startswith(b"\xef\xbb\xbf"):
        return raw.decode("utf-8-sig")
    # Heuristica: molti NUL → probabilmente UTF-16 senza BOM
    if raw[:64].count(0) > 16:
        return raw.decode("utf-16-le")
    return raw.decode("utf-8", errors="replace")


def parse_csv_line_fields(line: str) -> list[str]:
    """
    Estrae i campi tra doppi apici da una riga CSV MSG.

    Conta SOLO i caratteri dentro \"...\". Spazi o altro dopo la \" di
    chiusura (tipico export Excel: ...det\" ) non entrano nel campo e
    quindi non pesano sul controllo SIZE. "" dentro il campo = virgoletta
    escaped.
    """
    fields: list[str] = []
    i = 0
    n = len(line)
    while i < n:
        # Salta separatori / spazi fuori dalle virgolette
        while i < n and line[i] in " \t,":
            i += 1
        if i >= n:
            break
        if line[i] != '"':
            # Campo non quotato (raro nei MSG): leggi fino a virgola/EOL
            start = i
            while i < n and line[i] != ",":
                i += 1
            fields.append(line[start:i].rstrip())
            continue
        # Campo quotato: contenuto strettamente tra " e "
        i += 1  # salta la " di apertura
        buf: list[str] = []
        while i < n:
            ch = line[i]
            if ch == '"':
                # "" → una virgoletta letterale; altrimenti fine campo
                if i + 1 < n and line[i + 1] == '"':
                    buf.append('"')
                    i += 2
                    continue
                i += 1  # salta la " di chiusura; il resto fuori non conta
                break
            buf.append(ch)
            i += 1
        fields.append("".join(buf))
    return fields


def expected_filename(lang: str, table: str) -> str:
    """Nome file atteso per la combinazione lingua/tabella."""
    if lang == "ML":
        return f"ML-MSG{table}.csv"
    return f"{lang}-MSG{table}-uni.csv"


def discover_msg_files(msg_dir: Path) -> tuple[list[tuple[Path, str, str]], list[Issue]]:
    """
    Elenca i CSV validi in MSG/ e segnala naming anomalo (ignorati dal tool originale).

    Ritorna (lista (path, lang, table), issues di naming non bloccanti a parte
    lingua/tabella non riconosciute che invece sono errori di cartella).
    """
    files: list[tuple[Path, str, str]] = []
    issues: list[Issue] = []
    if not msg_dir.is_dir():
        issues.append(
            Issue("error", "MSG/", f"cartella mancante: {msg_dir}")
        )
        return files, issues

    for path in sorted(msg_dir.glob("*.csv")):
        m = RE_MSG_FILE.match(path.name)
        if not m:
            # Livello 0: file fuori schema → ignorati (non errore formale)
            continue
        lang = m.group("lang").upper()
        table = m.group("table").upper()
        has_uni = bool(m.group("uni"))
        # ML senza -uni; altre lingue con -uni
        if lang == "ML" and has_uni:
            continue
        if lang != "ML" and not has_uni:
            continue
        files.append((path, lang, table))
    return files, issues


def load_csv_table(path: Path, lang: str, table: str) -> CsvTable:
    """
    Carica e normalizza un file CSV (salta righe vuote / senza virgola).

    Campi mancanti → riempiti con spazio (come il tool originale).
    """
    text = read_text_auto(path)
    out = CsvTable(path=path, lang=lang, table=table)
    for line_no, raw in enumerate(text.splitlines(), start=1):
        if not raw.strip():
            continue
        if "," not in raw:
            continue
        fields = parse_csv_line_fields(raw)
        # Pad a 4 colonne: INDEX, ROW1, ROW2, INFO
        while len(fields) < 4:
            fields.append(" ")
        index, row1, row2, info = fields[0], fields[1], fields[2], fields[3]
        out.rows.append(
            CsvRow(
                index=index,
                row1=row1,
                row2=row2,
                info=info,
                raw=raw,
                line_no=line_no,
            )
        )
    return out


# ---------------------------------------------------------------------------
# Helper placeholder / INFO
# ---------------------------------------------------------------------------

def placeholders_in_message(row1: str, row2: str) -> list[int]:
    """Elenco ordinato degli indici §N presenti (con ripetizioni)."""
    text = row1 + row2
    return [int(m.group(1)) for m in RE_PLACEHOLDER.finditer(text)]


def placeholder_counts(row1: str, row2: str) -> dict[int, int]:
    """Conteggio per ogni slot §1..§8 nel messaggio."""
    counts = {k: 0 for k in range(1, 9)}
    for n in placeholders_in_message(row1, row2):
        counts[n] += 1
    return counts


def parse_info_params(info: str) -> dict[int, int]:
    """
    Estrae {N: K} da INFO tipo 'parametro 1: 3 caratteri; parametro 2: 5 …'.

    Contesto size/congruenza: K è la larghezza che sostituisce §N (2 char).
    """
    result: dict[int, int] = {}
    for m in RE_INFO_PARAM.finditer(info or ""):
        n = int(m.group(1))
        k = int(m.group(2))
        if 1 <= n <= 8:
            result[n] = k
    return result


def effective_row_len(text: str, info_params: dict[int, int]) -> int:
    """
    Lunghezza effettiva di una riga: ogni §N contato come K (da INFO), non 2.

    Se §N non ha K in INFO, resta lunghezza letterale (2).
    """
    def repl(m: re.Match[str]) -> str:
        n = int(m.group(1))
        k = info_params.get(n)
        if k is None:
            return m.group(0)  # non sostituito
        return " " * k

    return len(RE_PLACEHOLDER.sub(repl, text))


def info_has_param_keywords(info: str) -> bool:
    """True se INFO contiene le keyword del formato tool ('parametr' + 'caratter')."""
    low = (info or "").lower()
    return "parametr" in low and "caratter" in low


def check_info_format(info: str) -> bool:
    """
    Validazione formato INFO (solo ML, se non vuota).

    Allinea le regole documentate:
    - keyword parametr + caratter
    - #':' == #"parametr"
    - #';' == #parametr - 1
    - #"caratter" == #parametr
    - pattern ': K ' (K=1..16) == #caratter
    """
    if not (info or "").strip():
        return True
    low = info.lower()
    if "parametr" not in low or "caratter" not in low:
        return False
    n_parametr = low.count("parametr")
    n_caratter = low.count("caratter")
    n_colon = info.count(":")
    n_semi = info.count(";")
    if n_colon != n_parametr:
        return False
    if n_semi != n_parametr - 1:
        return False
    if n_caratter != n_parametr:
        return False
    n_widths = len(RE_INFO_COLON_WIDTH.findall(info))
    if n_widths != n_caratter:
        return False
    return True


# ---------------------------------------------------------------------------
# Livello 1 — Cartella
# ---------------------------------------------------------------------------

def check_folder(
    files: list[tuple[Path, str, str]],
    tables_required: set[str],
) -> list[Issue]:
    """
    Controlli a livello cartella MSG/.

    tables_required: tabelle che devono comparire per ogni lingua
    (core + Z solo se referenziata in MES_LARHEA_ML.c).
    """
    issues: list[Issue] = []
    by_lang: dict[str, set[str]] = defaultdict(set)
    tables_seen: set[str] = set()
    langs_seen: set[str] = set()

    for _path, lang, table in files:
        langs_seen.add(lang)
        tables_seen.add(table)
        by_lang[lang].add(table)

    if "ML" not in langs_seen:
        issues.append(Issue("error", "MSG/", "Missing all ML .csv file"))

    # Tabelle riconosciute = core + Z (Z sempre ok a livello naming)
    known_tables = KNOWN_TABLES_CORE | {TABLE_Z}
    for tab in sorted(tables_seen):
        if tab not in known_tables:
            issues.append(
                Issue("error", "MSG/", f'Tab "{tab}" not recognize')
            )

    for lang in sorted(langs_seen):
        if lang not in KNOWN_LANGS:
            issues.append(
                Issue("error", "MSG/", f"language {lang} not recognize")
            )

    # Matrice completa solo se non ci sono già errori di riconoscimento
    if issues:
        return issues

    langs_for_matrix = sorted(langs_seen & KNOWN_LANGS)
    for lang in langs_for_matrix:
        for tab in sorted(tables_required):
            if tab not in by_lang.get(lang, set()):
                issues.append(
                    Issue(
                        "error",
                        "MSG/",
                        f"Missing file: {expected_filename(lang, tab)}",
                    )
                )
    return issues


# ---------------------------------------------------------------------------
# Livello 2 — Singolo file
# ---------------------------------------------------------------------------

def check_quotes_commas(row: CsvRow, file_label: str, issues: list[Issue]) -> None:
    """
    Controlli QUOTE ERROR / COMMA ERROR sulla riga grezza.

    Atteso: 8 virgolette + 3 separatori \"\",\" se INFO stile parametr/caratter,
    altrimenti 6 virgolette + 2 separatori.
    """
    raw = row.raw
    n_quotes = raw.count('"')
    # Separatore tipico tra campi quotati
    n_sep = raw.count('","')
    wants_info = info_has_param_keywords(raw)
    exp_quotes = 8 if wants_info else 6
    exp_sep = 3 if wants_info else 2

    if n_quotes != exp_quotes:
        issues.append(
            Issue(
                "error",
                file_label,
                f'QUOTE ERROR: missing or wrong position at msg index '
                f'(Message: "{row.row1}|{row.row2}")',
                line=row.line_no,
            )
        )
        return  # COMMA solo se quote OK (come tool originale)

    if n_sep != exp_sep:
        issues.append(
            Issue(
                "error",
                file_label,
                f'COMMA ERROR: missing or wrong position at msg index '
                f'(Message: "{row.row1}|{row.row2}")',
                line=row.line_no,
            )
        )


def check_message_index(table: CsvTable, issues: list[Issue]) -> None:
    """
    MESSAGE INDEX: riga i → INDEX == (i+1) a 3 cifre.

    Trim sul campo INDEX (export Excel a volte lascia spazi), poi confronta.
    Segnala il primo fuori sequenza e interrompe su quella tabella.
    """
    label = table.path.name
    for i, row in enumerate(table.rows):
        expected = f"{i + 1:03d}"
        got = (row.index or "").strip()
        if got != expected:
            issues.append(
                Issue(
                    "error",
                    label,
                    f"MESSAGE INDEX: atteso {expected}, trovato {row.index!r}",
                    line=row.line_no,
                )
            )
            return


def check_placeholders_single(row: CsvRow, file_label: str, issues: list[Issue]) -> None:
    """DUPLICATE / MISSING PLACEHOLDER INDEX su una riga."""
    msg = f'(Message: "{row.row1}|{row.row2}")'
    counts = placeholder_counts(row.row1, row.row2)
    text = row.row1 + row.row2

    for n, c in counts.items():
        if c > 1:
            issues.append(
                Issue(
                    "error",
                    file_label,
                    f"DUPLICATE PLACEHOLDER: placeholder {SECTION}{n} {msg}",
                    line=row.line_no,
                )
            )

    if SECTION in text:
        # Dopo il primo § deve esserci cifra 1-8
        pos = text.find(SECTION)
        if pos >= 0:
            nxt = text[pos + 1] if pos + 1 < len(text) else ""
            if nxt not in "12345678":
                issues.append(
                    Issue(
                        "error",
                        file_label,
                        f"MISSING PLACEHOLDER INDEX: carattere dopo {SECTION} "
                        f"non valido {msg}",
                        line=row.line_no,
                    )
                )
                return
        present = sorted({n for n, c in counts.items() if c > 0})
        if present:
            expected = list(range(1, max(present) + 1))
            if present != expected:
                issues.append(
                    Issue(
                        "error",
                        file_label,
                        f"MISSING PLACEHOLDER INDEX: indici non consecutivi "
                        f"da 1 ({present}) {msg}",
                        line=row.line_no,
                    )
                )


def check_first_char_equals(row: CsvRow, file_label: str, issues: list[Issue]) -> None:
    """FIRST CHAR NOT ALLOWED: nessun campo (trim) può iniziare con '='."""
    checks = [
        ("Index column", row.index),
        ("Message 1", row.row1),
        ("Message 2", row.row2),
        ("Info column", row.info),
    ]
    for name, val in checks:
        if (val or "").lstrip().startswith("="):
            issues.append(
                Issue(
                    "error",
                    file_label,
                    f"FIRST CHAR NOT ALLOWED IN REFERENCE COLUMN: "
                    f"{name} - {file_label} on index {row.index}",
                    line=row.line_no,
                )
            )


def check_size(
    row: CsvRow,
    table: str,
    file_label: str,
    issues: list[Issue],
    info_params: Optional[dict[int, int]] = None,
) -> None:
    """
    SIZE ERROR: lunghezza effettiva ROW1/ROW2 ≤ massimo tabella.

    info_params: larghezze §N. Per i file lingua (senza colonna INFO) si
    passano i parametri del corrispondente rigo ML — altrimenti §N resterebbe
    lungo 2 e gonfierebbe falsi overflow (caso tipico CN/JP/…).
    """
    max_len = MAX_LEN_BY_TABLE.get(table)
    if max_len is None:
        issues.append(
            Issue(
                "error",
                file_label,
                f"SIZE ERROR DETECTED IN: table for {table} not recognize: "
                f"check GetMaxLenMessages(), TableNameInCFile(), or .csv file naming",
                line=row.line_no,
            )
        )
        return
    if info_params is None:
        info_params = parse_info_params(row.info)
    for which, text in (("Message 1", row.row1), ("Message 2", row.row2)):
        eff = effective_row_len(text, info_params)
        if eff > max_len:
            over = eff - max_len
            issues.append(
                Issue(
                    "error",
                    file_label,
                    f"SIZE ERROR DETECTED IN: index {row.index} - (+{over}) in {which}",
                    line=row.line_no,
                )
            )


def check_info_ml(row: CsvRow, file_label: str, issues: list[Issue]) -> None:
    """INFO ERROR + INCONGRUENCE MSG AND INFO (solo file ML)."""
    info = row.info or ""
    if info.strip() and not check_info_format(info):
        issues.append(
            Issue(
                "error",
                file_label,
                f'INFO ERROR: info column (Message: "{row.row1}|{row.row2}")',
                line=row.line_no,
            )
        )

    info_params = parse_info_params(info)
    counts = placeholder_counts(row.row1, row.row2)
    for k in range(1, 9):
        in_info = k in info_params
        in_msg = counts.get(k, 0) > 0
        if in_info != in_msg:
            issues.append(
                Issue(
                    "error",
                    file_label,
                    f"INCONGRUENCE MSG AND INFO: placeholder {SECTION}{k} "
                    f'(Message: "{row.row1}|{row.row2}")',
                    line=row.line_no,
                )
            )


def check_single_table(
    table: CsvTable,
    issues: list[Issue],
    ml_tables: Optional[dict[str, CsvTable]] = None,
) -> None:
    """Esegue tutti i controlli di livello 2 su un file."""
    label = table.path.name
    ml = (ml_tables or {}).get(table.table) if table.lang != "ML" else None

    for row in table.rows:
        check_quotes_commas(row, label, issues)
    check_message_index(table, issues)
    for i, row in enumerate(table.rows):
        check_placeholders_single(row, label, issues)
        check_first_char_equals(row, label, issues)
        # Lingue: eredita INFO dal rigo ML stesso indice (riferimento strutturale)
        info_params = parse_info_params(row.info)
        if ml is not None and i < len(ml.rows):
            info_params = parse_info_params(ml.rows[i].info)
        check_size(row, table.table, label, issues, info_params=info_params)
        if table.lang == "ML":
            check_info_ml(row, label, issues)


# ---------------------------------------------------------------------------
# Livello 3 — Confronto lingua vs ML
# ---------------------------------------------------------------------------

def check_compare_with_ml(
    ml_tables: dict[str, CsvTable],
    lang_tables: dict[tuple[str, str], CsvTable],
    issues: list[Issue],
) -> None:
    """
    ROW / PLACEHOLDER MISALIGNMENT WITH ML.

    Per ogni tabella in comune: stesso numero di righe e stessi conteggi §N.
    """
    for (lang, tab), lang_tbl in sorted(lang_tables.items()):
        if lang == "ML":
            continue
        ml = ml_tables.get(tab)
        if ml is None:
            continue
        if len(ml.rows) != len(lang_tbl.rows):
            issues.append(
                Issue(
                    "error",
                    lang_tbl.path.name,
                    f"ROW MISALIGNMENT WITH ML: "
                    f"ML={len(ml.rows)} vs {lang}={len(lang_tbl.rows)}",
                )
            )
        n = min(len(ml.rows), len(lang_tbl.rows))
        for i in range(n):
            ml_row = ml.rows[i]
            lg_row = lang_tbl.rows[i]
            ml_c = placeholder_counts(ml_row.row1, ml_row.row2)
            lg_c = placeholder_counts(lg_row.row1, lg_row.row2)
            for k in range(1, 9):
                if ml_c[k] != lg_c[k]:
                    issues.append(
                        Issue(
                            "error",
                            lang_tbl.path.name,
                            f"PLACEHOLDER MISALIGNMENT WITH ML: "
                            f"index {lg_row.index} placeholder {SECTION}{k} "
                            f"(ML={ml_c[k]} vs {lang}={lg_c[k]})",
                            line=lg_row.line_no,
                        )
                    )


# ---------------------------------------------------------------------------
# Livello 4 — Cross-check MES_LARHEA_ML.c ↔ ML CSV
# ---------------------------------------------------------------------------

def extract_c_msg_refs(root: Path) -> tuple[list[CMsgRef], list[Issue]]:
    """
    Estrae gli ID @Xnnn e le lunghezze dei gruppi placeholder da MES_LARHEA_ML.c.

    Riusa il parser di check_language_arrays (stessa semantica escape \\0..\\x0F).
    """
    issues: list[Issue] = []
    ml_path = root / "MES_LARHEA_ML.c"
    lang_def = root / "LANG_DEF.h"
    if not ml_path.exists():
        issues.append(Issue("error", "MES_LARHEA_ML.c", "file mancante"))
        return [], issues
    if not lang_def.exists():
        issues.append(Issue("error", "LANG_DEF.h", "file mancante"))
        return [], issues

    # Import locale: evita dipendenza circolare a livello di package
    tools_dir = str(Path(__file__).resolve().parent)
    if tools_dir not in sys.path:
        sys.path.insert(0, tools_dir)
    import check_language_arrays as arrays  # noqa: WPS433

    parse_issues: list = []
    macros = arrays.parse_lang_def(lang_def)
    ml_arrays = arrays.analyze_file(ml_path, macros, parse_issues)
    refs: list[CMsgRef] = []

    for arr in ml_arrays:
        if arr.prefix != "ML":
            continue
        for el in arr.elements:
            if el.is_macro_only:
                continue
            if arrays._is_exempt_from_ml_id_check(el):
                continue
            prefix = el.msg_id_prefix or ""
            m = RE_ML_ID.match(prefix)
            if not m:
                # Formato ID già coperto dal checker arrays; qui saltiamo
                continue
            table = m.group(1)
            index = int(m.group(2))
            param_lens = tuple(len(g) for g in el.param_groups)
            refs.append(
                CMsgRef(
                    msg_id=prefix,
                    table=table,
                    index=index,
                    param_lens=param_lens,
                    array_name=arr.name,
                    line=el.line,
                    branch_path=el.branch_path,
                )
            )
    return refs, issues


def check_cross_ml_c(
    ml_tables: dict[str, CsvTable],
    c_refs: list[CMsgRef],
    issues: list[Issue],
) -> None:
    """
    Ogni @Xnnn del .c deve esistere nel CSV ML della tabella X.

    Inoltre le lunghezze parametro (INFO) devono coincidere con i gruppi
    escape consecutivi nel .c. Indici CSV non usati nel .c → ammessi.
    """
    # Indice rapido CSV: (tabella, indice_int) → riga
    csv_index: dict[tuple[str, int], CsvRow] = {}
    for tab, tbl in ml_tables.items():
        for row in tbl.rows:
            try:
                idx = int(row.index)
            except ValueError:
                continue
            csv_index[(tab, idx)] = row

    for ref in c_refs:
        key = (ref.table, ref.index)
        row = csv_index.get(key)
        branch = f" ramo='{ref.branch_path}'" if ref.branch_path else ""
        if row is None:
            issues.append(
                Issue(
                    "error",
                    "MES_LARHEA_ML.c",
                    f"{ref.array_name}: ID {ref.msg_id} assente in "
                    f"ML-MSG{ref.table}.csv{branch}",
                    line=ref.line,
                )
            )
            continue

        info_params = parse_info_params(row.info)
        # Ordine parametri = §1, §2, … presenti (consecutivi da 1)
        counts = placeholder_counts(row.row1, row.row2)
        present = [k for k in range(1, 9) if counts[k] > 0]
        csv_lens = tuple(info_params.get(k, 0) for k in present)

        if csv_lens != ref.param_lens:
            issues.append(
                Issue(
                    "error",
                    "MES_LARHEA_ML.c",
                    f"{ref.array_name}: {ref.msg_id} placeholder "
                    f"C={list(ref.param_lens)} vs CSV INFO={list(csv_lens)} "
                    f"(index CSV {row.index}){branch}",
                    line=ref.line,
                )
            )


def tables_required_from_c(c_refs: list[CMsgRef]) -> set[str]:
    """
    Tabelle obbligatorie in MSG/: sempre le core; Z solo se usata nel .c.

    Così Z può restare nei CSV anche senza essere nel firmware, ma se il
    .c referenzia @Znnn allora ML-MSGZ + tutte le lingue devono esserci.
    """
    required = set(KNOWN_TABLES_CORE)
    if any(r.table == TABLE_Z for r in c_refs):
        required.add(TABLE_Z)
    return required


# ---------------------------------------------------------------------------
# Orchestrazione
# ---------------------------------------------------------------------------

def run_checks(root: Path) -> list[Issue]:
    """Esegue i 4 livelli e restituisce la lista issues (errori)."""
    issues: list[Issue] = []
    msg_dir = root / "MSG"

    files, disc_issues = discover_msg_files(msg_dir)
    issues.extend(disc_issues)

    # Cross-ref .c subito: serve per sapere se Z è obbligatoria in cartella
    c_refs, c_issues = extract_c_msg_refs(root)
    issues.extend(c_issues)
    required_tables = tables_required_from_c(c_refs)

    # --- Livello 1 ---
    folder_issues = check_folder(files, required_tables)
    issues.extend(folder_issues)

    # Carichiamo comunque i file presenti (anche se la matrice è incompleta)
    # così livello 2/4 restano utili in diagnostica.
    loaded: list[CsvTable] = []
    for path, lang, table in files:
        if table not in (KNOWN_TABLES_CORE | {TABLE_Z}):
            continue
        if lang not in KNOWN_LANGS:
            continue
        try:
            loaded.append(load_csv_table(path, lang, table))
        except Exception as exc:  # noqa: BLE001 — report come errore file
            issues.append(
                Issue("error", path.name, f"lettura/parsing fallita: {exc}")
            )

    ml_tables = {t.table: t for t in loaded if t.lang == "ML"}
    lang_tables = {(t.lang, t.table): t for t in loaded}

    # --- Livello 2 ---
    # Eseguiamo sempre i controlli file (anche se la matrice cartella è KO)
    # per massimizzare la diagnostica nel report CI.
    # Prima i ML: servono come INFO di riferimento per la size delle lingue.
    for tbl in loaded:
        if tbl.lang == "ML":
            check_single_table(tbl, issues, ml_tables=ml_tables)
    for tbl in loaded:
        if tbl.lang != "ML":
            check_single_table(tbl, issues, ml_tables=ml_tables)

    # --- Livello 3 ---
    check_compare_with_ml(ml_tables, lang_tables, issues)

    # --- Livello 4: cross-check .c ↔ ML CSV ---
    check_cross_ml_c(ml_tables, c_refs, issues)

    return issues


def find_repo_root(start: Path) -> Path:
    cur = start.resolve()
    for p in [cur, *cur.parents]:
        if (p / "MSG").is_dir() and (p / "MES_LARHEA_ML.c").exists():
            return p
    return start.resolve()


def _write_report(path: Path, lines: list[str], failed: bool) -> None:
    from datetime import datetime, timezone

    header = [
        "=== check_msg_csv report ===",
        f"Data (UTC): {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M:%S')}",
        f"Esito: {'FAIL' if failed else 'OK'}",
        "",
        "Nota: errori CSV in MSG/ (cartella/file/confronto ML) e cross-check "
        "ID @Xnnn / placeholder verso MES_LARHEA_ML.c.",
        "",
        "----------",
        "",
    ]
    path.write_text(
        "\n".join(header + lines) + "\n", encoding="utf-8", errors="replace"
    )


def main(argv: Optional[list[str]] = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
        sys.stderr.reconfigure(encoding="utf-8", errors="replace")

    parser = argparse.ArgumentParser(
        description=(
            "Verifica i CSV in MSG/ (regole MultiLanguage Tool) "
            "e il collegamento con gli ID @Xnnn di MES_LARHEA_ML.c"
        ),
    )
    parser.add_argument("--root", type=Path, default=None)
    parser.add_argument(
        "--report",
        type=Path,
        default=None,
        help="Report .txt (default: <root>/check_msg_csv_report.txt)",
    )
    parser.add_argument(
        "--no-report",
        action="store_true",
        help="Non scrivere il file di report",
    )
    args = parser.parse_args(argv)

    root = args.root or find_repo_root(Path(__file__).parent)
    report_path = args.report or (root / "check_msg_csv_report.txt")

    lines: list[str] = []

    def out(msg: str = "") -> None:
        print(msg)
        lines.append(msg)

    out(f"Root: {root}")
    out(f"Cartella: {root / 'MSG'}")
    out(f"Cross-check: MES_LARHEA_ML.c")
    out()

    issues = run_checks(root)
    errors = [i for i in issues if i.severity == "error"]
    warnings = [i for i in issues if i.severity == "warning"]

    # Limita lo spam a console: primi N + riepilogo
    max_print = 200
    for i, issue in enumerate(issues):
        if i >= max_print:
            out(f"... altri {len(issues) - max_print} problemi omessi in console "
                f"(vedi report completo)")
            break
        out(issue.format())

    out()
    out(f"Riepilogo CSV: {len(errors)} errori, {len(warnings)} warning")
    failed = bool(errors)
    out("FAIL" if failed else "OK")

    if not args.no_report:
        # Nel report file mettiamo TUTTI gli issues
        report_lines = [i.format() for i in issues] + [
            "",
            f"Riepilogo CSV: {len(errors)} errori, {len(warnings)} warning",
            "FAIL" if failed else "OK",
        ]
        _write_report(report_path, report_lines, failed=failed)
        print(f"\nReport scritto in: {report_path}")

    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
