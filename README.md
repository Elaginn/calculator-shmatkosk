# calculator-shmatkosk

## What Has Been Done
This repository contains a pure C calculator that evaluates arithmetic expressions from standard input. It supports both integer arithmetic and floating-point arithmetic (using the --float flag). The project meets the DZ-3 requirements by including:
- A proper repository structure with directories for source code, unit tests (using GoogleTest), and integration tests (Python).
- Comprehensive unit tests for each function and integration tests for overall functionality.
- A Makefile to build the application, run tests, clean build artifacts, and manage dependencies.
- A .clang-format configuration based on the WebKit style for consistent code formatting.
- Strict compiler flags (-Wall -Wextra -Wpedantic -Werror -std=c11 for C and similar for C++) ensuring high code quality.

## How to Run/Use It
1. **Build the Project:**
   - Run `make all` to compile the application and unit tests.
   - Run `make clean` to remove build artifacts.
2. **Run the Application:**
   - For integer mode:  
     `echo "3 + 5 * 2" | make run-int`
   - For floating-point mode:  
     `echo "5 / 2" | make run-float`
3. **Run Tests:**
   - Unit tests: `make run-unit-test`
   - Integration tests: `make run-integration-tests`

## How It's Made
The calculator is implemented using a two-stack algorithm that processes numbers and operators to evaluate arithmetic expressions. The project structure is as follows:
- **src/** contains the source code (main.c, calculator.c, and calculator.h).
- **tests/unit/** contains unit tests for each function (stack operations, operator precedence, applyOperator, parse_args, evaluateExpression) using GoogleTest.
- **tests/integration/** contains Python tests that simulate end-to-end usage of the calculator.
The build system is managed by a Makefile that defines targets for building the application, running tests, and cleaning up artifacts. Code formatting is standardized via a .clang-format file based on the WebKit style.

