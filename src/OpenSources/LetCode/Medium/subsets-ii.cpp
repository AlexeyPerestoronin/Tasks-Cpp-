// https://leetcode.com/problems/subsets-ii

#include "../support.h"
#include <algorithm>
#include <vector>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using Subset = std::vector<int>;
    std::set<Subset> unique_subsetss{};

    void detect(Subset subset, Subset::iterator it_begin, const Subset::iterator& it_end) {
        unique_subsetss.emplace(subset);

        for (; it_begin != it_end; ++it_begin) {
            Subset next_subset = subset;
            next_subset.push_back(*it_begin);
            detect(std::move(next_subset), it_begin + 1, it_end);
        }
    }

public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        detect(Subset{}, nums.begin(), nums.end());
        return std::vector<Subset>(unique_subsetss.begin(), unique_subsetss.end());
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
      TestDataType{ InputDataType{ 1,2,2 }, OutputDataType{ {},{1},{1,2},{1,2,2},{2},{2,2} } },
      TestDataType{ InputDataType{ 0 }, OutputDataType{ {},{0} } },
     //     nums: [4,4,4,1,4]
     // expected: [[],[1],[1,4],[1,4,4],[1,4,4,4],[1,4,4,4,4],[4],[4,4],[4,4,4],[4,4,4,4]]
     //   output: [[],[1],[1,4],[4],[4,1],[4,1,4],[4,4],[4,4,1],[4,4,1,4],[4,4,4],[4,4,4,1],[4,4,4,1,4],[4,4,4,4]]
      TestDataType{ InputDataType{ 4,4,4,1,4 }, OutputDataType{ {},{1},{1,4},{1,4,4},{1,4,4,4},{1,4,4,4,4},{4},{4,4},{4,4,4},{4,4,4,4} } },
      // my tests
      TestDataType{ InputDataType{ 1,1,1 }, OutputDataType{ {},{1},{1,1},{1,1,1} } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [nums, expected_subsets] = GetParam();
    auto real_subsets = subsetsWithDup(nums);
    std::sort(real_subsets.begin(), real_subsets.end());
    std::sort(expected_subsets.begin(), expected_subsets.end());
    Support::compareTwoArray(expected_subsets, real_subsets);
}
} // namespace
