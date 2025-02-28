CC=gcc
CXX=g++
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c11
SRC=src/main.c
BUILD_DIR=build

all: $(BUILD_DIR)/app.exe $(BUILD_DIR)/unit-tests.exe

$(BUILD_DIR)/app.exe: $(SRC)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/unit-tests.exe: tests/unit/test_calc.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) -Wall $^ -o $@ -lgtest -lgtest_main -pthread

clean:
	rm -rf $(BUILD_DIR)

run-int: $(BUILD_DIR)/app.exe
	$(BUILD_DIR)/app.exe

run-float: $(BUILD_DIR)/app.exe
	$(BUILD_DIR)/app.exe --float

run-unit-test: $(BUILD_DIR)/unit-tests.exe
	$(BUILD_DIR)/unit-tests.exe

venv:
	python3 -m venv venv && source venv/bin/activate && pip install pytest

run-integration-tests:
	pytest tests/integration/
