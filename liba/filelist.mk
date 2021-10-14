CURRENT_DIR = $(lastword $(dir $(MAKEFILE_LIST)))
# C sources
C_SOURCES += $(wildcard $(CURRENT_DIR)*.c)
# C includes
C_INCLUDES += -I$(CURRENT_DIR)
# C defines
C_DEFS +=
