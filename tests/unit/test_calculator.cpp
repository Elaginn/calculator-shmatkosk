#include "calculator.h"
#include "gtest/gtest.h"
#include <string.h>

// Тестирование работы стека: инициализация
TEST(StackTest, InitStack) {
    Stack s;
    initStack(&s);
    EXPECT_EQ(s.valueTop, -1);
    EXPECT_EQ(s.operatorTop, -1);
}

// Тестирование pushValue/popValue
TEST(StackTest, PushPopValue) {
    Stack s;
    initStack(&s);
    pushValue(&s, 3.14);
    pushValue(&s, 2.71);
    EXPECT_DOUBLE_EQ(popValue(&s), 2.71);
    EXPECT_DOUBLE_EQ(popValue(&s), 3.14);
}

// Тестирование pushOperator/popOperator
TEST(StackTest, PushPopOperator) {
    Stack s;
    initStack(&s);
    pushOperator(&s, '+');
    pushOperator(&s, '*');
    EXPECT_EQ(popOperator(&s), '*');
    EXPECT_EQ(popOperator(&s), '+');
}

// Тестирование функции precedence
TEST(FunctionTest, Precedence) {
    EXPECT_EQ(precedence('+'), 1);
    EXPECT_EQ(precedence('-'), 1);
    EXPECT_EQ(precedence('*'), 2);
    EXPECT_EQ(precedence('/'), 2);
    EXPECT_EQ(precedence('x'), 0);  // символ, не являющийся оператором
}

// Тестирование функции applyOperator в целочисленном режиме
TEST(FunctionTest, ApplyOperatorIntegerMode) {
    float_mode = 0;
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '+'), 7);
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '-'), 3);
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '*'), 10);
    // В целочисленном режиме деление приводит к приведению результата к int: (int)(5/2) == 2
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '/'), 2);
}

// Тестирование функции applyOperator в режиме с плавающей точкой
TEST(FunctionTest, ApplyOperatorFloatMode) {
    float_mode = 1;
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '+'), 7);
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '-'), 3);
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '*'), 10);
    // В режиме с плавающей точкой деление дает 2.5
    EXPECT_DOUBLE_EQ(applyOperator(5, 2, '/'), 2.5);
    float_mode = 0; // сброс режима
}

// Тестирование функции parse_args
TEST(FunctionTest, ParseArgs) {
    // Тест без "--float"
    float_mode = 0;
    const char* argv1[] = {"program", "test"};
    parse_args(2, const_cast<char**>(argv1));
    EXPECT_EQ(float_mode, 0);

    // Тест с "--float"
    float_mode = 0;
    const char* argv2[] = {"program", "--float", "other"};
    parse_args(3, const_cast<char**>(argv2));
    EXPECT_EQ(float_mode, 1);
    float_mode = 0; // сброс режима
}

// Тестирование функции evaluateExpression в целочисленном режиме
TEST(FunctionTest, EvaluateExpressionIntegerMode) {
    float_mode = 0;
    EXPECT_EQ((int)evaluateExpression("3 + 2"), 5);
    EXPECT_EQ((int)evaluateExpression("10 - 3"), 7);
    EXPECT_EQ((int)evaluateExpression("4 * 5"), 20);
    EXPECT_EQ((int)evaluateExpression("5 / 2"), 2);  // целочисленное деление
    EXPECT_EQ((int)evaluateExpression("3 + (2 * 4)"), 11);
    EXPECT_EQ((int)evaluateExpression("(3 + 2) * 4"), 20);
}

// Тестирование функции evaluateExpression в режиме с плавающей точкой
TEST(FunctionTest, EvaluateExpressionFloatMode) {
    float_mode = 1;
    EXPECT_DOUBLE_EQ(evaluateExpression("5 / 2"), 2.5);
    EXPECT_DOUBLE_EQ(evaluateExpression("3.0 + 2.0"), 5.0);
    EXPECT_DOUBLE_EQ(evaluateExpression("3.0 + (2 * 4)"), 11.0);
    EXPECT_DOUBLE_EQ(evaluateExpression("3.5 * 2"), 7.0);
    float_mode = 0; // сброс режима
}

