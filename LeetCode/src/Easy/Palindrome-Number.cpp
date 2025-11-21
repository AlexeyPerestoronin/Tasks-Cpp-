////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `isPalindrome`-method of `Solution`-class
/// @details https://leetcode.com/problems/palindrome-number/
/// Given an integer x, return true if x is palindrome integer.
/// An integer is a palindrome when it reads the same backward as forward.
///
/// Example 1:
///   Input:
///     x = 121
///   Output:
///     true
///   Explanation: 121 reads as 121 from left to right and from right to left.
///
/// Example 2:
///   Input:
///     x = -121
///   Output:
///     false
///
/// Constraints:
///   -2^31 <= x <= 2^31 - 1
///
/// @author  Jon Galaz: jgalaz@aligntech.com
/// @date    26.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = int;
using OutputDataType = bool;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    bool isPalindrome(int x) {
        // implement solution here
        return false;
    }
};

struct TestSolution : Solution, testing::TestWithParam<TestDataType>
{
};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
      // from example
      TestDataType{ InputDataType{ 121 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ -121 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ 10 }, OutputDataType{ false } }
      // additional
      // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    ASSERT_GE(inputData, std::numeric_limits<int>::min());
    ASSERT_LE(inputData, std::numeric_limits<int>::max());
    ASSERT_EQ(isPalindrome(inputData), outputData);
}
} // namespace
