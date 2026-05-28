// https://leetcode.com/problems/insert-in  terval

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <optional>
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<std::vector<int>>, std::vector<int>>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    using VecInt = std::vector<int>;
    using VecVecInt = std::vector<VecInt>;

    bool tryIntersect(VecInt& l_interval, VecInt& r_interval) {
        if (l_interval[0] <= r_interval[0] && r_interval[0] <= l_interval[1]) {
            l_interval[0] = r_interval[0] = std::min(l_interval[0], r_interval[0]);
            r_interval[1] = l_interval[1] = std::max(l_interval[1], r_interval[1]);
            return true;
        }
        return false;
    }

    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        intervals.push_back(newInterval);
        std::sort(intervals.begin(), intervals.end());

        auto checkToRemove = [&](auto start_it) {
            return std::adjacent_find(
                start_it, intervals.end(), [&](auto& l_interval, auto& r_interval) -> bool { return tryIntersect(l_interval, r_interval); });
        };

        for (auto remove_it = checkToRemove(intervals.begin()); remove_it != intervals.end(); remove_it = checkToRemove(remove_it)) {
            intervals.erase(remove_it + 1);
        }

        return intervals;
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
      TestDataType{ InputDataType{ { {1,3},{6,9} }, {2,5} }, OutputDataType{{1,5},{6,9}}},
      TestDataType{ InputDataType{ { {1,3},{5,7} }, {2,6} }, OutputDataType{{1,7}}},
      TestDataType{ InputDataType{ { {1,3},{9,11} }, {5,7} }, OutputDataType{{1,3},{5,7},{9,11}}},
      TestDataType{ InputDataType{ { {1,3},{5,7}, {9, 11} }, {2,10} }, OutputDataType{{1,11}}},
      TestDataType{ InputDataType{ { {1,2},{3,5},{6,7},{8,10},{12,16} }, {4,8} }, OutputDataType{{1,2},{3,10},{12,16}}}
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, expected] = GetParam();
    auto& [intervals, new_interval] = input_data;
    auto result = insert(intervals, new_interval);

    ASSERT_EQ(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i) {
        ASSERT_EQ(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j) {
            ASSERT_EQ(expected[i][j], result[i][j]);
        }
    }
}
} // namespace
