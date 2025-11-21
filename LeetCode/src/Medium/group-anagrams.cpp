////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `groupAnagrams`-method of `Solution`-class
/// @details https://leetcode.com/problems/group-anagrams/
/// Given an array of strings strs, group the anagrams together. You can return the answer in any order.
/// An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
/// typically using all the original letters exactly once.
///
/// Example 1:
///   Input:
///     strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
///   Output:
///     [["bat"], ["nat", "tan"], ["ate", "eat", "tea"]]
///
/// Example 2:
///   Input:
///     strs = [""]
///   Output:
///     [[""]]
///
/// Example 3:
///   Input:
///     strs = ["a"]
///   Output:
///     [["a"]]
///
/// Constraints :
/// 1. 1 <= strs.length <= 10^4
/// 2. 0 <= strs[i].length <= 100
/// 3. strs[i] consists of lowercase English letters.
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    28.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::string>;
using OutputDataType = std::vector<std::vector<std::string>>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
        std::vector<std::vector<std::string>> results{};
        // TODO: implement this method...
        return results;
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
          TestDataType{ InputDataType{ "eat", "tea", "tan", "ate", "nat", "bat" }, OutputDataType{ { "bat" }, { "nat", "tan" }, { "ate", "eat", "tea" } } },
          TestDataType{ InputDataType{ "" }, OutputDataType{ { "" } } },
          TestDataType{ InputDataType{ "a" }, OutputDataType{ { "a" } } }
          // additional
          // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    static auto sort = [](OutputDataType&& data) -> OutputDataType {
        for (auto& d : data)
            std::sort(d.begin(), d.end());

        std::sort(data.begin(), data.end(), [](const OutputDataType::value_type& lh, const OutputDataType::value_type& rh) -> bool {
            if (!lh.empty() && !rh.empty())
                if (lh.size() == rh.size())
                    return *lh.begin() < *rh.begin();
            return lh.size() < rh.size();
        });

        return data;
    };

    auto [strs, anagrams] = GetParam();
    ASSERT_GE(strs.size(), 1);
    ASSERT_LE(strs.size(), 10 ^ 4);
    for (const auto& str : strs)
        ASSERT_LE(str.length(), 100);
    ASSERT_EQ(sort(groupAnagrams(strs)), sort(std::move(anagrams)));
}
} // namespace
