/// https://leetcode.com/problems/merge-intervals/description/

#include <algorithm>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::pair<InputDataType, OutputDataType>;

class Solution {
    public:
    using Interval = std::vector<int>;
    std::vector<Interval> merge(std::vector<Interval>& intervals) {
        std::sort(intervals.begin(), intervals.end());
        auto prev_interval = intervals.begin();
        auto new_end_it = std::remove_if(intervals.begin() + 1, intervals.end(), [&](const auto& interval) -> bool {
            bool result = false;
            if ((*prev_interval)[1] >= interval[0]) {
                result = true;
                if ((*prev_interval)[1] < interval[1]) {
                    (*prev_interval)[1] = interval[1];
                }
                return true;
            } else {
                ++prev_interval;
                return false;
            }
        });

        intervals.erase(new_end_it, intervals.end());
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
          TestDataType { 
            InputDataType{{1,1}},
            OutputDataType{{1, 1}}
          },
          TestDataType { 
            InputDataType{{0,1}, {2, 3}},
            OutputDataType{{0, 1}, {2,3}}
          },
          TestDataType { 
            InputDataType{{1,4}, {0, 4}},
            OutputDataType{{0, 4}}
          },
          TestDataType { 
            InputDataType{{1,4}, {0, 5}},
            OutputDataType{{0, 5}}
          },
          TestDataType { 
            InputDataType{{1,5},{8,10},{3,9}},
            OutputDataType{{1, 10}}
          },
          TestDataType { 
            InputDataType{{2,3},{2,2},{3,3},{1,3},{5,7},{2,2},{4,6}},
            OutputDataType{{1, 3}, {4, 7}}
          },
          TestDataType { 
            InputDataType{{1,3},{2,6},{8,10},{15,18}},
            OutputDataType{{1,6},{8,10},{15,18}}
          }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, output_data] = GetParam();
    ASSERT_EQ(merge(input_data), output_data);
}
} // namespace
