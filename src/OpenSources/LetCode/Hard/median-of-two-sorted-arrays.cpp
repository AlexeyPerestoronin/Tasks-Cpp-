////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `findMedianSortedArrays`-method of `Solution`-class
/// @details https://leetcode.com/problems/median-of-two-sorted-arrays/
/// Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
///
/// The overall run time complexity should be O(log(m + n)).
///
/// Example 1:
///   Input:
///     nums1 = [1, 3]
///     nums2 = [2]
///  Output:
///    2.00000
///  Explanation:
///    merged array = [1, 2, 3]
///    and median is 2.
///
/// Example 2:
///   Input:
///     nums1 = [1, 2]
///     nums2 = [3, 4]
///   Output:
///     2.50000
///   Explanation:
///     merged array = [1, 2, 3, 4]
///     and median is(2 + 3) / 2 = 2.5.
///
///  Constraints:
///  1. nums1.length == m
///  2. nums2.length == n
///  3. 0 <= m <= 1000
///  4. 0 <= n <= 1000
///  5. 1 <= m + n <= 2000
///  6. -10^6 <= nums1[i], nums2[i] <= 10^6
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    27.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <set>
#include <vector>

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

namespace {
  using InputDataType = std::pair<std::vector<int>, std::vector<int>>;
  using OutputDataType = double;
  using TestDataType = std::tuple<InputDataType, OutputDataType>;

  class Solution {
    public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
      // TODO: implement this method...
      return 0.;
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
            TestDataType{ InputDataType{ { 1, 3 }, { 2 } }, OutputDataType{ 2 } },
            TestDataType{ InputDataType{ { 1, 2 }, { 3, 4 } }, OutputDataType{ 2.5 } }
            // additional
            // TODO: create additional tests...
    ));
  // clang-format on

  TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    auto& [nums1, nums2] = inputData;
    const auto size1 = nums1.size(), size2 = nums2.size();
    ASSERT_LE(size1, 1000);
    ASSERT_LE(size2, 1000);
    ASSERT_GE(size1 + size2, 1);
    ASSERT_LE(size1 + size2, 2000);
    ASSERT_NEAR(findMedianSortedArrays(nums1, nums2), outputData, 1e-3);
  }
} // namespace
