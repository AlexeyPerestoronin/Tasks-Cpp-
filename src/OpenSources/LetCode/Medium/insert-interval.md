# Solution #2 - Accepted but slow
```cpp
class Solution {
public:
    using VecInt = std::vector<int>;
    using VecVecInt = std::vector<VecInt>;

    bool tryIntersect(VecInt& l_interval, VecInt& r_interval) {
        if (l_interval[0] <= r_interval[0] && r_interval[0] <= l_interval[1]) {
            l_interval[0] = r_interval[0] = std::min(l_interval[0], r_interval[0]);
            r_interval[1] = l_interval[1] = std::max(l_interval[1], r_interval[1]);
            return true;
        }
        return false;
    }

    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        intervals.push_back(newInterval);
        std::sort(intervals.begin(), intervals.end());

        auto checkToRemove = [&]() {
            return std::adjacent_find(
                intervals.begin(), intervals.end(), [&](auto& l_interval, auto& r_interval) -> bool { return tryIntersect(l_interval, r_interval); });
        };

        for (auto remove_it = checkToRemove(); remove_it != intervals.end(); remove_it = checkToRemove()) {
            intervals.erase(remove_it);
        }

        return intervals;
    }
};
```

# Solution №1 - Error with `TestDataType{ InputDataType{ { {1,3},{9,11} }, {5,7} }, OutputDataType{{1,3},{5,7},{9,11}}},`
```cpp
class Solution {
public:
    using VecInt = std::vector<int>;
    using VecVecInt = std::vector<VecInt>;

    std::vector<std::vector<int>> insert(std::vector<std::vector<int>>& intervals, std::vector<int>& newInterval) {
        {
            auto new_end_it = std::remove_if(intervals.begin(), intervals.end(), [&](const auto& interval) -> bool { return newInterval[0] < interval[0] && interval[1] < newInterval[1]; });
            intervals.erase(new_end_it, intervals.end());
            if (intervals.empty()) {
                intervals.push_back(newInterval);
                return intervals;
            }
        }

        const auto try_intersect = [](auto& l_interval, auto& r_interval) -> bool {
            if (l_interval[0] <= r_interval[0] && l_interval[1] >= r_interval[0]) {
                l_interval[1] = r_interval[1];
                r_interval[0] = l_interval[0];
                return true;
            }
            return false;
        };

        auto remove_inside_it = std::adjacent_find(intervals.begin(), intervals.end(), [&](auto& l_interval, auto& r_interval) -> bool {
            try_intersect(l_interval, newInterval);
            try_intersect(newInterval, r_interval);
            return try_intersect(l_interval, r_interval);
        });

        if (remove_inside_it != intervals.end()) {
            intervals.erase(remove_inside_it);
        }

        return intervals;
    }
};
```