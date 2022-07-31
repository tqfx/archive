#!/usr/bin/env python
import sys
import os
import re

DATABASE = os.path.splitext(os.path.abspath(sys.argv[0]))[0]
SCRIPTS = os.path.dirname(os.path.abspath(sys.argv[0]))
ROOT = os.path.abspath(os.path.join(SCRIPTS, ".."))
os.chdir(ROOT)

tables = []
BUILD = "build"
with open(DATABASE, "r", encoding="UTF-8") as f:
    textlines = f.read().split('\n')
for textline in textlines:
    if not textline or ';' in textline[0] or '=' not in textline:
        continue
    values = textline.split('=')
    source = values[0].strip()
    target = '='.join(values[1:]).strip()
    for string in (("\\r", '\r'), ("\\t", '\t'), ("\\n", '\n'), ("\\\\", '\\')):
        source = source.replace(string[0], string[1])
        target = target.replace(string[0], string[1])
    tables.append((source, target))
if not os.path.exists(BUILD) and len(sys.argv) > 1:
    os.mkdir(BUILD)
OUTPUT_H = os.path.basename(DATABASE + ".h")
with open(DATABASE + ".h", "r", encoding="UTF-8") as f:
    text = f.read()
with open(os.path.join(BUILD, OUTPUT_H), "wb") as f:
    f.write(text.encode("UTF-8"))

for input in sys.argv[1:]:
    output = os.path.join(BUILD, os.path.basename(input))

    with open(input, "r", encoding="UTF-8") as f:
        text = f.read()

    for string in tables:
        text = text.replace(string[0], string[-1])

    for string in ("A_PUBLIC ", "A_HIDDEN ", " @ingroup A\n"):
        text = text.replace(string, '')

    for string in (
        ("A_INLINE ", "static inline "),
        ('#include "../a.h"\n', '#include "' + OUTPUT_H + '"\n'),
        ('#include "a.h"\n', '#include "' + OUTPUT_H + '"\n'),
    ):
        text = text.replace(string[0], string[1])

    for result in re.findall(r"([\t\n\*\(\) ])a_(\w*)", text):
        text = text.replace(result[0] + "a_" + result[1], result[0] + result[1])

    for result in re.findall(r"A_(\w*)", text):
        text = text.replace("A_" + result, result)

    with open(output, "wb") as f:
        f.write(text.encode("UTF-8"))

    print(input, "->", output)
