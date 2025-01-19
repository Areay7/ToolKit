#ifdef Testgoogle
#include "gtest/gtest.h"


// 测试用例 1：一个简单的加法测试
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(2 + 2, 4);
}

// 测试用例 2：另一个加法测试
TEST(AdditionTest, HandlesNegativeInput) {
    EXPECT_EQ(-2 + -2, -4);
}

#endif
