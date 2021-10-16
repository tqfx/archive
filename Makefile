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
	-$(PYTHON) -m pip wheel ./test

cython:
	-$(PYTHON) test/setup.py --quiet build_ext --inplace

clean:
	@-git clean -fdX

format: liba
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;

test: cython debug
	-$(PYTHON) test/test_lpf.py
	-$(PYTHON) test/test_pid.py
	-$(PYTHON) test/test_polytrack.py
	-cd build;bin/test_hash
	-cd build;bin/test_hmac
	-cd build;bin/test_base
	-cd build;bin/test_math
