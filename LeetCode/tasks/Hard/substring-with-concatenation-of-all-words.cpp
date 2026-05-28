////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `findSubstring`-method of `Solution`-class
/// @details https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
/// You are given a string s and an array of strings words. All the strings of words are of the same length.
///
/// A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.
/// For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings.
/// "acdbef" is not a concatenated substring because it is not the concatenation of any permutation of words. Return the starting indices of all the
/// concatenated substrings in s. You can return the answer in any order.
///
/// Example 1:
///   Input: s = "barfoothefoobarman", words = ["foo","bar"]
///   Output: [0,9]
///   Explanation:
///     Since words.length == 2 and words[i].length == 3, the concatenated substring has to be of length 6.
///     The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
///     The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
///     The output order does not matter. Returning [9,0] is fine too.
///
/// Example 2:
///   Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
///   Output: []
///   Explanation:
///     Since words.length == 4 and words[i].length == 4, the concatenated substring has to be of length 16.
///     There is no substring of length 16 is s that is equal to the concatenation of any permutation of words.
///     We return an empty array.
///
/// Example 3:
///   Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
///   Output: [6,9,12]
///   Explanation:
///     Since words.length == 3 and words[i].length == 3, the concatenated substring has to be of length 9.
///     The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"] which is a permutation of words.
///     The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"] which is a permutation of words.
///     The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"] which is a permutation of words.
///
/// Constraints:
/// 1. 1 <= s.length <= 104
/// 2. 1 <= words.length <= 5000
/// 3. 1 <= words[i].length <= 30
/// 4. s and words[i] consist of lowercase English letters.
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    4.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::pair<std::string, std::vector<std::string>>;
using OutputDataType = std::vector<int>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
        return {};
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
          TestDataType{ InputDataType{ "barfoothefoobarman", { "foo", "bar" }  }, OutputDataType{ 0, 9 } },
          TestDataType{ InputDataType{ "wordgoodgoodgoodbestword", { "word", "good", "best", "word" }  }, OutputDataType{} },
          TestDataType{ InputDataType{ "barfoofoobarthefoobarman", { "bar", "foo", "the" }  }, OutputDataType{ 6, 9, 12 } }
          // additional
          // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input, result] = GetParam();
    auto [s, words] = input;

    ASSERT_LE(s.length(), 100000);
    ASSERT_GE(words.size(), 1);
    ASSERT_LE(words.size(), 5000);
    for (auto itWord = words.begin(); itWord != words.end(); ++itWord) {
        auto wordLength = itWord->length();
        ASSERT_GE(wordLength, 1);
        ASSERT_LE(wordLength, 30);
        if (auto itNextWord = std::next(itWord); itNextWord != words.end()) {
            ASSERT_EQ(itNextWord->length(), wordLength);
        }
    }

    ASSERT_EQ(findSubstring(std::move(s), words), result);
}
} // namespace
