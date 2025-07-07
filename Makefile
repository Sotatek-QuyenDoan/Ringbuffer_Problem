.PHONY: all test clean

# 1) Compiler
CC       := gcc
CXX      := g++
#CFLAGS   := -Wall -Wextra -Isource -pthread
#CXXFLAGS := -Wall -Wextra -Isource -pthread
CFLAGS   := -Wall -Wextra -Isource -pthread --coverage
CXXFLAGS := -Wall -Wextra -Isource -pthread --coverage


# 2) Directories
SRCDIR    := source
TESTDIR   := test
BUILDDIR  := build

# 3) Sources
MAIN_SRC := main.c
LIB_SRC  := $(SRCDIR)/ringbuffer.c
TEST_SRC := $(TESTDIR)/ringbuffer_test.cpp

# 4) Objects
MAIN_OBJ := $(BUILDDIR)/main.o
LIB_OBJ  := $(BUILDDIR)/ringbuffer.o
TEST_OBJ := $(BUILDDIR)/ringbuffer_test.o

# 5) Targets
APP       := $(BUILDDIR)/ringbuffer_app
TEST_BIN  := $(BUILDDIR)/test_runner
#GTEST_LIBS := -lgtest -lgtest_main -pthread
GTEST_LIBS := /usr/src/googletest/googletest/lib/libgtest.a /usr/src/googletest/googletest/lib/libgtest_main.a -pthread

# -------------------------------------------------------------------
# Default: build app only
all: $(APP)

# Link app
$(APP): $(MAIN_OBJ) $(LIB_OBJ) | $(BUILDDIR)
	$(CC) $(CFLAGS) $^ -o $@

# Compile main
$(MAIN_OBJ): $(MAIN_SRC) | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile library
$(LIB_OBJ): $(LIB_SRC) | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------------------------------------------------
# Build & run tests
test: $(TEST_BIN)
	@echo "==> Running unit tests..."
	./$(TEST_BIN)

# Link test runner: library + test.o + GTest
$(TEST_BIN): $(TEST_OBJ) $(LIB_OBJ) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_LIBS)

# Compile test.cpp
$(TEST_OBJ): $(TEST_SRC) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# -------------------------------------------------------------------
# Ensure build directory exists
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Clean all
clean:
	rm -rf $(BUILDDIR)
