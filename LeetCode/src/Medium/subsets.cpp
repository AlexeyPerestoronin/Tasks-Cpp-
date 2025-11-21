// https://leetcode.com/problems/subsets/

#include "../support.h"
#include <algorithm>
#include <vector>

namespace {
using InputDataType = std::vector<int>;
using OutputDataType = std::vector<std::vector<int>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using SubSet = std::vector<int>;
    using SubSets = std::vector<SubSet>;

    SubSets possible_subsets{};

    void detectNewSubset(SubSet subset, SubSet::iterator beginIt, const SubSet::iterator& endIt) {
        possible_subsets.push_back(subset);

        for (; beginIt != endIt; ++beginIt) {
            auto new_subset = subset;
            new_subset.push_back(*beginIt);
            detectNewSubset(std::move(new_subset), beginIt + 1, endIt);
        }
    }

    public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        detectNewSubset(SubSet{}, nums.begin(), nums.end());
        return possible_subsets;
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
      TestDataType{ InputDataType{ 1,2,3 }, OutputDataType{ {},{1},{2},{1,2},{3},{1,3},{2,3},{1,2,3} } },
      TestDataType{ InputDataType{ 0 }, OutputDataType{ {},{0} } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [nums, expected_subsets] = GetParam();
    auto real_subsets = subsets(nums);
    std::sort(real_subsets.begin(), real_subsets.end());
    std::sort(expected_subsets.begin(), expected_subsets.end());
    Support::compareTwoArray(expected_subsets, real_subsets);
}
} // namespace
