// https://leetcode.com/problems/minimum-path-sum

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        const size_t m = grid.size();
        const size_t n = grid[0].size();
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (auto& value = grid[i][j]; i == 0 && j == 0) {
                } else if (i == 0) {
                    value += grid[i][j - 1];
                } else if (j == 0) {
                    value += grid[i - 1][j];
                } else {
                    value = std::min(value + grid[i - 1][j], value + grid[i][j - 1]);
                }
            }
        }
        return grid[m - 1][n - 1];
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
      TestDataType{ InputDataType{ {1,3,1},{1,5,1},{4,2,1} }, OutputDataType{7} },
      TestDataType{ InputDataType{ {1,2,3},{4,5,6} }, OutputDataType{12} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_matrix, expected_minimum_path] = GetParam();
    ASSERT_EQ(expected_minimum_path, minPathSum(input_matrix));
}
} // namespace
