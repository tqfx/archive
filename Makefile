BUILD = build

ifdef MINGW
CMAKE_G = -G "MinGW Makefiles"
endif
ifdef MSYS
CMAKE_G = -G "MSYS Makefiles"
endif
ifndef CMAKE_G
CMAKE_G = -G "Unix Makefiles"
endif

all: $(BUILD) cython

install:
	@-python -m pip install -U -r requirements.txt

cython:
	@-python test/setup.py build_ext --inplace

.PHONY: $(BUILD) format clean test

$(BUILD):
	@cmake -B $@ $(CMAKE_G) -DCMAKE_BUILD_TYPE="Release"
	@cmake --build $@

clean:
	@-git clean -fdX

format: liba
	@-find $^ test -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format --verbose -style=file -i {} \;
	@-black --pyi -S $(shell find $^ test -regex '.*\.\(py\)')

test: cython
	-test/test_polynomial.py
