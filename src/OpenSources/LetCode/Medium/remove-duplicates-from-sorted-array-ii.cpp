// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

#include "../support.h"
#include <algorithm>
#include <map>
#include <vector>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
    int removeDuplicates(std::vector<int>& nums) {
        auto size = nums.size();
        if (size <= 2) {
            return size;
        }

        int previous_value = nums[0], quantity = 1;
        for (size_t i = 1; i < size; ++i) {
            if (nums[i] != previous_value) {
                previous_value = nums[i];
                quantity = 1;
                continue;
            }

            if (++quantity >= 3) {
                for (size_t j = i; j < size - 1; ++j) {
                    std::swap(nums[j], nums[j+1]);
                }
                --size;
                --i;
            }
        }

        return size;
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
      TestDataType{ InputDataType{ 1,1,1,2,2,3 }, OutputDataType{ 5 } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [nums, new_length] = GetParam();
    ASSERT_EQ(new_length, removeDuplicates(nums));
}
} // namespace