////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `divide`-method of `Solution`-class
/// @details https://leetcode.com/problems/divide-two-integers/
/// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
/// The integer division should truncate toward zero, which means losing its fractional part.
/// For example, 8.345 would be truncated to 8, and-2.7335 would be truncated to - 2.
///
/// Return the quotient after dividing dividend by divisor.
///
///  Note : Assume we are dealing with an environment that could only store integers within the 32- bit signed integer range : [−231, 231 − 1].
///  For this problem, if the quotient is strictly greater than 2^31 - 1, then return 2^31 - 1, and if the quotient is strictly less than -2^31, then return -2^31.
///  Example 1:
///    Input:
///      dividend = 10
///      divisor = 3
///    Output: 3
///    Explanation: 10 / 3 = 3.33333.. which is truncated to 3.
///
///  Example 2:
///    Input:
///      dividend = 7
///      divisor = -3
///    Output:
///      -2
///    Explanation: 7 / -3 = -2.33333.. which is truncated to -2.
///
///  Constraints:
///  1. -2^31 <= dividend, divisor <= 2^31 - 1
///  2. divisor != 0
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    3.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

namespace {
  using InputDataType = std::pair<int, int>;
  using OutputDataType = int;
  using TestDataType = std::tuple<InputDataType, OutputDataType>;

  class Solution {
    public:
    int divide(int dividend, int divisor) {
      // TODO: implement this method...
      return 0;
    }
  };

  struct TestSolution
      : Solution
      , testing::TestWithParam<TestDataType> {};

  // clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      TestSolution,
      ::testing::Values(
          // from example
          TestDataType{ InputDataType{ 10, 3 }, OutputDataType{ 3 } },
          TestDataType{ InputDataType{ -7, 3 }, OutputDataType{ -2 } }
          // additional
          // TODO: create additional tests...
  ));
  // clang-format on

  TEST_P(TestSolution, Test1) {
    auto [input, result] = GetParam();
    auto [dividend, divisor] = input;
    ASSERT_GE(dividend, std::numeric_limits<int>::min());
    ASSERT_LE(dividend, std::numeric_limits<int>::max());
    ASSERT_GE(divisor, std::numeric_limits<int>::min());
    ASSERT_LE(divisor, std::numeric_limits<int>::max());
    ASSERT_NE(divisor, 0);
    ASSERT_EQ(divide(dividend, divisor), result);
  }
} // namespace
