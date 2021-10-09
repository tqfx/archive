MAKEFLAGS += --silent
ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

PYTHON = python

all: release wheel

.PHONY: debug release install cython wheel format clean test

debug:
	-git submodule update --init --recursive
	-cmake -B build $(CMAKE_G)
	-cmake --build build

release:
	-git submodule update --init --recursive
	-cmake -B build -DCMAKE_BUILD_TYPE=Release $(CMAKE_G)
	-cmake --build build

install:
	-$(PYTHON) -m pip install -U -r requirements.txt

wheel:
	-$(PYTHON) -m pip wheel ./test --use-feature=in-tree-build

cython:
	-$(PYTHON) test/setup.py build_ext --inplace

clean:
	@-git clean -fdX

format: liba
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;

test: debug cython
	-cd build;bin/math
	-cd build;bin/md5
	-cd build;bin/sha1
	-cd build;bin/sha256
	-cd build;bin/sha512
	-cd build;bin/sha3
	-cd build;bin/tiger
	-cd build;bin/whirl
	-$(PYTHON) test/test_lpf.py
	-$(PYTHON) test/test_pid.py
	-$(PYTHON) test/test_polytrack.py
