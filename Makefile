MAKEFLAGS += --silent

all: format

.PHONY: format clean

format: liba
	@-black -S $(shell find $^ test -regex '.*\.\(py\)')
	@-find $^ test -regex '.*\.\(c\|h\|cxx\|hxx\|cpp\|hpp\)' -exec clang-format --verbose -style=file -i {} \;

clean:
	@-git clean -fdX
