MAKEFLAGS += --silent
MAKEFILE := $(lastword $(MAKEFILE_LIST))
CURDIR := $(subst \,/,$(lastword $(dir $(MAKEFILE_LIST))))
BUILD := build
OBJ := $(BUILD)/obj
LIB := $(BUILD)/lib
MK := mkdir
SZ := size

ARFLAGS := rcs
FLAGS += -fPIC -O2 -Wall -Wextra -Wpedantic
CFLAGS += -std=c11 $(FLAGS)
CXXFLAGS += -std=c++11 $(FLAGS)

DIRS := $(CURDIR) $(CURDIR)crc $(CURDIR)poly $(CURDIR)hash

C_DEFS += -DNDEBUG
CXX_DEFS += -DNDEBUG
C_SRCS := $(foreach d,$(DIRS),$(foreach c,c,$(wildcard $(d:/=)/*.$(c))))
CXX_SRCS := $(foreach d,$(DIRS),$(foreach c,cc cxx cpp,$(wildcard $(d:/=)/*.$(c))))

C_DIRS += $(sort $(dir $(C_SRCS)))
C_INCS += $(foreach d,$(C_DIRS),-I$(d:/=))
C_DEPS += $(foreach d,$(C_DIRS),$(foreach h,h,$(wildcard $(d)*.$(h))))
C_OBJS += $(addprefix $(OBJ)/,$(addsuffix .o,$(notdir $(C_SRCS))))
CFLAGS += $(C_DEFS) $(C_INCS)

CXX_DIRS += $(sort $(dir $(CXX_SRCS) $(C_SRCS)))
CXX_INCS += $(foreach d,$(CXX_DIRS),-I$(d:/=))
CXX_DEPS += $(foreach d,$(CXX_DIRS),$(foreach h,h hh hxx hpp,$(wildcard $(d)*.$(h))))
CXX_OBJS += $(addprefix $(OBJ)/,$(addsuffix .o,$(notdir $(CXX_SRCS))))
CXXFLAGS += $(CXX_DEFS) $(CXX_INCS)

STATIC := $(LIB)/lib$(TARGET).a
SHARED := $(LIB)/lib$(TARGET).so

all: $(SHARED) $(STATIC)
shared:$(SHARED)
static:$(STATIC)

size: $(SHARED) $(STATIC)
	@$(SZ) $^
$(SHARED): $(C_OBJS) $(CXX_OBJS) | $(LIB)
	@echo $(CC) $@
	$(CC) -shared -o $@ $^
$(STATIC): $(C_OBJS) $(CXX_OBJS) | $(LIB)
	@echo $(AR) $@
	$(AR) $(ARFLAGS) $@ $^
$(LIB):$(BUILD)
	@$(MK) -p $@

vpath %.c $(C_DIRS)
$(OBJ)/%.c.o:%.c $(C_DEPS) $(MAKEFILE) | $(OBJ)
	@echo $(CC) $<
	$(CC) $(CFLAGS) -o $@ -c $<
vpath %.cc $(CXX_DIRS)
$(OBJ)/%.cc.o:%.cc $(CXX_DEPS) $(MAKEFILE) | $(OBJ)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<
vpath %.cxx $(CXX_DIRS)
$(OBJ)/%.cxx.o:%.cxx $(CXX_DEPS) $(MAKEFILE) | $(OBJ)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<
vpath %.cpp $(CXX_DIRS)
$(OBJ)/%.cpp.o:%.cpp $(CXX_DEPS) $(MAKEFILE) | $(OBJ)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<
$(OBJ):$(BUILD)
	@$(MK) -p $@
$(BUILD):
	@$(MK) -p $@

.PHONY: clean help
clean:
	$(RM) -r $(BUILD)
help:
	@echo The following are some of the valid targets for this $(MAKEFILE):
	@echo ... all \(the default if no target is provided\)
	@echo ... help
	@echo ... size
	@echo ... clean
	@echo ... static
	@echo ... shared
	@echo ... $(STATIC)
	@echo ... $(SHARED)
