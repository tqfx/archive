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
url = "https://github.com/tqfx/a.git"
license = "MPL"

script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if len(argv) < 2:
    exit(Popen([executable, script, "build_ext", "--inplace"]).wait())
from distutils.ccompiler import get_default_compiler
from setuptools import setup, Extension
from Cython.Build import cythonize
from glob import glob

suffix_cc = (".c", ".cc", ".cpp", ".cxx", ".c++", ".m", ".mm")
suffix_cy = (".pyx", ".py")

sources = []
sources_cy = []
include_dirs = ["include"]
define_macros = [("a_VERSION", '"%s"' % (version))]
for source in glob("src/**", recursive=True):
    if not os.path.isfile(source):
        continue
    prefix, suffix = os.path.splitext(source)
    if suffix in suffix_cy:
        sources_cy.append(source)
        for fix in suffix_cc:
            if os.path.exists(prefix + fix):
                os.remove(prefix + fix)
    if suffix in suffix_cc + suffix_cy and os.path.exists(source):
        sources.append(source)
link_args = []
compile_args = []
if get_default_compiler() == "mingw32":
    link_args += [
        "-static-libgcc",
        "-static-libstdc++",
        "-Wl,-Bstatic,--whole-archive",
        "-lwinpthread",
        "-Wl,--no-whole-archive",
    ]
ext_modules = Extension(
    name=name,
    sources=sources,
    include_dirs=include_dirs,
    define_macros=define_macros,
    extra_compile_args=compile_args,
    extra_link_args=link_args,
)
try:
    setup(
        name=name,
        version=version,
        description=description,
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
for pyx in sources_cy:
    prefix = os.path.splitext(pyx)[0]
    for suffix in suffix_cc:
        if os.path.exists(prefix + suffix):
            os.remove(prefix + suffix)
