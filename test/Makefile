MAKEFLAGS += --silent
CURDIR := $(subst \,/,$(lastword $(dir $(MAKEFILE_LIST))))
BUILD := build
OBJ := $(BUILD)/obj
LIB := $(BUILD)/lib
BIN := $(BUILD)/bin
MK := mkdir

FLAGS += -O2 -Wall -Wextra -Wpedantic
CFLAGS += -std=c11 $(FLAGS)
CXXFLAGS += -std=c++11 $(FLAGS)

LIBA := $(LIB)/liba.a
-include $(CURDIR)../liba/make.mk

C_INCS += $(foreach d,$(CURDIR),-I$(d:/=))
CFLAGS += $(C_DEFS) $(C_INCS) $(LIBA_INCS)

CXX_INCS += $(foreach d,$(CURDIR),-I$(d:/=))
CXXFLAGS += $(CXX_DEFS) $(CXX_INCS) $(LIBA_INCS)

all: $(BIN)/test $(BIN)/math $(BIN)/mean $(BIN)/notefreqs \
     $(BIN)/hash $(BIN)/hmac $(BIN)/base $(BIN)/crc \
     $(BIN)/str $(BIN)/vec $(BIN)/list

$(LIBA): $(LIBA_DEPS) | $(LIB)
	$(MAKE) -f $(CURDIR)../liba/Makefile TARGET=a
$(BIN)/test:$(CURDIR)test.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/math:$(CURDIR)test_math.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/mean:$(CURDIR)test_mean.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/notefreqs:$(CURDIR)test_notefreqs.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/hash:$(CURDIR)test_hash.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/hmac:$(CURDIR)test_hmac.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/base:$(CURDIR)test_base.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/crc:$(CURDIR)test_crc.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/str:$(CURDIR)test_str.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/vec:$(CURDIR)test_vec.cpp $(LIBA) | $(BIN)
	@echo $(CXX) $@
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/list:$(CURDIR)test_list.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ):$(BUILD)
	@$(MK) -p $@
$(LIB):$(BUILD)
	@$(MK) -p $@
$(BIN):$(BUILD)
	@$(MK) -p $@
$(BUILD):
	@$(MK) -p $@

.PHONY: clean help
clean:
	$(RM) -r $(BUILD)
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all \(the default if no target is provided\)
	@echo ... help
	@echo ... clean
