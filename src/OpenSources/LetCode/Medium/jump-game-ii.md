# Solution №2 = Time Limit Exceeded
```cpp
class Solution {
    std::optional<int> min_jumps{};

    bool attempt(const std::vector<int>& nums, size_t position, int jumps_quantity) {
        const auto size = nums.size() - 1;

        if (position == size) {
            min_jumps = std::min(min_jumps.value_or(std::numeric_limits<int>::max()), jumps_quantity);
            return true;
        }

        for (int increment{nums[position]}; increment > 0; --increment) {
            if (position + increment <= size) {
                if (auto next_jump = jumps_quantity + 1; attempt(nums, position + increment, next_jump)) {
                    if (min_jumps.value() <= next_jump) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

public:
    int jump(std::vector<int>& nums) {
        attempt(nums, 0, 0);
        return min_jumps.value_or(0);
    }
};
```

# Solution №1 = Time Limit Exceeded
```cpp
class Solution {
    std::optional<int> min_jumps{};

    void attempt(const std::vector<int>& nums, size_t position, int jumps_quantity) {
        if (const auto size = nums.size() - 1; position == size) {
            min_jumps = std::min(min_jumps.value_or(std::numeric_limits<int>::max()), jumps_quantity);
        } else if (position > size) {
            return;
        } else {
            for (int increment{1}; increment <= nums[position]; ++increment) {
                attempt(nums, position + increment, jumps_quantity + 1);
            }
        }
    }

public:
    int jump(std::vector<int>& nums) {
        attempt(nums, 0, 0);
        return min_jumps.value();
    }
};
```