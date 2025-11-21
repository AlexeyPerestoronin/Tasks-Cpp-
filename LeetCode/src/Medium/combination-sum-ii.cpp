// https://leetcode.com/problems/combination-sum-ii/

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <set>
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<int>, int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using Combination = std::vector<int>;
    using UniqueCombinations = std::set<Combination>;
    using CombinationStorage = std::map<int, int>;

    UniqueCombinations combinations;

    Combination extend(Combination combination, int value, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            combination.push_back(value);
        }
        return combination;
    }

    void find(CombinationStorage::iterator it_being, const CombinationStorage::iterator& it_end, Combination combination, int target) {
        if (it_being != it_end) {
            const auto& [value, amount] = *it_being;
            for (int quantity = 0; quantity <= amount; ++quantity) {
                if (auto increment = value * quantity; increment < target) {
                    find(std::next(it_being), it_end, extend(combination, value, quantity), target - increment);
                } else if (increment == target) {
                    combinations.emplace(extend(combination, value, quantity));
                }
            }
        }
    }

    public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        auto it_end = std::remove_if(candidates.begin(), candidates.end(), [&](int value) { return value > target; });
        std::sort(candidates.begin(), it_end);
        CombinationStorage storage;
        for (auto it_begin = candidates.begin(); it_begin != it_end; ++it_begin) {
            storage[*it_begin]++;
        }

        find(storage.begin(), storage.end(), Combination{}, target);

        std::vector<std::vector<int>> result(combinations.begin(), combinations.end());
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
      TestDataType{ InputDataType{ { 1 }, 8 }, OutputDataType{}},
      TestDataType{ InputDataType{ { 1 }, 1 }, OutputDataType{ {1} }},
      TestDataType{ InputDataType{ { 1, 1, 1 }, 3 }, OutputDataType{ {1, 1, 1} }},
      TestDataType{ InputDataType{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, 24 }, OutputDataType{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } }},
      TestDataType{ InputDataType{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, 25 }, OutputDataType{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } }},
      TestDataType{ InputDataType{ { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, 27 }, OutputDataType{}},
      TestDataType{
        InputDataType{ { 14,6,25,9,30,20,33,34,28,30,16,12,31,9,9,12,34,16,25,32,8,7,30,12,33,20,21,29,24,17,27,34,11,17,30,6,32,21,27,17,16,8,24,12,12,28,11,33,10,32,22,13,34,18,12 }, 27 },
        OutputDataType{{6,6,7,8},{6,7,14},{6,8,13},{6,9,12},{6,10,11},{6,21},{7,8,12},{7,9,11},{7,20},{8,8,11},{8,9,10},{9,9,9},{9,18},{10,17},{11,16},{13,14},{27}}},
      TestDataType{ InputDataType{ {10,1,2,7,6,1,5}, 8 }, OutputDataType{ {1,1,6 }, {1,2,5}, {1,7}, {2,6} } },
      TestDataType{ InputDataType{ {2,5,2,1,2}, 5 }, OutputDataType{ {1,2,2 }, {5} } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, expected_sums] = GetParam();
    auto& [candidates, target] = input_data;
    auto real_sums = combinationSum2(candidates, target);
    ASSERT_EQ(expected_sums.size(), real_sums.size());

    std::sort(expected_sums.begin(), expected_sums.end());
    std::sort(real_sums.begin(), real_sums.end());
    for (size_t i{0}; i < expected_sums.size(); ++i) {
        auto& expected_sum = expected_sums[i];
        auto& real_sum = real_sums[i];

        ASSERT_EQ(expected_sum.size(), real_sum.size());

        std::sort(expected_sum.begin(), expected_sum.end());
        std::sort(real_sum.begin(), real_sum.end());

        for (size_t j{0}; j < expected_sum.size(); ++j) {
            ASSERT_EQ(expected_sum[j], real_sum[j]);
        }
    }
}
} // namespace
