// https://leetcode.com/problems/set-matrix-zeroes

#include "../support.h"
#include <vector>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        const size_t m = matrix.size();
        const size_t n = matrix[0].size();

        std::vector<std::function<void()>> zeroMakers{};

        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    zeroMakers.emplace_back([=, &matrix]() {
                        for (size_t k = 0; k < n; ++k) {
                            matrix[i][k] = 0;
                        }

                        for (size_t k = 0; k < m; ++k) {
                            matrix[k][j] = 0;
                        }
                    });
                }
            }
        }

        for (auto& maker : zeroMakers) {
            maker();
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
      TestDataType{ InputDataType{ {1,1,1},{1,0,1},{1,1,1} }, OutputDataType{ {1,0,1},{0,0,0},{1,0,1} } },
      TestDataType{ InputDataType{ {0,1,2,0},{3,4,5,2},{1,3,1,5} }, OutputDataType{ {0,0,0,0},{0,4,5,0},{0,3,1,0} } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_matrix, zeros_matrix] = GetParam();
    setZeroes(input_matrix);
    Support::compareTwoMatrix(input_matrix, zeros_matrix);
}
} // namespace
