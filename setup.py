#!/usr/bin/env python
'''
 @file setup.py
 @brief Setup this algorithm library using Cython.
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from sys import argv, executable
from subprocess import Popen
import os

script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if len(argv) < 2:
    exit(Popen([executable, script, "build_ext", "--inplace"]).wait())
from setuptools.command.build_ext import build_ext
from setuptools import setup, Extension
from glob import glob
import re


class Build(build_ext):
    def build_extensions(self):
        if self.compiler.compiler_type == "mingw32":
            for e in self.extensions:
                e.extra_link_args = [
                    "-static-libgcc",
                    "-static-libstdc++",
                    "-Wl,-Bstatic,--whole-archive",
                    "-lwinpthread",
                    "-Wl,--no-whole-archive",
                ]
        super(Build, self).build_extensions()


try:
    from Cython.Build import cythonize

    USE_CYTHON = True
except:
    USE_CYTHON = False

if USE_CYTHON and os.path.exists("cython/a/source.pyx"):
    source_c = ["cython/a/source.pyx"]
else:
    source_c = ["cython/a/source.c"]
if USE_CYTHON and os.path.exists("cython/aa/source.pyx"):
    source_cc = ["cython/aa/source.pyx"]
else:
    source_cc = ["cython/aa/source.cpp"]

define_macros = [("A_EXPORTS", None), ("A_SHARED", None)]
with open("setup.cfg", "r", encoding="UTF-8") as f:
    version = re.findall(r"version = (.*)", f.read())
if version:
    define_macros.append(("A_VERSION", '"' + version[0] + '"'))

header_h = []
header_hh = []
suffix_c = (".c",)
suffix_h = (".h",)
suffix_cc = (".cc", ".cpp", ".cxx")
suffix_hh = (".hh", ".hpp", ".hxx")

for source in glob("src/**", recursive=True):
    if not os.path.isfile(source):
        continue
    prefix, suffix = os.path.splitext(source)
    if suffix in suffix_cc:
        source_cc.append(source)
    if suffix in suffix_c:
        source_c.append(source)
for header in glob("include/**", recursive=True):
    if not os.path.isfile(header):
        continue
    prefix, suffix = os.path.splitext(header)
    if suffix in suffix_hh:
        header_hh.append(header)
    if suffix in suffix_h:
        header_h.append(header)

ext_modules = [
    Extension(
        name="a",
        language="c",
        sources=source_c,
        include_dirs=["include"],
        define_macros=define_macros,
    ),
    Extension(
        name="aa",
        language="c++",
        sources=source_cc,
        include_dirs=["include"],
        define_macros=define_macros,
    ),
]

if USE_CYTHON:
    from Cython.Build import cythonize

    ext_modules = cythonize(
        ext_modules,
        language_level=3,
        annotate=True,
        quiet=True,
    )

try:
    setup(
        ext_modules=ext_modules,
        cmdclass={"build_ext": Build},
    )
except Exception as e:
    print(e)
