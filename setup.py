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
from Cython.Build import cythonize
from re import findall
from glob import glob


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


headers = []
sources = []
sources_cy = []
define_macros = []
suffix_cy = (".py", ".pyx")
suffix_cc = (".c", ".cc", ".cpp", ".cxx")
suffix_hh = (".h", ".hh", ".hpp", ".hxx")
with open("setup.cfg", "r", encoding="UTF-8") as f:
    version = findall(r"version = (.*)", f.read())
if version:
    define_macros.append(("a_VERSION", '"' + version[0] + '"'))
for source in glob("src/**", recursive=True):
    if not os.path.isfile(source):
        continue
    prefix, suffix = os.path.splitext(source)
    if suffix not in suffix_cy:
        continue
    sources.append(source)
    sources_cy.append(source)
    for suffix in suffix_cc:
        if os.path.exists(prefix + suffix):
            os.remove(prefix + suffix)
for source in glob("src/**", recursive=True):
    if not os.path.isfile(source):
        continue
    prefix, suffix = os.path.splitext(source)
    if suffix in suffix_cc:
        sources.append(source)
for header in glob("include/**", recursive=True):
    if not os.path.isfile(header):
        continue
    prefix, suffix = os.path.splitext(header)
    if suffix in suffix_hh:
        headers.append(header)
ext_modules = Extension(
    name="a",
    sources=sources,
    include_dirs=["include"],
    define_macros=define_macros,
)

try:
    setup(
        cmdclass={"build_ext": Build},
        ext_modules=cythonize(
            ext_modules,
            language_level=3,
            annotate=True,
            quiet=True,
        ),
    )
except Exception as e:
    print(e)

for source in sources_cy:
    prefix, suffix = os.path.splitext(source)
    for suffix in suffix_cc:
        if os.path.exists(prefix + suffix):
            os.remove(prefix + suffix)
