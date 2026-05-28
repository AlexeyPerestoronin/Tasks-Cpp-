/// https://leetcode.com/problems/spiral-matrix/description/

#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = std::vector<int>;
using TestDataType = std::pair<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        enum
        {
            RIGHT,
            DOWN,
            LEFT,
            UP,
        } direction = RIGHT;

        auto [m1, m2] = std::make_pair(size_t{1}, matrix.size());
        auto [n1, n2] = std::make_pair(size_t{0}, matrix[0].size());
        size_t step{m2-- * n2--};
        size_t i{0};
        size_t j{0};
        std::vector<int> result{};
        while (step--) {
            result.push_back(matrix[i][j]);

            if (direction == RIGHT) {
                if (j != n2) {
                    ++j;
                } else {
                    --n2;
                    ++i;
                    direction = DOWN;
                }
            } else if (direction == DOWN) {
                if (i != m2) {
                    ++i;
                } else {
                    --m2;
                    --j;
                    direction = LEFT;
                }
            } else if (direction == LEFT) {
                if (j != n1) {
                    --j;
                } else {
                    ++n1;
                    --i;
                    direction = UP;
                }
            } else if (direction == UP) {
                if (i != m1) {
                    --i;
                } else {
                    ++m1;
                    ++j;
                    direction = RIGHT;
                }
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
          TestDataType
          {
            InputDataType
            {
              {1},
            },
            OutputDataType{1}
          },
          TestDataType
          {
            InputDataType
            {
              {1,2,3},
            },
            OutputDataType{1,2,3}
          },
          TestDataType
          {
            InputDataType
            {
              {1},
              {4},
              {7}
            },
            OutputDataType{1,4,7}
          },
          TestDataType{
            InputDataType
            {
              {1,2,3},
              {4,5,6},
              {7,8,9}
            },
            OutputDataType{1,2,3,6,9,8,7,4,5}
          },
          TestDataType
          {
            InputDataType
            {
              {1,2,3,4},
              {5,6,7,8},
              {9,10,11,12}
            },
            OutputDataType{1,2,3,4,8,12,11,10,9,5,6,7}
          }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, output_data] = GetParam();
    ASSERT_EQ(spiralOrder(input_data), output_data);
}
} // namespace
