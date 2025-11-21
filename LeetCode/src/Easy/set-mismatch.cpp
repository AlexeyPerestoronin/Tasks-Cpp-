////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `findErrorNums`-method of `Solution`-class
/// @details https://leetcode.com/problems/set-mismatch/
/// You have a set of integers s, which originally contains all the numbers from 1 to n.
/// Unfortunately, due to some error, one of the numbers in s got duplicated to another number in the set, which results
/// in repetition of one number and loss of another number.
///
/// You are given an integer array nums representing the data status of this set after the error.
/// Find the number that **occurs twice** and the number that **is missing** and return them in the form of an array.
///
/// Example 1:
///   Input:
///     nums = [1, 2, 2, 4]
///   Output:
///     [2, 3]
///
/// Example 2:
///   Input:
///     nums = [1, 1]
///   Output:
///     [1, 2]
///
/// Constraints:
/// 1. 2 <= nums.length <= 10^4
/// 2. 1 <= nums[i] <= 10^4
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    23.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<int>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<int> findErrorNums(std::vector<int>& nums) {
        // TODO: implement this method...
        return nums;
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
            TestDataType{ InputDataType{ 1, 2, 2, 4 }, OutputDataType{ 2, 3 } },
            TestDataType{ InputDataType{ 1, 1 }, OutputDataType{ 1, 2 } }
            // additional
            // TODO: create additional tests...
    ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    ASSERT_EQ(findErrorNums(inputData), outputData);
}
} // namespace
