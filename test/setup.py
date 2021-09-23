#!/usr/bin/env python
'''
    python setup.py build_ext --inplace
'''
import os
from sys import argv

script = os.path.abspath(argv[0])
os.chdir(os.path.dirname(script))
if 1 == len(argv):
    exit(os.system("{} build_ext --inplace".format(script)))
del script

from glob import glob
from distutils.core import setup, Extension
from Cython.Build import cythonize


def clean(pyxs):
    for pyx in pyxs:
        prefix = os.path.splitext(pyx)[0]
        for suffix in ('.c', '.cpp'):
            if os.path.exists(prefix + suffix):
                os.remove(prefix + suffix)
    return pyxs


modules = [os.path.abspath("../liba")]

ext_modules = []
source_cpyx = []
for module in modules:
    source_pyx = glob(module + '/*.pyx', recursive=True)
    source_cpyx += clean(source_pyx)
    source_cpp = glob(module + '/*.cpp', recursive=True)
    source_c = glob(module + '/*.c', recursive=True)
    source = source_c + source_cpp + source_pyx
    ext_modules.append(
        Extension(
            name=os.path.basename(os.path.abspath(module)),
            include_dirs=modules,
            sources=source,
        )
    )
del modules

try:
    setup(
        name='liba',
        version='1.0',
        license='MIT',
        author='tqfx',
        author_email='tqfx@foxmail.com',
        url='https://github.com/tqfx/liba',
        description='The algorithm library is based on C language.',
        ext_modules=cythonize(ext_modules, language_level=3, quiet=True),
    )
except Exception as e:
    print(e)
del ext_modules

clean(source_cpyx)
del source_cpyx
