MAKEFLAGS += --silent

SOURCE_CLANG += include/crc  src/crc
SOURCE_CLANG += include/poly src/poly
SOURCE_CLANG += include/hash src/hash
SOURCE_CLANG += include      src
SOURCE_CLANG += test
SOURCE_BLACK += test

all: format black

.PHONY: format black clean

SOURCE_C := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch]))
SOURCE_CC := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][ch]))
SOURCE_CXX := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][xp][xp]))
format: $(SOURCE_C) $(SOURCE_CC) $(SOURCE_CXX)
	@clang-format -style=file -i $^ --verbose

SOURCE_PY := $(foreach v,$(SOURCE_BLACK),$(wildcard $(v)/*.py))
black: $(SOURCE_PY)
	@black -S $^

clean:
	@-git clean -fdX
