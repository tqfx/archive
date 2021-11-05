# algorithm

[![Deploy](https://github.com/tqfx/liba/actions/workflows/deploy.yml/badge.svg)](https://github.com/tqfx/liba/actions/workflows/deploy.yml)

## required tools

- [msys2](https://www.msys2.org)
- [python](https://www.python.org/downloads)
- [winlibs](https://winlibs.com)
- [tdm-gcc](https://jmeubank.github.io/tdm-gcc/download)
- [Microsoft C++](https://visualstudio.microsoft.com/visual-cpp-build-tools)

## setup

### submodules

```bash
git submodule update --init --recursive
```

### python packages

```bash
python -m pip install -r requirements.txt
```

## build

### debug

```bash
cmake -B build
cmake --build build
```

### release

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### wheel

```bash
python test/setup.py --quiet bdist_wheel
```

### cython

```bash
python test/setup.py --quiet build_ext --inplace
```
