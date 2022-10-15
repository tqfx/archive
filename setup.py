#!/usr/bin/env python
from sys import argv, executable, version_info
from subprocess import Popen
import time
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
        if not self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_compile_args += ["-std=c++11"]
                elif e.language == "c":
                    e.extra_compile_args += ["-std=c11"]
        if self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c":
                    e.extra_compile_args += ["/std:c11"]
        if self.compiler.compiler_type == "mingw32":
            for e in self.extensions:
                e.extra_link_args += [
                    "-static-libgcc",
                    "-static-libstdc++",
                    "-Wl,-Bstatic,--whole-archive",
                    "-lwinpthread",
                    "-Wl,--no-whole-archive",
                ]
        super(Build, self).build_extensions()


source_c, source_cc = [], []
header_h, header_hh = [], []
suffix_c, suffix_cc = (".c",), (".cc", ".cpp", ".cxx")
suffix_h, suffix_hh = (".h",), (".hh", ".hpp", ".hxx")
define_macros = [("A_CONFIG", None), ("A_EXPORTS", None)]
include_dirs = ["build", "include"]
try:
    USE_CYTHON = True
    from Cython.Build import cythonize
except:
    USE_CYTHON = False
if USE_CYTHON and os.path.exists("ffi/python/src/lib.pyx"):
    source_c = ["ffi/python/src/lib.pyx"]
elif os.path.exists("ffi/python/src/lib.c"):
    source_c = ["ffi/python/src/lib.c"]

if not os.path.exists("build"):
    os.mkdir("build")
with open("setup.cfg", "r") as f:
    version = re.findall(r"version = (.+)", f.read())[0]
major, minor, patch = re.findall(r"(\d+).(\d+).(\d+)", version)[0]
tweak = time.strftime("%Y%m%d%H%M")
text = '''/*!
 @file a.config.h
 @brief algorithm library configuration
 @details it is autogenerated by setup.py
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_CONFIG_H
#define LIBA_CONFIG_H

#define A_VERSION "{}"
#define A_VERSION_MAJOR {}
#define A_VERSION_MINOR {}
#define A_VERSION_PATCH {}
#define A_VERSION_TWEAK A_U64_C({})

#endif /* LIBA_CONFIG_H */
'''.format(
    version, major, minor, patch, tweak
)
if not os.path.exists("build/a.config.h"):
    with open("build/a.config.h", "wb") as f:
        f.write(text.encode("UTF-8"))

for source in glob("src/**"):
    if not os.path.isfile(source):
        continue
    prefix, suffix = os.path.splitext(source)
    if suffix in suffix_cc:
        source_cc.append(source)
    elif suffix in suffix_c:
        source_c.append(source)
for header in glob("include/**"):
    if not os.path.isfile(header):
        continue
    prefix, suffix = os.path.splitext(header)
    if suffix in suffix_hh:
        header_hh.append(header)
    elif suffix in suffix_h:
        header_h.append(header)

ext_modules = [
    Extension(
        name="liba",
        language="c",
        sources=source_c,
        include_dirs=include_dirs,
        define_macros=define_macros,
    )
]

if USE_CYTHON:
    from Cython.Build import cythonize

    ext_modules = cythonize(
        ext_modules,
        language_level=version_info[0],
        annotate=True,
        quiet=True,
    )

setup(
    ext_modules=ext_modules,
    cmdclass={"build_ext": Build},
)
