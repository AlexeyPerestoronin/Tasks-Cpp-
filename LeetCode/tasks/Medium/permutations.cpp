/// https://leetcode.com/problems/permutations/description/

#include <algorithm>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::pair<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        std::vector<std::vector<int>> result{};
        do {
            result.emplace_back(nums.begin(), nums.end());
        } while (std::next_permutation(nums.begin(), nums.end()));
        return result;
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
          TestDataType{ InputDataType{0}, OutputDataType{{0}} },
          TestDataType{ InputDataType{0, 1}, OutputDataType{{0, 1}, {1, 0}} },
          TestDataType{ InputDataType{1,2,3}, OutputDataType{
            {1,2,3},
            {1,3,2},
            {2,1,3},
            {2,3,1},
            {3,1,2},
            {3,2,1}}}
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, output_data] = GetParam();
    ASSERT_EQ(permute(input_data), output_data);
}
} // namespace
