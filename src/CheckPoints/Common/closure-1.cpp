////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing working with C++ closure
/// @details Look into closures in the code and make this test green
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    22.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

TEST(Closure1, Test1) {
    int a1{ 1 };
    int a2{ 2 };

    EXPECT_EQ(a1, /* past the right value here */ 0);
    EXPECT_EQ(a2, /* past the right value here */ 0);

    [&]() {
        ++a1;
        ++a2;
    }();

    EXPECT_EQ(a1, /* past the right value here */ 0);
    EXPECT_EQ(a2, /* past the right value here */ 0);

    [=]() mutable {
        ++a1;
        ++a2;
    }();

    EXPECT_EQ(a1, /* past the right value here */ 0);
    EXPECT_EQ(a2, /* past the right value here */ 0);
}
