MAKEFLAGS += --silent

SOURCE_CLANG += src/crc
SOURCE_CLANG += src/hash
SOURCE_CLANG += src/poly
SOURCE_CLANG += src
SOURCE_CLANG += test
SOURCE_BLACK += test

all: format black

.PHONY: format black test clean

SOURCE_C := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch]))
SOURCE_CC := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][ch]))
SOURCE_CXX := $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][xp][xp]))
format: $(SOURCE_C) $(SOURCE_CC) $(SOURCE_CXX)
	@$(foreach v,$^,$(shell clang-format -style=file -i $(v) --verbose))

SOURCE_PY := $(foreach v,$(SOURCE_BLACK),$(wildcard $(v)/*.py))
black: $(SOURCE_PY)
	@$(foreach v,$^,$(shell black -S $(v) --quiet))

test:
	$(MAKE) -f src/Makefile
	$(MAKE) -f test/Makefile

clean:
	@-git clean -fdX
