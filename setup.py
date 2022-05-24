#!/usr/bin/env python
'''
 @file setup.py
 @brief python setup.py build_ext --inplace
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from sys import argv, executable
from subprocess import Popen
import os

name = "a"
version = "0.1.0"
description = "An algorithm library based on C language."
author = "tqfx"
author_email = "tqfx@foxmail.com"
url = "https://github.com/tqfx/liba.git"
license = "MPL-2.0"

script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if len(argv) < 2:
    exit(Popen([executable, script, "build_ext", "--inplace"]).wait())
from setuptools.command.build_ext import build_ext
from setuptools import setup, Extension
from Cython.Build import cythonize
from glob import glob

suffix_cc = (".c", ".cc", ".cpp", ".cxx", ".c++", ".m", ".mm")
suffix_cy = (".pyx", ".py")

sources = []
sources_cy = []
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
ext_modules = Extension(
    name=name,
    sources=sources,
    include_dirs=["include"],
    define_macros=[("a_VERSION", '"%s"' % (version))],
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
        name=name,
        version=version,
        description=description,
        author=author,
        author_email=author_email,
        url=url,
        license=license,
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
