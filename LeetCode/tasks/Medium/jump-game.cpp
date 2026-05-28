/// https://leetcode.com/problems/jump-game/description/

#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = bool;
using TestDataType = std::pair<InputDataType, OutputDataType>;

class Solution {
    public:
    bool jump(size_t position, std::vector<int>& nums) {
        if (position == nums.size() - 1) {
            return true;
        }

        if (nums[position] == -1) {
            return false;
        }

        for (size_t length = nums[position]; length >= 1; --length) {
            const size_t point = position + length;
            if (point >= nums.size() || jump(point, nums)) {
                return true;
            }
        }

        // mark that position as visited
        nums[position] = -1;
        return false;
    }

    bool canJump(std::vector<int>& nums) {
        return jump(0, nums);
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
          TestDataType{ InputDataType{0}, OutputDataType{true} },
          TestDataType{ InputDataType{10}, OutputDataType{true} },
          TestDataType{ InputDataType{2,3,1,1,4}, OutputDataType{true} },
          TestDataType{ InputDataType{3,2,1,0,4}, OutputDataType{false} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, output_data] = GetParam();
    ASSERT_EQ(canJump(input_data), output_data);
}
} // namespace
