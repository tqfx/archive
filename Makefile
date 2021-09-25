ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

all: build wheel

.PHONY: install build format clean test

install:
	-python -m pip install -U -r requirements.txt

build:
	-git submodule update --init --recursive
	-cmake -B $@ -DCMAKE_BUILD_TYPE=Release $(CMAKE_G)
	-cmake --build $@

wheel:
	-python -m pip wheel --use-feature=in-tree-build ./test

clean:
	@-git clean -fdX

format: liba
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')

cython:
	-python test/setup.py build_ext --inplace

test: cython
	-test/test_lpf.py
	-test/test_pid.py
	-test/test_polytrack.py
