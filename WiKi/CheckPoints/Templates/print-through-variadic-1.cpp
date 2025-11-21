////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing working with C++ variadic templates
/// @details Look into unit-tests and implement the `print`-function
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    22.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

template<class... Args>
void print(const Args&... i_args) {
    // TODO: try to implement...
}

/// @brief work with digits
TEST(Templates1, Test1) {
    print(1);
    // should be printed: 1
}

/// @brief work with strings
TEST(Templates1, Test2) {
    print("Hi Align!");
    // should be printed: Hi Align!
}

/// @brief work with digits and strings simultaneously
TEST(Templates1, Test3) {
    print("result is ", 11, "!");
    // should be printed: result is 11!
}
