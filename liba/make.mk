CWD = $(lastword $(dir $(MAKEFILE_LIST)))
MAKEFLAGS += --silent
BUILD = build

TARGET = a

-include $(CWD)include.mk

C_SOURCES += $(wildcard $(CWD)*.c)
C_SOURCES += $(wildcard $(CWD)crc/*.c)
C_SOURCES += $(wildcard $(CWD)poly/*.c)
C_SOURCES += $(wildcard $(CWD)hash/*.c)

C_DEFS += -DNDEBUG
CFLAGS += -std=c11 -O2
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += $(C_DEFS) $(C_INCLUDES)

OBJECTS += $(addprefix $(BUILD)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

all: $(BUILD)/lib$(TARGET).so $(BUILD)/lib$(TARGET).a

$(BUILD)/lib$(TARGET).so: $(OBJECTS)
	@echo $(CC) $@
	$(CC) -o $@ -shared $^
$(BUILD)/lib$(TARGET).a: $(OBJECTS)
	@echo $(AR) $@
	$(AR) -rcs $@ $^
$(BUILD)/%.o: %.c | $(BUILD)
	@echo $(CC) $^
	$(CC) -o $@ -c $^ -fPIC $(CFLAGS)
$(BUILD):
	@mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(BUILD_DIR)/lib$(TARGET).so $(BUILD_DIR)/lib$(TARGET).a
