////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `maxLength`-method of `Solution`-class
/// @details https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
/// You are given an array of strings `arr`.
/// A string s is formed by the **concatenation** of a **subsequence** of `arr` that has unique characters.
///
/// Return the maximum possible length of s.
///
/// A **subsequence** is an array that can be derived from another array by deleting some
/// or no elements without changing the order of the remaining elements.
///
/// Example 1:
///   Input: arr = ["un", "iq", "ue"]
///   Output: 4
///   Explanation: All the valid **concatenations** are:
///   - ""
///   - "un"
///   - "iq"
///   - "ue"
///   - "uniq"("un" + "iq")
///   - "ique"("iq" + "ue") -> Maximum length is 4.
///
/// Example 2:
///   Input: arr = ["cha", "r", "act", "ers"]
///   Output: 6
///   Explanation: Possible longest valid concatenations are:
///   - "chaers"("cha" + "ers")
///   - "acters"("act" + "ers") -> Maximum length is 6.
///
/// Example 3:
///   Input: arr = ["abcdefghijklmnopqrstuvwxyz"]
///   Output: 26
///   Explanation: The only string in arr has all 26 characters.
///
/// Constraints:
/// 1. 1 <= arr.length <= 16
/// 2. 1 <= arr[i].length <= 26
/// 3. arr[i] contains only lowercase English letters.
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    23.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::string>;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using SetStr = std::set<std::string>;

    public:
    static size_t compute(SetStr::iterator itFrom, SetStr::iterator itTo, const std::string& str) {
        size_t result = str.size();
        if (result < 26)
            for (; itFrom != itTo; ++itFrom) {
                std::string loc = str + *itFrom;
                if (std::sort(loc.begin(), loc.end());
                    std::adjacent_find(loc.begin(), loc.end(), [](char ch1, char ch2) { return ch1 == ch2; }) == loc.end())
                    result = std::max(result, compute(std::next(itFrom), itTo, str + *itFrom));
            }
        return result;
    }

    int maxLength(std::vector<std::string>& arr) {
        size_t result{0};
        // TODO: implement this method...
        return static_cast<int>(result);
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
            TestDataType{ InputDataType{ "un", "iq", "ue" }, OutputDataType{ 4 } },
            TestDataType{ InputDataType{ "cha", "r", "act", "ers" }, OutputDataType{ 6 } },
            TestDataType{ InputDataType{ "abcdefghijklmnopqrstuvwxyz" }, OutputDataType{ 26 } }
            // additional
            // TODO: create additional tests...
    ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    ASSERT_LE(inputData.size(), 16);
    for (const auto& str : inputData)
        ASSERT_LE(str.size(), 26);
    ASSERT_EQ(maxLength(inputData), outputData);
}
} // namespace
