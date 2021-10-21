CURRENT_DIR = $(lastword $(dir $(MAKEFILE_LIST)))

C_DEFS +=
C_INCLUDES += -I$(CURRENT_DIR)
C_SOURCES += $(wildcard $(CURRENT_DIR)*.c)

C_INCLUDES += -I$(CURRENT_DIR)poly
C_SOURCES += $(wildcard $(CURRENT_DIR)poly/*.c)

C_INCLUDES += -I$(CURRENT_DIR)hash
C_SOURCES += $(wildcard $(CURRENT_DIR)hash/*.c)

CXX_DEFS +=
CXX_INCLUDES += -I$(CURRENT_DIR)
CXX_SOURCES += $(wildcard $(CURRENT_DIR)*.cpp)
