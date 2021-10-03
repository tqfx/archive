ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

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
	-python -m pip install -U -r requirements.txt

wheel:
	-python -m pip wheel ./test --use-feature=in-tree-build

cython:
	-python test/setup.py build_ext --inplace

clean:
	@-git clean -fdX

format: liba
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')

test: cython
	-test/test_lpf.py
	-test/test_pid.py
	-test/test_polytrack.py
