#!/usr/bin/env python
import sys
import os

if len(sys.argv) < 2:
    exit()

SCRIPTS = os.path.dirname(os.path.abspath(sys.argv[0]))
ROOT = os.path.abspath(os.path.join(SCRIPTS, ".."))
os.chdir(ROOT)

BUILD = "build"
if not os.path.exists(BUILD) and len(sys.argv) > 1:
    os.mkdir(BUILD)

with open(sys.argv[1], "r", encoding="UTF-8") as f:
    lines = f.read().split('\n')
tables = []
for line in lines:
    if '=' not in line:
        continue
    values = line.split('=')
    source = values[0].strip()
    target = ""
    for value in values[1:]:
        target += value + "="
    target = target[:-1].strip()
    for string in (
        ("\\r", '\r'),
        ("\\t", '\t'),
        ("\\n", '\n'),
        ("\\\\", '\\'),
    ):
        target = target.replace(string[0], string[1])
    tables.append((source, target))

NAME = os.path.splitext(os.path.basename(sys.argv[1]))[0]

for input in sys.argv[2:]:
    source = os.path.basename(input)
    define = os.path.splitext(source)[0]
    suffix = os.path.splitext(source)[-1]
    output = os.path.join(BUILD, NAME + suffix)

    with open(input, "r", encoding="UTF-8") as f:
        text = f.read()

    stddef = '''#include <stddef.h>\n#include <stdint.h>\n#undef __include__\n
#undef __cast__
#undef __null__
#if defined(__cplusplus)
#define __null__ nullptr
#define __cast__(T, ...) static_cast<T>(__VA_ARGS__)
#else /* !__cplusplus */
#define __cast__(T, ...) (T)(__VA_ARGS__)
#define __null__ NULL
#endif /* __cplusplus */
'''
    for string in (
        ('#include "../__a__.h"\n', stddef),
        ('#include "__a__.h"\n', stddef),
    ):
        text = text.replace(string[0], string[1])

    for string in tables:
        text = text.replace(string[0], string[1])

    for string in ("__public__ ", "__hidden__ "):
        text = text.replace(string, '')

    for string in (
        (define, NAME),
        ("__zero__", "0"),
        ("__failure__", "1"),
        ("__success__", "0"),
        ("__type__", NAME + "_s"),
        (define.upper(), NAME.upper()),
        ("__inline__", "static inline"),
    ):
        text = text.replace(string[0], string[1])

    with open(output, "wb") as f:
        f.write(text.encode("UTF-8"))

    print(input, "->", output)
