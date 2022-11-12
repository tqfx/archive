#!/usr/bin/env python
from sys import argv, executable
from subprocess import Popen
import os, sys, time

script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if len(argv) < 2:
    exit(Popen([executable, script, "build_ext", "--inplace"]).wait())
try:
    from setuptools.command.build_ext import build_ext
    from setuptools import setup, Extension
except ImportError:
    from distutils.command.build_ext import build_ext
    from distutils.extension import Extension
    from distutils.core import setup
from sys import byteorder
from re import findall
from glob import glob
import ctypes.util
import ctypes


def check_math(define_macros=[]):
    if sys.platform == "win32":
        path_libm = ctypes.util.find_library("ucrtbase")
        if not path_libm:
            path_libm = ctypes.util.find_msvcrt()
    else:
        path_libm = ctypes.util.find_library("m")
    text = "#define A_HAVE_COMPLEX_H 1\n"
    text += "#define A_HAVE_STDINT_H 1\n"
    try:
        libm = ctypes.CDLL(path_libm)
    except:
        return text
    A_REAL_BYTE = 0x08
    for define_macro in define_macros:
        if "A_REAL_BYTE" in define_macro:
            A_REAL_BYTE = int(define_macro[-1])
            break
    for func in (
        "hypot",
        "log1p",
        "atan2",
        "csqrt",
        "cpow",
        "cexp",
        "clog",
        "csin",
        "ccos",
        "ctan",
        "csinh",
        "ccosh",
        "ctanh",
        "casin",
        "cacos",
        "catan",
        "casinh",
        "cacosh",
        "catanh",
    ):
        name = "A_HAVE_" + func.upper()
        if A_REAL_BYTE == 0x10:
            func += 'l'
        if A_REAL_BYTE == 0x04:
            func += 'f'
        try:
            libm[func]
        except:
            continue
        text += "#define %s 1\n" % (name)
    return text


def configure(config, define_macros=[]):
    with open("setup.cfg", "r") as f:
        version = findall(r"version = (.+)", f.read())[0]
    major, minor, patch = findall(r"(\d+).(\d+).(\d+)", version)[0]
    order = {"little": 1234, "big": 4321}.get(byteorder)
    vsize = ctypes.sizeof(ctypes.c_void_p(0))
    tweak = time.strftime("%Y%m%d%H%M")
    check = check_math(define_macros)
    text = '''/*!
@file a.config.h
@brief algorithm library configuration
@details it is autogenerated by setup.py
@copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/
#ifndef LIBA_CONFIG_H
#define LIBA_CONFIG_H
#define A_BYTE_ORDER {}
#define A_SIZE_PTR {}
#define A_VERSION "{}"
#define A_VERSION_MAJOR {}
#define A_VERSION_MINOR {}
#define A_VERSION_PATCH {}
#define A_VERSION_TWEAK A_U64_C({})
{}#endif /* LIBA_CONFIG_H */
'''.format(
        order, vsize, version, major, minor, patch, tweak, check
    )
    with open(config, "wb") as f:
        f.write(text.encode("UTF-8"))


build = "build"
config_h = "a.config.h"
source_c, source_cc = [], []
header_h, header_hh = [], []
suffix_c, suffix_cc = (".c",), (".cc", ".cpp", ".cxx")
suffix_h, suffix_hh = (".h",), (".hh", ".hpp", ".hxx")
define_macros = [("A_HAVE_H", None), ("A_EXPORTS", None)]
include_dirs = [build, "include"]
try:
    USE_CYTHON = True
    from Cython.Build import cythonize
except:
    USE_CYTHON = False
if USE_CYTHON and os.path.exists("ffi/python/src/lib.pyx"):
    source_c = ["ffi/python/src/lib.pyx"]
elif os.path.exists("ffi/python/src/lib.c"):
    source_c = ["ffi/python/src/lib.c"]
with open("ffi/python/src/a/__init__.pxi", "r") as f:
    define_macros += findall(r"DEF (\w+) = (\d+)", f.read())
config = os.path.join(build, config_h)
if not os.path.exists(config):
    if not os.path.exists(build):
        os.mkdir(build)
    configure(config, define_macros)

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
    from sys import version_info

    ext_modules = cythonize(
        ext_modules,
        language_level=version_info[0],
        annotate=True,
        quiet=True,
    )


class Build(build_ext):  # type: ignore
    def build_extensions(self):
        if self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c":
                    e.extra_compile_args += ["/std:c11"]
        if not self.compiler.compiler_type == "msvc":
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_compile_args += ["-std=c++11"]
                elif e.language == "c":
                    e.extra_compile_args += ["-std=c11"]
        if self.compiler.compiler_type == "mingw32":
            self.compiler.define_macro("__USE_MINGW_ANSI_STDIO", 1)
            for e in self.extensions:
                if e.language == "c++":
                    e.extra_link_args += ["-static-libstdc++"]
                e.extra_link_args += ["-static-libgcc"]
                e.extra_link_args += [
                    "-Wl,-Bstatic,--whole-archive",
                    "-lwinpthread",
                    "-Wl,--no-whole-archive",
                ]
        build_ext.build_extensions(self)


setup(
    ext_modules=ext_modules,  # type: ignore
    cmdclass={"build_ext": Build},
)
