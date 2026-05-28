# Answer
## Solution
```cpp
class Solution {
    public:
    std::vector<int> findErrorNums(std::vector<int>& nums) {
        std::map<int, int> valueToQuantity{};
        for (const auto value : nums)
            ++valueToQuantity[value];

        std::vector<int> twice{};
        std::vector<int> absent{};
        for (int expected{ 1 }; expected <= nums.size(); ++expected)
            if (valueToQuantity[expected] == 2)
                twice.push_back(expected);
            else if (valueToQuantity[expected] == 0)
                absent.push_back(expected);

        twice.insert(twice.end(), absent.begin(), absent.end());
        return twice;
    }
};
```

## Tests
```
// clang-format off
INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
        // from example
        TestDataType{ InputDataType{ 1, 2, 2, 4 }, OutputDataType{ 2, 3 } },
        TestDataType{ InputDataType{ 1, 1 }, OutputDataType{ 1, 2 } },
        // additional
        TestDataType{ InputDataType{}, OutputDataType{} },
        TestDataType{ InputDataType{ 1 }, OutputDataType{} },
        TestDataType{ InputDataType{ 2 }, OutputDataType{ 1 } },
        TestDataType{ InputDataType{ 1, 2, 3, 4, 5, 6 }, OutputDataType{} },
        TestDataType{ InputDataType{ 3, 2, 2 }, OutputDataType{ 2, 1 } },
        TestDataType{ InputDataType{ 3, 2, 2, 1, 4 }, OutputDataType{ 2, 5 } }
));
// clang-format on
```