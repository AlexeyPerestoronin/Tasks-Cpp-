// https://leetcode.com/problems/combinations/

#include "../support.h"
#include <algorithm>
#include <vector>

namespace {
using InputDataType = std::pair<int, int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    int k;
    std::vector<int> digits{};
    std::vector<std::vector<int>> combinations{};

    void add(size_t i, std::vector<int> combination) {
        if (combination.size() == k) {
            combinations.push_back(std::move(combination));
            return;
        }

        for (; i < digits.size(); ++i) {
            auto next_combination = combination;
            next_combination.push_back(digits[i]);
            add(i + 1, std::move(next_combination));
        }
    }

    public:
    std::vector<std::vector<int>> combine(int n, int k) {
        this->k = k;
        for (size_t i = 1; i <= n; ++i) {
            digits.push_back(i);
        }

        add(0, std::vector<int>{});
        return combinations;
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
      TestDataType{ InputDataType{ 4, 2 }, OutputDataType{ {1,2},{1,3},{1,4},{2,3},{2,4},{3,4} } },
      TestDataType{ InputDataType{ 1, 1 }, OutputDataType{ {1} } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input, expected_combinations] = GetParam();
    auto [n, k] = input;
    auto result_combinations = combine(n, k);
    std::sort(result_combinations.begin(), result_combinations.end());
    Support::compareTwoArray(expected_combinations, result_combinations);
}
} // namespace
