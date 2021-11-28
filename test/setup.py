#!/usr/bin/env python
'''
 @file setup.py
 @brief python setup.py --quiet build_ext --inplace
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
'''
import os
from sys import argv

amodule = ".."
modules = ["src", "src/crc", "src/poly", "src/hash"]

name = "liba"
version = "0.1"
description = "algorithm library based on C language."
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
    exit(os.system("{} --quiet build_ext --inplace".format(script)))
del script
from glob import glob
from setuptools import setup, Extension
from Cython.Build import cythonize


sources = []
source_cpyx = []
for i in range(len(modules)):
    modules[i] = os.path.join(amodule, modules[i])
    modules[i] = os.path.abspath(modules[i])
for module in modules:
    source_pyx = glob(module + "/*.pyx", recursive=True)
    source_cpyx += clean(source_pyx)
    source_cpp = glob(module + "/*.cpp", recursive=True)
    source_c = glob(module + "/*.c", recursive=True)
    sources += source_c + source_cpp + source_pyx
ext_modules = Extension(
    name=name,
    sources=sources,
    include_dirs=modules,
    define_macros=[("_CRT_SECURE_NO_WARNINGS", None)],
)
del amodule
del modules
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
