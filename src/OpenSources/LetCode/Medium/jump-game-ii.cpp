// https://leetcode.com/problems/combination-sum-ii/

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <vector>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

/*
 *  Описание решение:
 * 
 */

class Solution {
public:
    int jump(std::vector<int>& nums) {
        int n = nums.size();
        int jumps = 0, curent_end = 0, farthest = 0;

        for (int i = 0; i < n - 1; ++i) {
            farthest = std::max(farthest, i + nums[i]);
            if (i == curent_end) {
                ++jumps;
                curent_end = farthest;
            }
        }

        return jumps;
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
      TestDataType{ InputDataType{ 2,1  }, OutputDataType{ 1 }},
      TestDataType{ InputDataType{ 2,3,1,1,4  }, OutputDataType{ 2 }},
      TestDataType{ InputDataType{ 2,3,0,1,4  }, OutputDataType{ 2 }},
      TestDataType{ InputDataType{ 3,4,2,1,4,1,2,1,1  }, OutputDataType{ 3 }},
      TestDataType{ InputDataType{ 5,6,4,4,6,9,4,4,7,4,4,8,2,6,8,1,5,9,6,5,2,7,9,7,9,6,9,4,1,6,8,8,4,4,2,0,3,8,5  }, OutputDataType{ 5 }}
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, expected] = GetParam();
    ASSERT_EQ(jump(input_data), expected);
}
} // namespace
