#include "gtest/gtest.h"
extern "C" {
#include "../../src/main.c"
}

TEST(CalculatorTest, IntegerAddition) {
    EXPECT_EQ(evaluateExpression("2+2"), 4);
}

TEST(CalculatorTest, IntegerMultiplication) {
    EXPECT_EQ(evaluateExpression("3*3"), 9);
}

TEST(CalculatorTest, FloatMode) {
    float_mode = 1;
    EXPECT_DOUBLE_EQ(evaluateExpression("3.5+2.5"), 6.0);
}
