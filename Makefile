# open386 — build system (GNU make >= 4.0)
# Recipes use '>' instead of a leading tab so the file survives editors that expand tabs.
.RECIPEPREFIX := >

CC      ?= gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter   # unused-parameter allowed while bodies are stubs (M0)
OPT     ?= -O2 -g
CFLAGS  += $(CSTD) $(WARN) $(OPT) -Isrc -D_POSIX_C_SOURCE=200809L
LDFLAGS +=
LDLIBS  += -lm

BIN_DIR := bin
OBJ_DIR := obj

SRC_DIRS := src/util src/cpu src/mem src/io src/dev src/bios src/machine src/debugger src/ui
SRCS     := $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
LIB_OBJS := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRCS))
MAIN_OBJ := $(OBJ_DIR)/main.o
TARGET   := $(BIN_DIR)/open386

TEST_SRCS := $(wildcard tests/unit/test_*.c)
TEST_BINS := $(patsubst tests/unit/%.c,$(BIN_DIR)/tests/%,$(TEST_SRCS))

.PHONY: all test clean tests dirs

all: $(TARGET) tests

tests: $(TEST_BINS)

$(TARGET): $(MAIN_OBJ) $(LIB_OBJS) | dirs
> $(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: src/%.c | dirs
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -MMD -MP -c -o $@ $<

$(BIN_DIR)/tests/%: tests/unit/%.c $(LIB_OBJS) | dirs
> @mkdir -p $(dir $@)
> $(CC) $(CFLAGS) -Itests/unit -o $@ $< $(LIB_OBJS) $(LDLIBS)

test: tests
> @set -e; for t in $(TEST_BINS); do echo "== $$t"; $$t; done

dirs:
> @mkdir -p $(BIN_DIR) $(OBJ_DIR)

clean:
> rm -rf $(BIN_DIR) $(OBJ_DIR)

-include $(LIB_OBJS:.o=.d) $(MAIN_OBJ:.o=.d)
