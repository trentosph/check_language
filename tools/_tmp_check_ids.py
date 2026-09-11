# -*- coding: utf-8 -*-
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding="utf-8", errors="replace")
sys.path.insert(0, str(Path(__file__).resolve().parent))

import check_language_arrays as m

issues = []
macros = m.parse_lang_def(Path(__file__).resolve().parents[1] / "LANG_DEF.h")
arrays = m.analyze_file(
    Path(__file__).resolve().parents[1] / "MES_LARHEA_ML.c", macros, issues
)
m.check_ml_message_ids(arrays, issues)
for i in issues:
    if "ID" in i.message or "1240" in i.format() or "B126" in i.message:
        print(i.format())

# Elementi vicino MSP 98
for a in arrays:
    if a.base_name != "MSAP_1":
        continue
    for e in a.elements:
        if 100 <= e.logical_index <= 105 or e.line in (1238, 1239, 1240, 1241):
            print(
                f"idx={e.logical_index} line={e.line} id={e.msg_id_prefix!r} "
                f"macro={e.is_macro_only} prev={e.preview!r}"
            )
