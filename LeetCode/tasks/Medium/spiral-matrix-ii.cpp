// https://leetcode.com/problems/spiral-matrix-ii

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <optional>
#include <vector>

namespace {
using InputDataType = int;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using Row = std::vector<int>;
    using Matrix = std::vector<Row>;

    class Position {
        struct Coordinate
        {
            size_t x;
            size_t y;
        };

        public:
        Position(size_t i, size_t n)
            : _i{i}
            , _n{n}
            , _current{i, i} {
        }

        void goAround() {
            if (_current.x == _i && _current.y < _n) {
                ++_current.y;
            } else if (_current.x == _i && _current.y == _n) {
                ++_current.x;
            } else if (_current.x < _n && _current.y == _n) {
                ++_current.x;
            } else if (_current.x == _n && _current.y == _n) {
                --_current.y;
            } else if (_current.x == _n && _current.y > _i) {
                --_current.y;
            } else if (_current.x == _n && _current.y == _i) {
                --_current.x;
            } else if (_current.x > _i + 1 && _current.y == _i) {
                --_current.x;
            } else if (_current.x == _i + 1 && _current.y == _i) {
                _current.x = _current.y = _i = ++_i;
                --_n;
            }
        }

        const Coordinate& get() {
            return _current;
        }

        private:
        size_t _i;
        size_t _n;
        Coordinate _current{};
    };

    public:
    Matrix generateMatrix(int n) {
        Matrix matrix(n, Row(n, 0));
        int value{0};
        for (Position position(0, n - 1); value != n * n; position.goAround()) {
            auto& [i, j] = position.get();
            matrix[i][j] = ++value;
        }
        return matrix;
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
      TestDataType{ InputDataType{ 1 }, OutputDataType{{1}} },
      TestDataType{ InputDataType{ 2 }, OutputDataType{{1,2}, {4, 3}} },
      TestDataType{ InputDataType{ 3 }, OutputDataType{{1,2,3},{8,9,4},{7,6,5}} },
      TestDataType{ InputDataType{ 4 }, OutputDataType{{1,2,3,4}, {12,13,14,5}, {11,16,15,6}, {10,9,8,7}} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [n, expected_matrix] = GetParam();
    auto real_matrix = generateMatrix(n);

    ASSERT_EQ(expected_matrix.size(), real_matrix.size());
    for (size_t i = 0; i < expected_matrix.size(); ++i) {
        ASSERT_EQ(expected_matrix[i].size(), real_matrix[i].size());
        for (size_t j = 0; j < expected_matrix[i].size(); ++j) {
            ASSERT_EQ(expected_matrix[i][j], real_matrix[i][j]);
        }
    }
}
} // namespace
