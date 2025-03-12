import subprocess
import pytest
import os

# Проверяем, что исполняемый файл существует перед запуском тестов
def pytest_configure(config):
    if not os.path.isfile("./build/app.exe"):
        pytest.exit("Ошибка: приложение не скомпилировано!", returncode=1)

# Набор тестов для корректных выражений
valid_cases = [
    ("1+2", "3", False, 0),  
    ("6-4*2", "-2", False, 0),
    ("15/4", "3", False, 0),
    ("(3+6)*2", "18", False, 0),
    ("7-(3+2)", "2", False, 0),
    ("10/(2+3)", "2", False, 0),

    # Варианты с плавающей точкой
    ("4+1", "5.0000", True, 0),
    ("7/4", "1.7500", True, 0),
]

# Набор тестов на ошибки (некорректный ввод)
error_cases = [
    ("2+b", "", False, 3),  # Некорректный символ
    ("10/0", "", False, 1),  # Деление на 0 (целые)
    ("4/0", "", True, 2),  # Деление на 0 (float)
    ("(5+2", "", False, 4),  # Незакрытая скобка
    ("5+3)", "", False, 4),  # Лишняя скобка
]

# Функция для запуска калькулятора с разными параметрами
def run_calculator(input_data, use_float=False):
    cmd = ["./build/app.exe"]
    if use_float:
        cmd.append("--float")

    process = subprocess.Popen(
        cmd,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input=input_data + "\n")
    return process.returncode, stdout.strip(), stderr.strip()

# Тестируем корректные выражения
@pytest.mark.parametrize("input_data,expected_output,use_float,exit_code", valid_cases)
def test_valid_expressions(input_data, expected_output, use_float, exit_code):
    return_code, output, error = run_calculator(input_data, use_float)
    assert return_code == exit_code
    assert error == ""
    assert output == expected_output

# Тестируем ошибочные выражения
@pytest.mark.parametrize("input_data,expected_output,use_float,exit_code", error_cases)
def test_invalid_expressions(input_data, expected_output, use_float, exit_code):
    return_code, output, error = run_calculator(input_data, use_float)
    assert return_code != 0
    assert output == ""

# Проверяем обработку пробелов
def test_whitespace_handling():
    return_code, output, error = run_calculator("   1  +   ( 2 * 3 )   ")
    assert return_code == 0
    assert output == "7"

# Проверяем порядок операций
def test_operator_precedence():
    return_code, output, error = run_calculator("2+4*3")
    assert output == "14"
    return_code, output, error = run_calculator("(2+4)*3")
    assert output == "18"

# Проверяем работу с отрицательными числами
def test_negative_numbers():
    return_code, output, error = run_calculator("0-6-2")
    assert output == "-8"
    return_code, output, error = run_calculator("(0-3/5*2)", True)
    assert output == "-1.2000"

# Проверяем унарные операторы
def test_unary_operators():
    return_code, output, error = run_calculator("-3-2")
    assert return_code != 0
    return_code, output, error = run_calculator("(/5*2)", True)
    assert return_code != 0

