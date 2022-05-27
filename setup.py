#!/usr/bin/env python
'''
 @file setup.py
 @brief python setup.py build_ext --inplace
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
from glob import glob
from re import findall

suffix_cc = (".c", ".cc", ".cpp", ".cxx", ".c++", ".m", ".mm")
suffix_cy = (".pyx", ".py")

sources = []
sources_cy = []
define_macros = []
with open("setup.cfg", "r", encoding="UTF-8") as f:
    version = findall(r"version = (.*)", f.read())
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
    if suffix not in suffix_cc:
        continue
    sources.append(source)
if version:
    define_macros.append(("a_VERSION", "\"%s\"" % version[0]))
ext_modules = Extension(
    name="a",
    sources=sources,
    include_dirs=["include"],
    define_macros=define_macros,
)


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
