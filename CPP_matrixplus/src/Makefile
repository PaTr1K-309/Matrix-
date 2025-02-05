CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Werror -Wpedantic -I.
LDFLAGS := -lcheck -lpthread -lrt -lm -lsubunit
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

SRC_DIR := .
OBJ_DIR := obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cc)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET := s21_matrix_oop.a
TEST_EXEC := test

GTEST_DIR := /usr/src/googletest/googletest
GTEST_LIB := /usr/src/googletest/googletest/build/lib
GTEST_FLAGS := -I$(GTEST_DIR)/include -L$(GTEST_LIB) -lgtest -lgtest_main -pthread

.PHONY: all clean test coverage gcov_report valgrind check clang

all: clean $(TARGET) $(TEST_EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_FILES)
	ar rcs $@ $^

$(TEST_EXEC): $(TARGET) test.cc
	$(CC) $(CFLAGS) test.cc -o $(TEST_EXEC) $(TARGET) $(GTEST_FLAGS)
	./test

clean:
	rm -rf $(TARGET) $(TEST_EXEC) $(OBJ_DIR) gcov_report *.info *.gcda *.gcno

coverage: CFLAGS += $(COVERAGE_FLAGS)
coverage: all

valgrind: $(TEST_EXEC)
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --num-callers=20 ./test

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.h *.cc

clang:
	clang-format -n *.cc *.h -style=Google

gcov_report: coverage
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html
