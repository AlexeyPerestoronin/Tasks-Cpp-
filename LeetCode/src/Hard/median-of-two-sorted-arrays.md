# Answer
## Solution
```cpp
class Solution {
  public:
  double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    std::multiset<int> nums{};
    nums.insert(nums1.begin(), nums1.end());
    nums.insert(nums2.begin(), nums2.end());
    const auto size = nums.size();
    auto middleIt = std::next(nums.begin(), size / 2);
    if (size % 2 == 1)
      return *middleIt;
    return static_cast<double>(*middleIt + *(--middleIt)) / 2;
  }
};
```

## Tests
```cpp
// clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      TestSolution,
      ::testing::Values(
          // from example
          TestDataType{ InputDataType{ { 1, 3 }, { 2 } }, OutputDataType{ 2 } },
          TestDataType{ InputDataType{ { 1, 2 }, { 3, 4 } }, OutputDataType{ 2.5 } },
          // additional
          TestDataType{ InputDataType{ {}, { 1 } }, OutputDataType{ 1 } },
          TestDataType{ InputDataType{ { 2 }, {} }, OutputDataType{ 2 } },
          TestDataType{ InputDataType{ { 2 }, { 2 } }, OutputDataType{ 2 } },
          TestDataType{ InputDataType{ {}, { 2, 2 } }, OutputDataType{ 2 } },
          TestDataType{ InputDataType{ { 2 }, { 2, 2 } }, OutputDataType{ 2 } },
          TestDataType{ InputDataType{ { 1, 2, 2, 2, 2 }, { 5, 6, 6, 7, 3, 1 } }, OutputDataType{ 2 } }
          // TODO: create additional tests...
  ));
// clang-format on
```