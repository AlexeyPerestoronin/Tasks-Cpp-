/// https://leetcode.com/problems/maximum-subarray/
///
/// Здесь надо использовать алгоритм Кэхэна:
/// https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D1%8D%D1%85%D1%8D%D0%BD%D0%B0

#include <vector>

#include <algorithm>
#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>


namespace {
using InputDataType = std::vector<int>;
using OutputDataType = int;
using TestDataType = std::pair<InputDataType, OutputDataType>;

class Solution {
public:
  int maxSubArray(std::vector<int> &nums) {
    int result = nums[0], buff{0}, local_max = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
      const int num = nums[i];
      local_max = std::max({local_max + buff + num, buff + num, num});
      if (local_max < num) {
        buff = num;
      } else {
        buff = 0;
      }
      result = std::max(local_max, result);
    }
    return result;
  }
};

struct TestSolution : Solution, testing::TestWithParam<TestDataType> {};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      TestSolution,
      ::testing::Values(
          TestDataType{ InputDataType{5,1,5}, OutputDataType{11} },
          TestDataType{ InputDataType{5,-4,5}, OutputDataType{6} },
          TestDataType{ InputDataType{5,-4,20}, OutputDataType{21} },
          TestDataType{ InputDataType{8,-10,5,-4,20}, OutputDataType{21} },
          TestDataType{ InputDataType{8,-19,5,-4,20}, OutputDataType{21} },
          TestDataType{ InputDataType{-2,-1}, OutputDataType{-1} },
          TestDataType{ InputDataType{-2,1,-3,4,-1,2,1,-5,4}, OutputDataType{6} },
          TestDataType{ InputDataType{1}, OutputDataType{1} },
          TestDataType{ InputDataType{5,4,-1,7,8}, OutputDataType{23} }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
  auto [input_data, output_data] = GetParam();
  ASSERT_EQ(maxSubArray(input_data), output_data);
}
} // namespace
