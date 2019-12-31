# An algorithm library {#mainpage}

[![msvc](https://github.com/tqfx/a/actions/workflows/msvc.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/msvc.yml)
[![linux](https://github.com/tqfx/a/actions/workflows/linux.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/linux.yml)
[![macos](https://github.com/tqfx/a/actions/workflows/macos.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/macos.yml)
[![mingw](https://github.com/tqfx/a/actions/workflows/mingw.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/mingw.yml)
[![msys2](https://github.com/tqfx/a/actions/workflows/msys2.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/msys2.yml)
[![freebsd](https://github.com/tqfx/a/actions/workflows/freebsd.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/freebsd.yml)
[![doxygen](https://github.com/tqfx/a/actions/workflows/doxygen.yml/badge.svg)](https://github.com/tqfx/a/actions/workflows/doxygen.yml)

## required tools

- C/C++ compiler: [gcc](https://gcc.gnu.org) or [llvm](https://llvm.org) or [msvc](https://visualstudio.microsoft.com/visual-cpp-build-tools) etc
- [cmake](https://cmake.org/download)

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
cmake -S . -B build
cmake --build build
cmake --install build
```

### cython

```bash
python setup.py build_ext --inplace
```

### wheel

```bash
python setup.py bdist_wheel
```

## using

### cmake

```cmake
find_package(a CONFIG REQUIRED)
target_link_libraries(<TARGET> PRIVATE a::a)
```

## Copyright {#copyright}

Copyright (C) 2020 tqfx, All rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at https://mozilla.org/MPL/2.0/.
