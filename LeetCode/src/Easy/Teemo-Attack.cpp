////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `findPoisonedDuration`-method of `Solution`-class
/// @details https://leetcode.com/problems/teemo-attacking/
/// Our hero Teemo is attacking an enemy Ashe with poison attacks! When Teemo attacks Ashe, Ashe gets poisoned for a
/// exactly duration seconds. More formally, an attack at second t will mean Ashe is poisoned during the inclusive
/// time interval [t, t + duration - 1]. If Teemo attacks again before the poison effect ends, the timer for it is
/// reset, and the poison effect will end duration seconds after the new attack.
/// You are given a non - decreasing integer array timeSeries, where timeSeries[i] denotes that Teemo attacks Ashe
/// at second timeSeries[i], and an integer duration.
/// Return the total number of seconds that Ashe is poisoned.
///
/// Example 1:
///   Input:
///     timeSeries = [1,4], duration = 2
///   Output:
///     4
///   Explanation: Teemo's attacks on Ashe go as follows:
///                - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
///                - At second 4, Teemo attacks, and Ashe is poisoned for seconds 4 and 5.
///                Ashe is poisoned for seconds 1, 2, 4, and 5, which is 4 seconds in total.
/// Example 2:
///   Input:
///     timeSeries = [1,2], duration = 2
///   Output:
///     3
/// Explanation: Teemo's attacks on Ashe go as follows:
///              - At second 1, Teemo attacks, and Ashe is poisoned for seconds 1 and 2.
///              - At second 2 however, Teemo attacks againand resets the poison timer.
///                 Ashe is poisoned for seconds 2 and 3.
///              Ashe is poisoned for seconds 1, 2, and 3, which is 3 seconds in total.
///
/// Constraints:
///   1 <= timeSeries.length <= 10^4
///   0 <= timeSeries[i], duration <= 10^7
///   timeSeries is sorted in non - decreasing order.
///
/// @author  Jon Galaz: jgalaz@aligntech.com
/// @date    27.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::pair<std::vector<int>, int>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    int findPoisonedDuration(std::vector<int>& timeSeries, int duration) {
        // implement solution here
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
      TestDataType{ InputDataType{ {1, 4} ,2 }, OutputDataType{ 4 } },
      TestDataType{ InputDataType{ {1, 2}, 2 }, OutputDataType{ 3 } }
      // additional
      // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();

    ASSERT_GE(inputData.first.size(), 1);
    ASSERT_LE(inputData.first.size(), static_cast<int>(10e4));

    ASSERT_GE(inputData.second, 1);
    ASSERT_LE(inputData.second, static_cast<int>(10e7));

    for (auto n : inputData.first) {
        ASSERT_GE(n, 1);
        ASSERT_LE(n, static_cast<int>(10e7));
    }

    std::sort(inputData.first.begin(), inputData.first.end());

    ASSERT_EQ(findPoisonedDuration(inputData.first, inputData.second), outputData);
}
} // namespace
