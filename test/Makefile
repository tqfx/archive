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
LDFLAGS += -lm

LIBA := $(LIB)/liba.a
LIBADIR := $(CURDIR)../liba/

DIRS += $(LIBADIR) $(LIBADIR)crc $(LIBADIR)poly $(LIBADIR)hash

C_INCS += $(foreach d,$(DIRS),-I$(d:/=))
C_DEPS += $(foreach d,$(DIRS),$(wildcard $(d:/=)/*.h))
CFLAGS += $(C_DEFS) $(C_INCS)

CXX_INCS += $(foreach d,$(DIRS),-I$(d:/=))
CXX_DEPS += $(foreach h,.hh .hxx .hpp,$(foreach d,$(DIRS),$(wildcard $(d:/=)/*$(h))))
CXXFLAGS += $(CXX_DEFS) $(CXX_INCS)

all: $(BIN)/test $(BIN)/math $(BIN)/mean $(BIN)/notefreqs \
     $(BIN)/hash $(BIN)/hmac $(BIN)/base \
     $(BIN)/str $(BIN)/vec $(BIN)/list

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
$(BIN)/str:$(CURDIR)test_str.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/vec:$(CURDIR)test_vec.cpp $(LIBA) | $(BIN)
	@echo $(CXX) $@
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
$(BIN)/list:$(CURDIR)test_list.c $(LIBA) | $(BIN)
	@echo $(CC) $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIBA): $(C_DEPS) $(CXX_DEPS)
	$(MAKE) -f $(LIBADIR)Makefile TARGET=a
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
	$(RM) $(BUILD)/lib$(TARGET).so $(BUILD)/lib$(TARGET).a $(C_OBJS) $(CXX_OBJS)
	$(RM) -r $(BUILD)
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all \(the default if no target is provided\)
	@echo ... help
	@echo ... clean
