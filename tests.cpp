#include "what.h"
#include <gtest/gtest.h>
 
TEST(Factorialtest, PositiveNos) { 
    ASSERT_EQ(6, fact(3));
    ASSERT_EQ(24, fact(4));
}
 
TEST(Factorialtest, Zero) {
    ASSERT_EQ(1, fact(0));
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
