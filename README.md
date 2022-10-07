# An algorithm library {#mainpage}

[![conan](https://github.com/tqfx/liba/actions/workflows/conan.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/conan.yml)
[![xmake](https://github.com/tqfx/liba/actions/workflows/xmake.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/xmake.yml)
[![msvc](https://github.com/tqfx/liba/actions/workflows/msvc.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msvc.yml)
[![linux](https://github.com/tqfx/liba/actions/workflows/linux.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/linux.yml)
[![macos](https://github.com/tqfx/liba/actions/workflows/macos.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/macos.yml)
[![mingw](https://github.com/tqfx/liba/actions/workflows/mingw.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/mingw.yml)
[![msys2](https://github.com/tqfx/liba/actions/workflows/msys2.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/msys2.yml)
[![freebsd](https://github.com/tqfx/liba/actions/workflows/freebsd.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/freebsd.yml)
[![doxygen](https://github.com/tqfx/liba/actions/workflows/doxygen.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/doxygen.yml)

## required tools

- C/C++ compiler: [gnu](https://gcc.gnu.org) or [llvm](https://clang.llvm.org) or [msvc](https://visualstudio.microsoft.com/visual-cpp-build-tools) etc

## optional tools

- [lua](https://www.lua.org)
- [java](https://www.oracle.com/java)
- [rust](https://www.rust-lang.org)
- [xmake](https://xmake.io)
- [cmake](https://cmake.org)
- [conan](https://conan.io)
- [vcpkg](https://vcpkg.io)
- [python](https://www.python.org)

## build

### xmake

```bash
xmake f -m release
xmake --build --all
xmake install --all
```

### cmake

```bash
cmake -S . -B build
cmake --build build
cmake --install build
```

### vcpkg

```bash
cmake -S . -B build -DENABLE_VCPKG=ON
```

```bash
cp -r build/vcpkg/* $VCPKG_INSTALLATION_ROOT
```

```pwsh
cp -r -Force build/vcpkg/* $ENV:VCPKG_INSTALLATION_ROOT
```

### conan

```bash
conan create .
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

## usage

### C/C++

#### xmake.lua

```lua
add_requires("a")
```

### CMakeLists.txt

```cmake
find_package(liba CONFIG REQUIRED)
target_link_libraries(<TARGET> PRIVATE liba::a)
```

#### conanfile.txt

```txt
[requires]
liba/[~0.1]
```

### Lua

```lua
local a = require("liba")
print("version", a.version())
```

### Java

```java
import liba.a;
```

### Rust

#### Cargo.toml

```toml
[dependencies]
liba = { git = "https://github.com/tqfx/liba.git" }
```

#### main.rs

```rs
use liba;
fn main() {
    println!("version {}", liba::version());
}
```

### Python

```py
import liba
print("version", liba.version())
```

## Copyright {#copyright}

Copyright (C) 2020-present tqfx, All rights reserved.

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at https://mozilla.org/MPL/2.0/.
