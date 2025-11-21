# Solution №1 - Accepted but slow
```cpp
class Solution {
    int k;
    std::vector<int> digits{};
    std::vector<std::vector<int>> combinations{};

    void add(size_t i, std::vector<int> combination) {
        if (combination.size() == k) {
            combinations.push_back(std::move(combination));
            return;
        }

        for (; i < digits.size(); ++i) {
            auto next_combination = combination;
            next_combination.push_back(digits[i]);
            add(i + 1, std::move(next_combination));
        }
    }

public:
    std::vector<std::vector<int>> combine(int n, int k) {
        this->k = k;
        for (size_t i = 1; i <= n; ++i) {
            digits.push_back(i);
        }

        add(0, std::vector<int>{});
        return combinations;
    }
};
```