////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `threeSum`-method of `Solution`-class
/// @details https://leetcode.com/problems/3sum/
/// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
/// nums[k] == 0. Notice that the solution set must not contain duplicate triplets.
///
/// Example-1:
///   Input:
///     nums = [-1, 0, 1, 2, -1, -4]
///   Output:
///     [[-1, -1, 2], [-1, 0, 1]]
///   Explanation:
///     nums[0] + nums[1] + nums[2] =(-1) + 0 + 1 = 0
///     nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0
///     nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0
///     The distinct triplets are[-1, 0, 1] and [-1, -1, 2].Notice that the order of the output and the order of the triplets does not matter.
///
/// Example-2:
///   Input:
///     nums = [0, 1, 1]
///   Output:
///     []
///   Explanation:
///     The only possible triplet does not sum up to 0.
///
/// Example-3:
///   Input:
///     nums = [0, 0, 0]
///   Output:
///     [[0, 0, 0]]
///   Explanation:
///     The only possible triplet sums up to 0.
///
/// Constraints:
/// 1. 3 <= nums.length <= 3000
/// 2. -10^5 <= nums[i] <= 10^5
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    29.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        // TODO: implement this method...
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
          TestDataType{ InputDataType{ 0, 1, 1 }, OutputDataType{} },
          TestDataType{ InputDataType{ 0, 0, 0 }, OutputDataType{ { 0, 0, 0 } } }
          // additional
          // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    static auto sort = [](OutputDataType&& data) -> OutputDataType {
        std::for_each(data.begin(), data.end(), [](auto& d) { std::sort(d.begin(), d.end()); });
        std::sort(data.begin(), data.end(), [&](auto& lh, auto& rh) -> bool {
            std::sort(lh.begin(), lh.end());
            std::sort(rh.begin(), rh.end());
            for (size_t i = 0; i < 3; ++i)
                if (lh[i] != rh[i])
                    return lh[i] < rh[i];

            throw std::logic_error("the triplets couldn't be equal");
        });

        return data;
    };

    auto [nums, triplets] = GetParam();
    ASSERT_GE(nums.size(), 3);
    ASSERT_LE(nums.size(), 3000);
    for (const auto& num : nums) {
        constexpr int limit = 1000000;
        ASSERT_GE(num, -limit);
        ASSERT_LE(num, limit);
    }
    ASSERT_EQ(sort(threeSum(nums)), sort(std::move(triplets)));
}
} // namespace
