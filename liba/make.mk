CURRENT_DIR = $(lastword $(dir $(MAKEFILE_LIST)))
MAKEFLAGS += --silent
BUILD_DIR = build

TARGET = a

C_SOURCES += $(wildcard $(CURRENT_DIR)*.c)
C_SOURCES += $(wildcard $(CURRENT_DIR)poly/*.c)
C_SOURCES += $(wildcard $(CURRENT_DIR)hash/*.c)

C_INCLUDES += -I$(CURRENT_DIR)
C_INCLUDES += -I$(CURRENT_DIR)poly
C_INCLUDES += -I$(CURRENT_DIR)hash

C_DEFS += -DNDEBUG
CFLAGS += -std=c11 -O2
CFLAGS += -Wall -Wextra -Wpedantic
CFLAGS += $(C_DEFS) $(C_INCLUDES)

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

all: $(BUILD_DIR)/lib$(TARGET).so $(BUILD_DIR)/lib$(TARGET).a

$(BUILD_DIR)/lib$(TARGET).so: $(OBJECTS)
	@echo $(CC) $@
	$(CC) -o $@ -shared $^
$(BUILD_DIR)/lib$(TARGET).a: $(OBJECTS)
	@echo $(AR) $@
	$(AR) -rcs $@ $^
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo $(CC) $^
	$(CC) -o $@ -c $^ -fPIC $(CFLAGS)
$(BUILD_DIR):
	@mkdir $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(BUILD_DIR)/lib$(TARGET).so $(BUILD_DIR)/lib$(TARGET).a
