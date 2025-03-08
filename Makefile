CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c11
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++17
LDFLAGS = -lgtest -lgtest_main -pthread
SRC = src/main.c src/calculator.c
OUT = build/app.exe
TEST_SRC = tests/unit/test_calculator.cpp
TEST_OUT = build/unit-tests.exe
PYTHON_TEST = tests/integration/test_calculator.py

all: $(OUT) $(TEST_OUT)

$(OUT): $(SRC)
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# В этом правиле сначала компилируем тестовый файл и src/calculator.c,
# а затем добавляем флаги линковки
$(TEST_OUT): $(TEST_SRC) src/calculator.c
	mkdir -p build
	$(CXX) $(CXXFLAGS) -Isrc $(TEST_SRC) src/calculator.c -o $(TEST_OUT) $(LDFLAGS)

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

run-integration-tests: $(OUT)
	python3 $(PYTHON_TEST)

