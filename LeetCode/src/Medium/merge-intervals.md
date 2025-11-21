# Solutions:
## №1: Submitted but slow
```cpp
class Solution {
public:
  using Interval = std::vector<int>;
  std::vector<Interval> merge(std::vector<Interval> &intervals) {
    std::sort(intervals.begin(), intervals.end());
    std::vector<Interval> result{};
    for (const auto &interval : intervals) {
      auto it_begin = result.begin();
      auto it_end = result.end();
      auto it_left =
          std::find_if(it_begin, it_end, [&](const Interval &range) -> bool {
            return range[0] <= interval[0] && interval[0] <= range[1];
          });
      auto it_right =
          std::find_if(it_begin, it_end, [&](const Interval &range) -> bool {
            return range[0] <= interval[1] && interval[1] <= range[1];
          });

      if (it_left != it_end && it_right == it_end) {
        (*it_left)[1] = interval[1];
      } else if (it_left == it_end && it_right != it_end) {
        (*it_right)[0] = interval[0];
      } else if (it_left != it_end && it_right != it_end) {
        if (it_left != it_right) {
          (*it_left)[1] = (*it_right)[1];
          result.erase(it_right);
        }
      } else if (it_left == it_end && it_right == it_end) {
        result.push_back(interval);
      }
    }
    return result;
  }
};
```