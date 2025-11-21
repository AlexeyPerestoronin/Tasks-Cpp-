////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Your task it to implement the method `myAtoi` of `Solution`-class
/// @details without usage of any STL's function/classes, implement the function of conversion an `str`-string to integer digit.
///
/// Constraints:
/// 1. 0 <= len(str) <= 10
/// 2. 0 <= str[i] <= 9
/// 3. 0 < str[0] <= 9
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    15.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

namespace {
  using InputDataType = std::string;
  using OutputDataType = uint64_t;
  using TestDataType = std::tuple<InputDataType, OutputDataType>;

  class Solution {
    public:
    uint64_t myAtoi(const char* i_str) {
      // TODO: implement this method...
      return 0;
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
            TestDataType{ InputDataType{ "8" }, OutputDataType{ 8 } },
            TestDataType{ InputDataType{ "123" }, OutputDataType{ 123 } }
            // additional
            // TODO: create additional tests...
    ));
  // clang-format on

  TEST_P(TestSolution, Test1) {
    auto [str, res] = GetParam();
    ASSERT_GE(str.length(), 0);
    ASSERT_LE(str.length(), 10);
    for (size_t i{ 0 }; i < str.length(); ++i) {
      int digit{ std::stoi(std::string{ str[i] }) };
      if (i != 0) {
        ASSERT_GE(digit, 0);
      } else {
        ASSERT_GT(digit, 0);
      }
      ASSERT_LE(digit, 9);
    }
    ASSERT_EQ(myAtoi(str.c_str()), res);
  }
} // namespace
