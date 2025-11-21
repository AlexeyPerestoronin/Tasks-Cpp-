// https://leetcode.com/problems/set-matrix-zeroes

#include "../support.h"
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<std::vector<int>>, int>;
using OutputDataType = bool;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();

        bool result = false;
        for (size_t i = 0; i < m; ++i) {
            auto l_value = matrix[i][0];
            auto r_value = matrix[i][n - 1];
            if (l_value > target) {
                break;
            } else if (target > r_value) {
                continue;
            } else if (l_value <= target && target <= r_value) {
                for (size_t j = 0; j < n; ++j) {
                    if (matrix[i][j] == target) {
                        result = true;
                        break;
                    }
                }
            }

            if (result) {
                break;
            }
        }

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
      // from example
      TestDataType{ InputDataType{ {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 3  }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, 13 }, OutputDataType{ false } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input, result] = GetParam();
    auto& [input_matrix, target] = input;
    ASSERT_EQ(searchMatrix(input_matrix, target), result);
}
} // namespace
