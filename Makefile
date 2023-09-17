# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := VimSnake

BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC = clang
CFLAGS := -Wall -Wextra -pedantic 
CFLAGS += -g3
CFLAGS += $(INC_FLAGS)
CFLAGS += -MMD -MP 

CXX = clang++
CXXFLAGS = $(CFLAGS)

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
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

# Compiling C++
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compiling C
$(BUILD_DIR)/%.c.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean: 
	@echo "Clean up"
	@$(RM) -r $(BUILD_DIR) $(T_BUILD_DIR)

.PHONY: format
format:
	clang-format -i $(SRCS)

# aliases
.PHONY: b r f c
b: build
r: run
f: format
c: clean

-include $(DEPS)
