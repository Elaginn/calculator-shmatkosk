#include "gtest/gtest.h"
#include "calculator.h"

TEST(CalculatorTest, IntegerAddition) {
    EXPECT_EQ(computeExpression("3 + 2", 0), 5);
}

TEST(CalculatorTest, IntegerMultiplication) {
    EXPECT_EQ(computeExpression("4 * 5", 0), 20);
}

TEST(CalculatorTest, FloatDivision) {
    EXPECT_DOUBLE_EQ(computeExpression("5 / 2", 1), 2.5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

