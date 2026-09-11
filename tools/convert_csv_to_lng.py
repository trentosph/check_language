#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Conversione CSV → LNG (logica MultiLanguage Tool / LngManager).

Contesto: dopo i check CSV favorevoli, ogni file lingua
`<LL>-MSG<T>-uni.csv` diventa `<LL>-MSG<T>.lng` in MSG/.
I file ML di riferimento non vengono convertiti.

Formato .lng:
  - blocchi di 36 caratteri (code unit UTF-16) per messaggio
  - ogni blocco = MSG_ROW_1 + "\\n" + MSG_ROW_2, paddato con spazi a 36
  - encoding UTF-16 Big Endian con BOM (come Encoding.BigEndianUnicode .NET)

Uso:
  python tools/convert_csv_to_lng.py
  python tools/convert_csv_to_lng.py --root .
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path
from typing import Optional


# Lunghezza fissa di ogni messaggio nel .lng (LEN_MSG_BIN nel tool originale)
LEN_MSG_BIN = 36

# BOM UTF-16 BE (FE FF): StreamWriter/BigEndianUnicode .NET lo scrive sul file
UTF16_BE_BOM = b"\xfe\xff"


def find_repo_root(start: Path) -> Path:
    """Trova la root del repo (cartella MSG/ + sorgenti messaggi)."""
    cur = start.resolve()
    for p in [cur, *cur.parents]:
        if (p / "MSG").is_dir() and (p / "MES_LARHEA_ML.c").exists():
            return p
    return start.resolve()


def row_to_lng_block(row1: str, row2: str) -> str:
    """
    Costruisce un blocco .lng da una coppia di righe messaggio.

    Contesto: INDEX e INFO restano fuori; Row1 vuota → singolo spazio;
    niente truncate se >= 36 (comportamento attuale del tool).
    """
    if row1 == "":
        row1 = " "
    current = row1 + "\n" + row2
    if len(current) < LEN_MSG_BIN:
        current = current + (" " * (LEN_MSG_BIN - len(current)))
    return current


def csv_table_to_lng_bytes(rows: list[tuple[str, str]]) -> bytes:
    """
    Concatena tutti i blocchi messaggio e li codifica UTF-16 BE + BOM.

    rows: elenco (MSG_ROW_1, MSG_ROW_2) già parsati dal CSV.
    """
    final = "".join(row_to_lng_block(r1, r2) for r1, r2 in rows)
    return UTF16_BE_BOM + final.encode("utf-16-be")


def lng_output_name(lang: str, table: str) -> str:
    """Nome file .lng: senza suffisso -uni (es. IT-MSGA.lng)."""
    return f"{lang}-MSG{table}.lng"


def convert_one_csv(path: Path, lang: str, table: str, out_dir: Path) -> Path:
    """
    Converte un singolo CSV lingua in .lng nella cartella out_dir.

    Riusa il parser di check_msg_csv (stessi CSV UTF-16/UTF-8 già validati).
    """
    tools_dir = str(Path(__file__).resolve().parent)
    if tools_dir not in sys.path:
        sys.path.insert(0, tools_dir)
    import check_msg_csv as csv_check  # noqa: WPS433

    tbl = csv_check.load_csv_table(path, lang, table)
    pairs = [(row.row1, row.row2) for row in tbl.rows]
    data = csv_table_to_lng_bytes(pairs)
    out_path = out_dir / lng_output_name(lang, table)
    out_path.write_bytes(data)
    return out_path


def convert_all(root: Path) -> list[Path]:
    """
    Converte tutti i CSV lingua in MSG/ (esclude ML).

    Ritorna l'elenco dei .lng scritti.
    """
    tools_dir = str(Path(__file__).resolve().parent)
    if tools_dir not in sys.path:
        sys.path.insert(0, tools_dir)
    import check_msg_csv as csv_check  # noqa: WPS433

    msg_dir = root / "MSG"
    files, _issues = csv_check.discover_msg_files(msg_dir)
    written: list[Path] = []
    for path, lang, table in files:
        # ML = solo riferimento strutturale: non produce .lng
        if lang == "ML":
            continue
        written.append(convert_one_csv(path, lang, table, msg_dir))
    return written


def main(argv: Optional[list[str]] = None) -> int:
    if hasattr(sys.stdout, "reconfigure"):
        sys.stdout.reconfigure(encoding="utf-8", errors="replace")
        sys.stderr.reconfigure(encoding="utf-8", errors="replace")

    parser = argparse.ArgumentParser(
        description=(
            "Converte i CSV lingua in MSG/ in file .lng "
            "(UTF-16 BE, blocchi da 36 caratteri)"
        ),
    )
    parser.add_argument("--root", type=Path, default=None)
    args = parser.parse_args(argv)

    root = args.root or find_repo_root(Path(__file__).parent)
    msg_dir = root / "MSG"
    print(f"Root: {root}")
    print(f"Output: {msg_dir}")

    if not msg_dir.is_dir():
        print(f"[ERROR] cartella MSG/ mancante: {msg_dir}", file=sys.stderr)
        return 1

    written = convert_all(root)
    for p in written:
        print(f"  scritto: {p.name} ({p.stat().st_size} byte)")
    print(f"OK: {len(written)} file .lng generati in MSG/")
    return 0


if __name__ == "__main__":
    sys.exit(main())
