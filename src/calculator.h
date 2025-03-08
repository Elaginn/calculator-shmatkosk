#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

extern int float_mode;

typedef struct {
    double values[MAX];
    char operators[MAX];
    int valueTop;
    int operatorTop;
} Stack;

void parse_args(int argc, char *argv[]);
void initStack(Stack *stack);
void pushValue(Stack *stack, double value);
void pushOperator(Stack *stack, char op);
double popValue(Stack *stack);
char popOperator(Stack *stack);
int precedence(char op);
double applyOperator(double a, double b, char op);
double evaluateExpression(const char* expression);

#endif // CALCULATOR_H

