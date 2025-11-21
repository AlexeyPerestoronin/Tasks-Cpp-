////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `twoSum`-method of `Solution`-class
/// @details https://leetcode.com/problems/two-sum/
/// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
/// You may assume that each input would have exactly one solution, and you may not use the same element twice.
/// You can return the answer in any order.
///
/// Example 1:
///   Input:
///     nums = [2,7,11,15], target = 9
///   Output:
///     [0,1]
///   Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
///
/// Example 2:
///   Input:
///     nums = [3,2,4], target = 6
///   Output:
///     [1, 2]
///
/// Constraints:
///   2 <= nums.length <= 10^4
///   -10^9 <= nums[i] <= 10^9
///   -10^9 <= target <= 10^9
///   Only one valid answer exists.
///
/// @author  Jon Galaz: jgalaz@aligntech.com
/// @date    25.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <utility>
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<int>, int>;
using OutputDataType = std::vector<int>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // create a map where we will store the already visited and non valid answers
        std::unordered_map<int, int> counted;

        // for every number
        for (int i = 0; i < nums.size(); i++) {
            // compute it's complement
            int complement = target - nums[i];

            // if the complement is stored in our map
            if (counted.count(complement))
                // return it along with the index of the current iteration
                return {counted.at(complement), i};

            // add value as visited
            counted[nums[i]] = i;
        }

        // if we didn't find an answer we return an empty vector
        return {};
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
      TestDataType{ InputDataType{ {2, 7, 11, 15}, 9}, OutputDataType{ 0, 1 } },
      TestDataType{ InputDataType{ {3, 2, 4}, 6 }, OutputDataType{ 1, 2} },
      TestDataType{ InputDataType{ {3, 3}, 6 }, OutputDataType{ 0, 1} }
      // additional
      // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    ASSERT_EQ(twoSum(inputData.first, inputData.second), outputData);
}
} // namespace
