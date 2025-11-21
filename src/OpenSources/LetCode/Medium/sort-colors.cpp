// https://leetcode.com/problems/sort-colors

#include "../support.h"
#include <vector>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<int>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
    void sortColors(std::vector<int>& nums) {
        for (size_t i = 1; i < nums.size(); ++i) {
            for (size_t j = i; j != 0 && nums[j-1] > nums[j]; --j) {
                std::swap(nums[j-1], nums[j]);
            }
        }
        return;
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
      TestDataType{ InputDataType{ 2,0,1 }, OutputDataType{ 0,1,2 } },
      TestDataType{ InputDataType{ 2,0,2,1,1,0 }, OutputDataType{ 0,0,1,1,2,2 } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_color, output_color] = GetParam();
    sortColors(input_color);
    Support::compareTwoArray(input_color, output_color);
}
} // namespace
