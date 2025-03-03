CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17
LDFLAGS = -lgtest -lgtest_main
SRC = src/main.c src/calculator.c
OUT = build/app.exe
TEST_SRC = tests/unit/calculator_test.cpp
TEST_OUT = build/unit-tests.exe
PYTHON_TEST = tests/integration/test_calculator.py

all: $(OUT) $(TEST_OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

$(TEST_OUT): $(TEST_SRC) $(SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TEST_SRC) src/calculator.c -o $(TEST_OUT)

clean:
	rm -rf build/*

run-int: $(OUT)
	./$(OUT)

run-float: $(OUT)
	./$(OUT) --float

run-unit-test: $(TEST_OUT)
	./$(TEST_OUT)

venv:
	python3 -m venv venv && source venv/bin/activate && pip install pytest

run-integration-tests:
	python3 $(PYTHON_TEST)

