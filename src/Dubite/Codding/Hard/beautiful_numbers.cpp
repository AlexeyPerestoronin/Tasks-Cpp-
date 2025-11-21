////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief implement `beautifulNumber`-method of `Solution`-class that computes the number of 13-digit beautiful numbers
/// with leading zeros in the thirteenth number system.
///
/// @details
/// In this problem, we will consider 13-digit numbers in the thirteen-decimal system (digits 0,1,2,3,4,5,6,7,8,9,A,B,C)
/// with leading zeros.
///
/// For example, ABA98859978C0, 6789110551234, 0000007000000
///
/// We call a number beautiful if the sum of its first six digits is equal to the sum of the last six digits.
///
/// Example:
/// The number 0055237050A00 is beautiful because 0+0+5+5+2+3 = 0+5+0+A+0+0
/// The number 1234AB988BABA is ugly because 1+2+3+4+A+B != 8+8+B+A+B+A
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    16.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

namespace {
  using InputDataType = std::pair<char, size_t>;
  using OutputDataType = uint64_t;
  using TestDataType = std::pair<InputDataType, OutputDataType>;

  class Solution {
    protected:
    char dimension{};

    public:
    uint64_t beautifulNumber(size_t i_length) {
      // TODO: implement this method...
      return 0ui64;
    }
  };

  struct TestSolution
      : Solution
      , testing::TestWithParam<TestDataType> {
    void SetUp() override {
      dimension = GetParam().first.first;
    }
  };

  // clang-format off
    INSTANTIATE_TEST_SUITE_P(
        GeneralTestData,
        TestSolution,
        ::testing::Values(
            // Dimension = 'D' = 13
            TestDataType{ InputDataType{ 'D', 2 }, OutputDataType{ 13 } },
            TestDataType{ InputDataType{ 'D', 3 }, OutputDataType{ 169 } },
            TestDataType{ InputDataType{ 'D', 4 }, OutputDataType{ 1033 } },
            TestDataType{ InputDataType{ 'D', 5 }, OutputDataType{ 13429 } },
            TestDataType{ InputDataType{ 'D', 13 }, OutputDataType{ 198555497257 } }
            // TODO: create additional tests...
    ));
  // clang-format on

  TEST_P(TestSolution, Test1) {
    const auto& [dimensionAndLength, quantity] = GetParam();
    const auto& [dimension, length] = dimensionAndLength;
    ASSERT_TRUE(dimension >= '0' && (dimension <= '9' || (dimension >= 'A' && dimension <= 'Z')));
    ASSERT_LE(length, 13);
    ASSERT_EQ(beautifulNumber(length), quantity);
  }
} // namespace
