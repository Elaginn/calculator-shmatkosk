#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int float_mode = 0;

typedef struct {
    double values[MAX];
    char operators[MAX];
    int valueTop;
    int operatorTop;
} Stack;

void parse_args(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--float") == 0) {
            float_mode = 1;
        }
    }
}

void initStack(Stack *stack) {
    stack->valueTop = -1;
    stack->operatorTop = -1;
}

void pushValue(Stack *stack, double value) {
    stack->values[++(stack->valueTop)] = value;
}

void pushOperator(Stack *stack, char operator) {
    stack->operators[++(stack->operatorTop)] = operator;
}

double popValue(Stack *stack) {
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

double applyOperator(double a, double b, char operator) {
    switch (operator) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return float_mode ? a / b : (int)(a / b);
        default: return 0;
    }
}

double evaluateExpression(const char* expression) {
    Stack stack;
    initStack(&stack);
    int i = 0;
    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }
        if (isdigit(expression[i])) {
            double value = 0;
            while (isdigit(expression[i]) || (float_mode && expression[i] == '.')) {
                if (expression[i] == '.') {
                    i++;
                    double fraction = 0.1;
                    while (isdigit(expression[i])) {
                        value += (expression[i] - '0') * fraction;
                        fraction /= 10;
                        i++;
                    }
                    break;
                }
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            pushValue(&stack, value);
        } else if (expression[i] == '(') {
            pushOperator(&stack, expression[i]);
            i++;
        } else if (expression[i] == ')') {
            while (stack.operatorTop >= 0 && stack.operators[stack.operatorTop] != '(') {
                double b = popValue(&stack);
                double a = popValue(&stack);
                char op = popOperator(&stack);
                pushValue(&stack, applyOperator(a, b, op));
            }
            popOperator(&stack);
            i++;
        } else if (strchr("+-*/", expression[i])) {
            while (stack.operatorTop >= 0 && precedence(stack.operators[stack.operatorTop]) >= precedence(expression[i])) {
                double b = popValue(&stack);
                double a = popValue(&stack);
                char op = popOperator(&stack);
                pushValue(&stack, applyOperator(a, b, op));
            }
            pushOperator(&stack, expression[i]);
            i++;
        }
    }
    while (stack.operatorTop >= 0) {
        double b = popValue(&stack);
        double a = popValue(&stack);
        char op = popOperator(&stack);
        pushValue(&stack, applyOperator(a, b, op));
    }
    return popValue(&stack);
}

int main(int argc, char *argv[]) {
    parse_args(argc, argv);

    char expression[MAX];
    if (!fgets(expression, MAX, stdin)) return 1;

    double result = evaluateExpression(expression);
    if (float_mode) {
        printf("%lf\n", result);
    } else {
        printf("%d\n", (int)result);
    }
    return 0;
}
