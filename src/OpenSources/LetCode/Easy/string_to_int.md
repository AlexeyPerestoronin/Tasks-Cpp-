# Answer
## Solution
```cpp
  class Solution {
    public:
    uint64_t myAtoi(const char* i_str) {
      uint64_t result{};
      for (int i{ 0 }; i_str[i] != '\0'; ++i) {
        result *= 10;
        result += int(i_str[i] - '0');
      }
      return result;
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
            TestDataType{ InputDataType{ "8" }, OutputDataType{ 8 } },
            TestDataType{ InputDataType{ "123" }, OutputDataType{ 123 } },
            // additional
            TestDataType{ InputDataType{ "" }, OutputDataType{ 0 } },
            TestDataType{ InputDataType{ "123456789" }, OutputDataType{ 123456789 } },
            TestDataType{ InputDataType{ "9999999999" }, OutputDataType{ 9999999999 } }
            // TODO: create additional tests...
    ));
  // clang-format on
```
