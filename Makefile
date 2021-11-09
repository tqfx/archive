MAKEFLAGS += --silent

SOURCE_CLANG += liba/crc
SOURCE_CLANG += liba/hash
SOURCE_CLANG += liba/poly
SOURCE_CLANG += liba
SOURCE_CLANG += test
SOURCE_BLACK += test

all: format black

.PHONY: format black clean

SOURCE_C = $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch]))
SOURCE_CC = $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][ch]))
SOURCE_CXX = $(foreach v,$(SOURCE_CLANG),$(wildcard $(v)/*.[ch][xp][xp]))
format: $(SOURCE_C) $(SOURCE_CC) $(SOURCE_CXX)
	@$(foreach v,$^,$(shell clang-format -style=file -i $(v) --verbose))

SOURCE_PY = $(foreach v,$(SOURCE_BLACK),$(wildcard $(v)/*.py))
black: $(SOURCE_PY)
	@$(foreach v,$^,$(shell black -S $(v) --quiet))

clean:
	@-git clean -fdX
