LIBA_CURDIR := $(subst \,/,$(lastword $(dir $(MAKEFILE_LIST))))
LIBA_DIRS += $(LIBA_CURDIR)
LIBA_DIRS += $(LIBA_CURDIR)crc
LIBA_DIRS += $(LIBA_CURDIR)poly
LIBA_DIRS += $(LIBA_CURDIR)hash
LIBA_INCS += $(foreach d,$(LIBA_DIRS),-I$(d:/=))
LIBA_DEPS += $(foreach d,$(LIBA_DIRS),$(foreach c,c cc cxx cpp,$(wildcard $(d:/=)/*.$(c))))
LIBA_DEPS += $(foreach d,$(LIBA_DIRS),$(foreach h,h hh hxx hpp,$(wildcard $(d:/=)/*.$(h))))
LDFLAGS += -lm
