# calculator-shmatkosk
# Алгоритм и основная идея программы

Программа реализует парсер арифметических выражений, используя стековый алгоритм для обработки операторов и операндов.

## Основные шаги работы алгоритма:

### Разбор входного выражения:
- Числа считываются и сохраняются в стеке значений.
- Операторы (`+`, `-`, `*`, `/`) и скобки `(`, `)` сохраняются в стеке операторов.
- Игнорируются пробелы.

### Обработка операторов с учётом приоритета:
- Операторы `*` и `/` выполняются раньше `+` и `-`.
- Если текущий оператор имеет меньший или равный приоритет, вычисляются предыдущие операции.

### Обработка скобок:
- Открывающая скобка `(` просто кладётся в стек операторов.
- Закрывающая `)` инициирует выполнение всех операций внутри неё до `(`.

### Финальный расчёт:
- После разбора выражения оставшиеся операции выполняются последовательно.
- В стеке остаётся только итоговое значение.

---

## Запуск программы

Программа не имеет сторонних зависимостей, кроме `libc`, поэтому для её сборки необходимо просто выполнить команду:

```bash
gcc main.c -o calc.exe
