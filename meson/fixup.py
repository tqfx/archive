#!/usr/bin/env python3
import os, argparse

parser = argparse.ArgumentParser()
parser.add_argument("dst")
parser.add_argument("src", nargs='+')
args = parser.parse_known_args()

if args[0].dst:
    with open(args[0].dst, "r") as f:
        a_have_h = f.read()

    old = "#if defined(A_HAVE_H)"
    for src in args[0].src:
        src = os.path.basename(src)
        new = "#include \"{}\"\n{}".format(src, old)
        a_have_h = a_have_h.replace(old, new)

    with open(args[0].dst, "wb") as f:
        f.write(a_have_h.encode())
