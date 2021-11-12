MAKEFLAGS += --silent
MAKEFILE := $(lastword $(MAKEFILE_LIST))
CURDIR := $(subst \,/,$(lastword $(dir $(MAKEFILE_LIST))))
BUILD := build
MK := mkdir

FLAGS += -O2 -Wall -Wextra -Wpedantic
CFLAGS += -std=c11 $(FLAGS)
CXXFLAGS += -std=c++11 $(FLAGS)

-include $(CURDIR)../liba/make.mk
LIBA := $(CURDIR)../liba/liba.a

C_INCS += $(foreach d,$(CURDIR),-I$(d:/=))
CFLAGS += $(C_DEFS) $(C_INCS) $(LIBA_INCS)

CXX_INCS += $(foreach d,$(CURDIR),-I$(d:/=))
CXXFLAGS += $(CXX_DEFS) $(CXX_INCS) $(LIBA_INCS)

all: $(BUILD)/test $(BUILD)/math $(BUILD)/mean $(BUILD)/notefreqs \
     $(BUILD)/hash $(BUILD)/hmac $(BUILD)/base $(BUILD)/crc \
     $(BUILD)/str $(BUILD)/vec $(BUILD)/list

$(BUILD)/test:$(CURDIR)test.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/math:$(CURDIR)test_math.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/mean:$(CURDIR)test_mean.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/notefreqs:$(CURDIR)test_notefreqs.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/hash:$(CURDIR)test_hash.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/hmac:$(CURDIR)test_hmac.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/base:$(CURDIR)test_base.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/crc:$(CURDIR)test_crc.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/str:$(CURDIR)test_str.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/vec:$(CURDIR)test_vec.cpp $(LIBA)
	@echo $(CXX) -o $@
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
$(BUILD)/list:$(CURDIR)test_list.c $(LIBA)
	@echo $(CC) -o $@
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(LIBA): $(LIBA_DEPS) | $(BUILD)
	@$(MAKE) -f $(CURDIR)../liba/Makefile
$(BUILD):
	@$(MK) -p $@

.PHONY: clean help
clean:
	@$(MAKE) -f $(CURDIR)../liba/Makefile clean
	@$(RM) -r $(BUILD)
help:
	@echo The following are some of the valid targets for this $(MAKEFILE):
	@echo ... all \(the default if no target is provided\)
	@echo ... help
	@echo ... clean
