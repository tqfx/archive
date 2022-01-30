MAKEFLAGS += --silent

SOURCE_CLANG += src/crc  include/crc
SOURCE_CLANG += src/poly include/poly
SOURCE_CLANG += src/hash include/hash
SOURCE_CLANG += src      include
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
