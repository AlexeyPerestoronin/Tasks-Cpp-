# Solution №4
```cpp
class Solution {
    using Combination = std::vector<int>;
    using UniqueCombinations = std::set<Combination>;
    using CombinationStorage = std::map<int, int>;

    UniqueCombinations combinations;

    Combination extend(Combination combination, int value, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            combination.push_back(value);
        }
        return combination;
    }

    void find(CombinationStorage::iterator it_being, const CombinationStorage::iterator& it_end, Combination combination, int target) {
        if (it_being != it_end) {
            const auto& [value, amount] = *it_being;
            for (int quantity = 0; quantity <= amount; ++quantity) {
                if (auto increment = value * quantity; increment < target) {
                    find(std::next(it_being), it_end, extend(combination, value, quantity), target - increment);
                } else if (increment == target) {
                    combinations.emplace(extend(combination, value, quantity));
                }
            }
        }
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        auto it_end = std::remove_if(candidates.begin(), candidates.end(), [&](int value) { return value > target; });
        std::sort(candidates.begin(), it_end);
        CombinationStorage storage;
        for (auto it_begin = candidates.begin(); it_begin != it_end; ++it_begin) {
            storage[*it_begin]++;
        }

        find(storage.begin(), storage.end(), Combination{}, target);

        std::vector<std::vector<int>> result(combinations.begin(), combinations.end());
        return result;
    }
};
```

# Solution №3 - [BISHT solution](https://leetcode.com/problems/combination-sum-ii/solutions/5629476/bisht-solution/)
```cpp
class Solution {
public:
    int n;
    std::set<std::vector<int>> combinations; // To store unique combinations

    void find(int index, std::vector<int>& candidates, int target, std::unordered_map<int, int>& mp, std::vector<int>& combination) {
        if (target == 0) {
            // Add the combination to the set if it meets the target
            combinations.insert(combination);
            return;
        }

        if (index >= n || target < 0) {
            return;
        }

        // Include the current element only if it's valid
        int currentNum = candidates[index];
        int maxCount = mp[currentNum];
        
        for (int i = 0; i <= maxCount; ++i) {
            // Try to use 'i' occurrences of the current number
            if (target - currentNum * i >= 0) {
                std::vector<int> tempCopy = combination;
                tempCopy.insert(tempCopy.end(), i, currentNum);
                find(index + maxCount , candidates, target - currentNum * i, mp, tempCopy);
            }
        }
    }

    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        n = candidates.size();
        std::sort(candidates.begin(), candidates.end()); // Sort to handle duplicates
        std::unordered_map<int, int> mp;
        for (int i : candidates) mp[i]++;
        std::vector<int> combination;
        find(0, candidates, target, mp, combination);

        // Convert set to vector
        std::vector<std::vector<int>> ans(combinations.begin(), combinations.end());
        return ans;
    }
};
```

# Solution №2 = Time Limit Exceeded
```cpp
class Solution {
    using VecInt = std::vector<int>;
    using SetVecInt = std::set<VecInt>;
    using VecVecInt = std::vector<std::vector<int>>;

public:
    SetVecInt combinations{};

    VecVecInt finish() {
        VecVecInt result{};
        std::move(combinations.begin(), combinations.end(), std::back_inserter(result));
        return result;
    }

    void search(VecInt::iterator it_begin, VecInt::iterator it_end, VecInt combination, int target) {
        if (target <= 0) {
            if (target == 0) {
                combinations.emplace(std::move(combination));
            }
            return;
        } else if (it_begin == it_end || std::accumulate(it_begin, it_end, 0) < target) {
            return;
        }

        while (it_begin != it_end) {
            auto next_combination = combination;
            next_combination.emplace_back(*it_begin);
            search(it_begin + 1, it_end, std::move(next_combination), target - *it_begin);
            search(it_begin + 1, it_end, combination, target);
            ++it_begin;
        }
    }

    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        auto it_end = std::remove_if(candidates.begin(), candidates.end(), [&](int value) { return value > target; });
        std::sort(candidates.begin(), it_end);
        search(candidates.begin(), it_end, VecInt{}, target);
        return finish();
    }
};
```

# Solution №1 = Time Limit Exceeded
```cpp
class Solution {
    using VectorInt = std::vector<int>;
    using SetVecInt = std::set<VectorInt>;

    void detectSum(SetVecInt& results, VectorInt result, VectorInt::iterator&& start_it, const VectorInt::iterator& end_it, int target) {
        while (start_it != end_it) {
            auto value = *start_it;
            if (value > target) {
                break;
            }

            auto local_result = VectorInt{result};
            local_result.push_back(value);

            if (value < target) {
                detectSum(results, std::move(local_result), start_it + 1, end_it, target - value);
            } else {
                results.emplace(std::move(local_result));
                break;
            }

            ++start_it;
        }
    }

public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result{};

        std::sort(candidates.begin(), candidates.end());

        if (auto total_sum = std::accumulate(candidates.begin(), candidates.end(), 0); total_sum < target) {
            return result;
        } else if (total_sum == target) {
            result.push_back(candidates);
            return result;
        }

        SetVecInt set_result{};
        detectSum(set_result, VectorInt{}, candidates.begin(), candidates.end(), target);

        result.reserve(set_result.size());
        std::move(set_result.begin(), set_result.end(), std::back_inserter(result));
        return result;
    }
};
```