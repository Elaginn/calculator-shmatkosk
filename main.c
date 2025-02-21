#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int values[MAX];
    char operators[MAX];
    int valueTop;
    int operatorTop;
} Stack;

void initStack(Stack *stack) {
    stack->valueTop = -1;
    stack->operatorTop = -1;
}

void pushValue(Stack *stack, int value) {
    stack->values[++(stack->valueTop)] = value;
}

void pushOperator(Stack *stack, char operator) {
    stack->operators[++(stack->operatorTop)] = operator;
}

int popValue(Stack *stack) {
    return stack->values[(stack->valueTop)--];
}

char popOperator(Stack *stack) {
    return stack->operators[(stack->operatorTop)--];
}

int precedence(char operator) {
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    return 0;
}

int applyOperator(int a, int b, char operator) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int evaluateExpression(const char* expression) {
    Stack stack;
    initStack(&stack);
    int i = 0;
    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (isdigit(expression[i])) {
            int value = 0;
            while (isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            pushValue(&stack, value);
        } else if (expression[i] == '(') {
            pushOperator(&stack, expression[i]);
            i++;
        } else if (expression[i] == ')') {
            while (stack.operatorTop >= 0 && stack.operators[stack.operatorTop] != '(') {
                int b = popValue(&stack);
                int a = popValue(&stack);
                char op = popOperator(&stack);
                pushValue(&stack, applyOperator(a, b, op));
            }
            popOperator(&stack);
            i++;
        } else if (expression[i] == '+' || expression[i] == '-' ||
                   expression[i] == '*' || expression[i] == '/') {
            while (stack.operatorTop >= 0 && precedence(stack.operators[stack.operatorTop]) >= precedence(expression[i])) {
                int b = popValue(&stack);
                int a = popValue(&stack);
                char op = popOperator(&stack);
                pushValue(&stack, applyOperator(a, b, op));
            }
            pushOperator(&stack, expression[i]);
            i++;
        }
    }

    while (stack.operatorTop >= 0) {
        int b = popValue(&stack);
        int a = popValue(&stack);
        char op = popOperator(&stack);
        pushValue(&stack, applyOperator(a, b, op));
    }

    return popValue(&stack);
}

int main() {
    char expression[MAX];
    fgets(expression, MAX, stdin);  // Считываем выражение из стандартного ввода

    int result = evaluateExpression(expression);
    printf("%d\n", result);  // Печатаем только результат, как ожидается
    return 0;
}

