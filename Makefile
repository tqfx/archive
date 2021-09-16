ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

BUILD = build

all: $(BUILD) cython

install:
	-python -m pip install -U -r requirements.txt

cython:
	-python test/setup.py build_ext --inplace

.PHONY: $(BUILD) format clean test

$(BUILD):
	-git submodule update --init --recursive
	-git submodule foreach git checkout .
	-cmake -B $@ -DCMAKE_BUILD_TYPE=Release $(CMAKE_G)
	-cmake --build $@

clean:
	@-git clean -fdX

format: liba
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')

test: cython
	-test/test_polytrack.py
