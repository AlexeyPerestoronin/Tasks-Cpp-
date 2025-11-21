// https://leetcode.com/problems/unique-paths

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::pair<int, int>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    int uniquePaths(int m, int n) {
        std::vector<std::vector<int>> matrix(m, std::vector<int>(n, 1));
        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 1; j < n; ++j) {
                matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];
            }
        }
        return matrix[m - 1][n - 1];
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
      TestDataType{ InputDataType{ 2, 2 }, OutputDataType{2} },
      TestDataType{ InputDataType{ 3, 2 }, OutputDataType{3} },
      TestDataType{ InputDataType{ 3, 7 }, OutputDataType{28} },
      TestDataType{ InputDataType{ 3, 3 }, OutputDataType{6} },
      TestDataType{ InputDataType{ 4, 4 }, OutputDataType{20} },
      TestDataType{ InputDataType{ 10, 10 }, OutputDataType{48620} },
      TestDataType{ InputDataType{ 51, 9 }, OutputDataType{1916797311} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, expected_paths] = GetParam();
    auto [m, n] = input_data;
    ASSERT_EQ(expected_paths, uniquePaths(m, n));
}
} // namespace
