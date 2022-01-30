#!/usr/bin/env python
'''
 @file setup.py
 @brief python setup.py --quiet build_ext --inplace
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
'''
import os
import subprocess
from sys import argv, executable

root = ".."
srcs = [
    "src",
    "src/crc",
    "src/poly",
    "src/hash",
]
incs = [
    "include",
    "include/crc",
    "include/poly",
    "include/hash",
]

name = "liba"
version = "0.1.0"
description = "The algorithm library based on C language."
long_description = ''
author = "tqfx"
author_email = "tqfx@foxmail.com"
url = "https://github.com/tqfx/liba.git"
license = "MIT"


def clean(pyxs):
    for pyx in pyxs:
        prefix = os.path.splitext(pyx)[0]
        for suffix in (".c", ".cpp"):
            if os.path.exists(prefix + suffix):
                os.remove(prefix + suffix)
    return pyxs


script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if 1 == len(argv):
    exit(
        subprocess.Popen(
            [executable, script, "--quiet", "build_ext", "--inplace"]
        ).wait()
    )
del script
from glob import glob
from setuptools import setup, Extension
from Cython.Build import cythonize


sources = []
source_cpyx = []
for i in range(len(incs)):
    incs[i] = os.path.join(root, incs[i])
    incs[i] = os.path.abspath(incs[i])
for i in range(len(srcs)):
    srcs[i] = os.path.join(root, srcs[i])
    srcs[i] = os.path.abspath(srcs[i])
    incs.append(srcs[i])
for src in srcs:
    source_pyx = glob(src + "/*.pyx", recursive=True)
    source_cpyx += clean(source_pyx)
    source_cpp = glob(src + "/*.cpp", recursive=True)
    source_cxx = glob(src + "/*.cxx", recursive=True)
    source_cc = glob(src + "/*.cc", recursive=True)
    source_c = glob(src + "/*.c", recursive=True)
    sources += source_pyx + source_cpp + source_cxx + source_cc + source_c
ext_modules = Extension(
    name=name,
    sources=sources,
    include_dirs=incs,
    define_macros=[("_CRT_SECURE_NO_WARNINGS", None)],
)
del root
del srcs
del incs
del sources
try:
    setup(
        name=name,
        version=version,
        description=description,
        long_description=long_description,
        author=author,
        author_email=author_email,
        url=url,
        license=license,
        ext_modules=cythonize(
            ext_modules,
            language_level=3,
            annotate=True,
            quiet=True,
        ),
    )
except Exception as e:
    print(e)
del ext_modules
clean(source_cpyx)
del source_cpyx
