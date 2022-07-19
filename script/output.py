#!/usr/bin/env python
import sys
import os
import re

SCRIPTS = os.path.dirname(os.path.abspath(sys.argv[0]))
ROOT = os.path.abspath(os.path.join(SCRIPTS, ".."))
os.chdir(ROOT)

BUILD = "build"
if not os.path.exists(BUILD) and len(sys.argv) > 1:
    os.mkdir(BUILD)

for input in sys.argv[1:]:
    output = os.path.join(BUILD, os.path.basename(input))

    with open(input, "r", encoding="UTF-8") as f:
        text = f.read()

    for string in ("A_PUBLIC ", "A_HIDDEN ", " @ingroup A\n"):
        text = text.replace(string, '')

    for string in (
        ("A_INLINE ", "static inline "),
        ('#include "../def.h"\n\n#', '#include <stddef.h>\n#include <stdint.h>\n#'),
        ('#include "def.h"\n\n#', '#include <stddef.h>\n#include <stdint.h>\n#'),
        ('#include "../def.h"\n', '#include <stddef.h>\n#include <stdint.h>\n'),
        ('#include "def.h"\n', '#include <stddef.h>\n#include <stdint.h>\n'),
    ):
        text = text.replace(string[0], string[1])

    for result in re.findall(r"([\n\*\( ])a_(\w*)", text):
        text = text.replace(result[0] + "a_" + result[1], result[0] + result[1])

    for result in re.findall(r"A_(\w*)", text):
        text = text.replace("A_" + result, result)

    with open(output, "wb") as f:
        f.write(text.encode("UTF-8"))

    print(input, "->", output)
