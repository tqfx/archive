# algorithm {#mainpage}

[![deploy](https://github.com/tqfx/liba/actions/workflows/deploy.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/deploy.yml)
[![msvc](https://github.com/tqfx/liba/actions/workflows/msvc.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msvc.yml)
[![linux](https://github.com/tqfx/liba/actions/workflows/linux.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/linux.yml)
[![macos](https://github.com/tqfx/liba/actions/workflows/macos.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/macos.yml)
[![mingw](https://github.com/tqfx/liba/actions/workflows/mingw.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/mingw.yml)
[![msys2](https://github.com/tqfx/liba/actions/workflows/msys2.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msys2.yml)
[![freebsd](https://github.com/tqfx/liba/actions/workflows/freebsd.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/freebsd.yml)

## required tools

- [msys2](https://www.msys2.org)
- [winlibs](https://winlibs.com)
- [tdm-gcc](https://jmeubank.github.io/tdm-gcc/download)
- [Microsoft C++](https://visualstudio.microsoft.com/visual-cpp-build-tools)

## optional tools

- [python](https://www.python.org/downloads)

## setup

### python packages

```bash
python -m pip install -r requirements.txt
```

## build

### release

```bash
cmake --preset=release
cmake --build --preset=release
```

### debug

```bash
cmake --preset=debug
cmake --build --preset=debug
```

### test

```bash
ctest --preset=debug
```

### wheel

```bash
python test/setup.py --quiet bdist_wheel
```

### cython

```bash
python test/setup.py --quiet build_ext --inplace
```

### Copyright {#copyright}

Copyright (C) 2020 tqfx. All rights reserved.
