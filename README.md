# An algorithm library {#mainpage}

[![msvc](https://github.com/tqfx/liba/actions/workflows/msvc.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msvc.yml)
[![linux](https://github.com/tqfx/liba/actions/workflows/linux.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/linux.yml)
[![macos](https://github.com/tqfx/liba/actions/workflows/macos.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/macos.yml)
[![mingw](https://github.com/tqfx/liba/actions/workflows/mingw.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/mingw.yml)
[![msys2](https://github.com/tqfx/liba/actions/workflows/msys2.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msys2.yml)
[![freebsd](https://github.com/tqfx/liba/actions/workflows/freebsd.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/freebsd.yml)
[![doxygen](https://github.com/tqfx/liba/actions/workflows/doxygen.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/doxygen.yml)

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

### cmake

```bash
cmake -S . -B build
cmake --build build
cmake --install build
```

### vcpkg

```bash
mkdir -p $VCPKG_INSTALLATION_ROOT/ports/liba
cp vcpkg/* $VCPKG_INSTALLATION_ROOT/ports/liba
vcpkg install liba
```

### conan

```bash
conan create . -s build_type=RelWithDebInfo
```

### cargo

```bash
cargo build --release
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

### CMakeLists.txt

```cmake
find_package(liba CONFIG REQUIRED)
target_link_libraries(<TARGET> PRIVATE liba::a)
```

#### conanfile.txt

```txt
[requires]
liba/0.1
```

### Rust

#### Cargo.toml

```toml
[build-dependencies]
liba = "0.1"
```

#### main.rs

```rs
use a;
fn main() {
    println!("version {}", a::version());
}
```

### python

```py
import a
print("version", a.version())
```

## Copyright {#copyright}

Copyright (C) 2020 tqfx, All rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at https://mozilla.org/MPL/2.0/.
