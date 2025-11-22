CC := gcc
CFLAGS := -std=c23 -Wall -Wextra -Iinclude -Itests

SRC_DIR := src
INCLUDE_DIR := include
TEST_DIR := tests
BUILD_DIR := build

SRCS := $(wildcard $(SRC_DIR)/*.c)

UNITY_SRC := $(TEST_DIR)/unity.c
TEST_MAIN := $(TEST_DIR)/test_main.c
TEST_SRCS := $(filter-out $(TEST_MAIN), $(wildcard $(TEST_DIR)/test_*.c))

TEST_BIN := $(BUILD_DIR)/test_alib

.PHONY: all test format clean

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_BIN): $(SRCS) $(UNITY_SRC) $(TEST_MAIN) $(TEST_SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TEST_BIN)

test: $(TEST_BIN)
	./$(TEST_BIN)

format:
	clang-format -i $(INCLUDE_DIR)/*.h $(SRC_DIR)/*.c $(TEST_DIR)/*.c $(TEST_DIR)/*.h

clean:
	rm -rf $(BUILD_DIR)
