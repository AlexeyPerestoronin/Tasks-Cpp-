// https://leetcode.com/problems/unique-paths-ii

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>>& matrix) {
        if (auto& start_position = matrix[0][0]; start_position == 1) {
            return 0;
        } else {
            start_position = 1;
        }

        const size_t m = matrix.size();
        const size_t n = matrix[0].size();

        for (size_t j = 1; j < n; ++j) {
            auto& value = matrix[0][j];
            value = value == 0 ? 1 : 0;

            if (value != 0) {
                auto left = j > 0 ? matrix[0][j - 1] : 0;
                value = left;
            }
        }

        for (size_t i = 1; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                auto& value = matrix[i][j];
                value = value == 0 ? 1 : 0;

                if (value != 0) {
                    auto upper = i > 0 ? matrix[i - 1][j] : 0;
                    auto left = j > 0 ? matrix[i][j - 1] : 0;
                    value = (upper + left);
                }
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
      TestDataType{ InputDataType{ {1,0} }, OutputDataType{0} },
      TestDataType{ InputDataType{ {0,1,0,0} }, OutputDataType{0} },
      TestDataType{ InputDataType{ {0,1},{0,0} }, OutputDataType{1} },
      TestDataType{ InputDataType{ {0,0,0},{0,1,0},{0,0,0} }, OutputDataType{2} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_matrix, expected_paths] = GetParam();
    ASSERT_EQ(expected_paths, uniquePathsWithObstacles(input_matrix));
}
} // namespace
