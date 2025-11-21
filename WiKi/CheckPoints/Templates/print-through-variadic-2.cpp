////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing knowledge about C++ type recognition
/// @details Look into unit-tests and implement the `print`-function
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    22.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <utility>
#include <vector>
#include <set>

#include <gtest/gtest.h>

template<class Arg>
void print(const Arg& i_arg) {
    // TODO: may you implement it ?
}

template<class Arg, class... Args>
void print(const Arg& i_arg, const Args&... i_args) {
    print(i_arg);
    print(i_args...);
}

TEST(Templates2, Test1) {
    print(1, 2, 3.3);
    // should be printed: 1, 2, 3.3,
}

TEST(Templates2, Test2) {
    int i{ 5 };
    double d{ 3.14 };
    print(i, d, -15);
    // should be printed: 5, 3.14, -15
}

TEST(Templates2, Test3) {
    std::vector<int> vec{ 1, 2, 3, 4, 5 };
    print(vec);
    // should be printed: 1, 2, 3, 4, 5,
}

TEST(Templates2, Test4) {
    std::vector<int> vec{ 1, 2, 3 };
    std::set<int> set{ 1, 2, 3 };
    print(vec, set, 15);
    // should be printed: 1, 2, 3, 1, 2, 3, 15
}