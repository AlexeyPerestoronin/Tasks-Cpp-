# Solutions:
## №1: Time limit exceeded
```cpp
class Solution {
public:
  int maxSubArray(std::vector<int> &nums) {
    int result = std::numeric_limits<int>::min();
    for (auto it_stop = nums.begin(); it_stop <= nums.end(); ++it_stop) {
      for (auto it_start = nums.begin(); it_start < it_stop; ++it_start) {
        result = std::max(std::accumulate(it_start, it_stop, int{0}), result);
      }
    }
    return result;
  }
};
```