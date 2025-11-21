// https://leetcode.com/problems/search-in-rotated-sorted-array-ii

#include "../support.h"
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<int>, int>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
    bool search(std::vector<int>& nums, int target) {
        const size_t size = nums.size();

        if (size == 1) {
            return nums[0] == target;
        }

        if (size == 2) {
            return nums[0] == target || nums[1] == target;
        }

        const size_t middle = nums.size() / 2 + 1;

        for (size_t i = 0, j = size - 1; !(i >= middle && i <= middle); ++i, --j) {
            if (nums[i] == target || nums[j] == target) {
                return true;
            }
        }

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
      TestDataType{ InputDataType{ {2,2,2,3,2,2,2}, 3 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {1,2,3}, 4 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ {1,2}, 2 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {1,2}, 3 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ {2,5,6,0,0,1,2}, 0 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {2,5,6,0,0,1,2}, 3 }, OutputDataType{ false } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, result] = GetParam();
    auto& [nums, target] = input_data;
    ASSERT_EQ(search(nums, target), result);
}
} // namespace