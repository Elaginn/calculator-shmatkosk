#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 100

// Функции для работы со стеком
void pushNum(int num);
void pushOp(char op);
int popNum();
char popOp();

// Функции для вычислений
int getPrecedence(char op);
int calculate(int x, int y, char op);
void processOp();
int computeExpression(const char* expr);

#endif // CALCULATOR_H
