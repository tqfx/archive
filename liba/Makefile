MAKEFLAGS += --silent
MAKEFILE := $(lastword $(MAKEFILE_LIST))
CURDIR := $(subst \,/,$(lastword $(dir $(MAKEFILE_LIST))))

ARFLAGS := rcs
FLAGS += -fPIC -O2 -Wall -Wextra -Wpedantic
CFLAGS += -std=c11 $(FLAGS)
CXXFLAGS += -std=c++11 $(FLAGS)

C_DEFS += -DNDEBUG
CXX_DEFS += -DNDEBUG

STATIC := $(CURDIR)liba.a
SHARED := $(CURDIR)liba.so

DIRS := $(CURDIR) $(CURDIR)crc $(CURDIR)poly $(CURDIR)hash

C_SRCS := $(foreach d,$(DIRS),$(foreach c,c,$(wildcard $(d:/=)/*.$(c))))
CXX_SRCS := $(foreach d,$(DIRS),$(foreach c,cc cxx cpp,$(wildcard $(d:/=)/*.$(c))))

C_OBJS := $(addsuffix .o,$(C_SRCS))
C_DIRS := $(sort $(dir $(C_SRCS)))
C_INCS := $(foreach d,$(C_DIRS),-I$(d:/=))
C_DEPS := $(foreach d,$(C_DIRS),$(foreach h,h,$(wildcard $(d)*.$(h))))
CFLAGS += $(C_DEFS) $(C_INCS)

CXX_OBJS := $(addsuffix .o,$(CXX_SRCS))
CXX_DIRS := $(sort $(dir $(C_SRCS) $(CXX_SRCS)))
CXX_INCS := $(foreach d,$(CXX_DIRS),-I$(d:/=))
CXX_DEPS := $(foreach d,$(CXX_DIRS),$(foreach h,h hh hxx hpp,$(wildcard $(d)*.$(h))))
CXXFLAGS += $(CXX_DEFS) $(CXX_INCS)

all: $(SHARED) $(STATIC)
shared:$(SHARED)
static:$(STATIC)

$(SHARED): $(C_OBJS) $(CXX_OBJS)
	@echo $(CC) $@
	$(CC) -shared -o $@ $^
$(STATIC): $(C_OBJS) $(CXX_OBJS)
	@echo $(AR) $@
	$(AR) $(ARFLAGS) $@ $^

vpath %.c $(C_DIRS)
%.c.o:%.c $(C_DEPS) $(MAKEFILE)
	@echo $(CC) $<
	$(CC) $(CFLAGS) -o $@ -c $<
vpath %.cc $(CXX_DIRS)
%.cc.o:%.cc $(CXX_DEPS) $(MAKEFILE)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<
vpath %.cxx $(CXX_DIRS)
%.cxx.o:%.cxx $(CXX_DEPS) $(MAKEFILE)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<
vpath %.cpp $(CXX_DIRS)
%.cpp.o:%.cpp $(CXX_DEPS) $(MAKEFILE)
	@echo $(CXX) $<
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean help
clean:
	@$(RM) $(C_OBJS) $(CXX_OBJS) $(STATIC) $(SHARED)
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
