////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `isMatch`-method of `Solution`-class
/// @details https://leetcode.com/problems/regular-expression-matching/
/// Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
///     '.' Matches any single character.​​​​
///     '*' Matches zero or more of the preceding element.
///
/// The matching should cover the entire input string (not partial).
///
/// Example 1:
///  Input:
///    s = "aa", p = "a"
///  Output:
///    false
///  Explanation:
///    "a" does not match the entire string "aa".
///
/// Example 2:
///   Input:
///     s = "aa", p = "a*"
///   Output:
///     true
///   Explanation:
///     '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".
///
/// Example 3:
///   Input:
///     s = "ab", p = ".*"
///   Output:
///     true
///   Explanation:
///     ".*" means "zero or more (*) of any character (.)".
///
/// Constraints:
/// 1. 1 <= s.length <= 20
/// 2. 1 <= p.length <= 30c
/// 3. s contains only lowercase English letters.
/// 4. p contains only lowercase English letters, '.', and '*'.
/// 5. It is guaranteed for each appearance of the character '*', there will be a previous valid character to match.
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    27.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <optional>
#include <algorithm>

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

namespace {
  using InputDataType = std::pair<std::string, std::string>;
  using OutputDataType = bool;
  using TestDataType = std::tuple<InputDataType, OutputDataType>;

  class Solution {
    public:
    bool isMatch(std::string s, std::string p) {
      // TODO: implement this method...
      return true;
    }
  };

  struct TestSolution
      : Solution
      , testing::TestWithParam<TestDataType> {};

  // clang-format off
    INSTANTIATE_TEST_SUITE_P(
        GeneralTestData,
        TestSolution,
        ::testing::Values(
            // from example
            TestDataType{ InputDataType{ "aa", "a" }, OutputDataType{ false } },
            TestDataType{ InputDataType{ "aa", "a*" }, OutputDataType{ true } }
            // additional
            // TODO: create additional tests...
    ));
  // clang-format on

  TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    auto& [s, p] = inputData;
    ASSERT_GE(s.length(), 1);
    ASSERT_LE(s.length(), 20);
    ASSERT_GE(p.length(), 1);
    ASSERT_LE(p.length(), 30);
    ASSERT_EQ(isMatch(s, p), outputData);
  }
} // namespace
