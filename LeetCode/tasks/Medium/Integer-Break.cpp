////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `integerBreak`-method of `Solution`-class
/// @details https://leetcode.com/problems/integer-break/
/// Given an integer n, break it into the sum of k positive integers, where k >= 2, and maximize the product of those integers.
/// Return the maximum product you can get.
///
/// Example 1:
///   Input:
///     n = 2
///   Output:
///     1
///   Explanation: 2 = 1 + 1, 1 x 1 = 1
///
/// Example 2:
///   Input:
///     n = 10
///   Output:
///     36
///   Explanation: 10 = 3 + 3 + 4, 3 x 3 x 4 = 36.
///
/// Constraints:
///   2 <= n <= 58
///
/// @author  Jon Galaz: jgalaz@aligntech.com
/// @date    26.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = int;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    int integerBreak(int n) {
        // Implement your solution here
        return 0;
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
      TestDataType{ InputDataType{ 2 }, OutputDataType{ 1 } },
      TestDataType{ InputDataType{ 10 }, OutputDataType{ 36 } }
      // additional
      // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();

    ASSERT_GE(inputData, 2);
    ASSERT_LE(inputData, 58);

    ASSERT_EQ(integerBreak(inputData), outputData);
}
} // namespace
