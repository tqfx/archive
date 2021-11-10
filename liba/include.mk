CWD = $(lastword $(dir $(MAKEFILE_LIST)))
C_INCLUDES += -I$(CWD)
C_INCLUDES += -I$(CWD)crc
C_INCLUDES += -I$(CWD)poly
C_INCLUDES += -I$(CWD)hash
