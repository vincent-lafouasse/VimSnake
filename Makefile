# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := VimSnake

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS := $(INC_FLAGS)
CFLAGS += -MMD -MP 
CFLAGS += -Wall -Wextra -pedantic 
CFLAGS += -std=c99
CFLAGS += -g3

LDLIBS := -lSDL2 -lSDL2_image

all: build

.PHONY: build
build: $(BUILD_DIR)/$(TARGET_EXEC)

.PHONY: run
run: $(BUILD_DIR)/$(TARGET_EXEC)
	@echo "\nrunning $^ !\n"
	@./$^

# Linking
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo "Linking"
	@$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.c.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	@echo "Clean up"
	@$(RM) -r $(BUILD_DIR) $(T_BUILD_DIR)

.PHONY: format
format:
	clang-format -i $(SRCS)

-include $(DEPS)
