# Answer
## Solution-1
```cpp
class Solution {
    protected:
    char dimension{};

    bool increment(std::string& io_number, size_t i = 1) {
      if (int j = io_number.length() - i; j >= 0) {
        char& d = io_number[j];
        if (d == '9') {
          d = 'A';
        } else {
          ++d;
        }

        if (d < dimension) {
          return true;
        }

        d = '0';
        return increment(io_number, i + 1);
      }
      return false;
    }

    bool isBeautiful(std::string_view i_number) {
      const size_t length = i_number.length();
      const size_t subLength = length / 2;
      std::string_view lSide = i_number.substr(0, subLength);
      std::string_view rSide = i_number.substr(length - subLength);
      int32_t sum{};
      for (char ch : lSide) {
        sum += static_cast<int32_t>(ch);
      }
      for (char ch : rSide) {
        sum -= static_cast<int32_t>(ch);
      }
      return sum == 0i32;
    }

    public:
    uint64_t beautifulNumber(size_t i_length) {
      std::set<std::string> beautifulNumber{};
      std::string number(i_length, '0');
      do {
        if (isBeautiful(number)) {
          beautifulNumber.emplace_hint(beautifulNumber.end(), number);
        }
      } while (increment(number));
      return beautifulNumber.size();
    }
  };
```

## Solution-2
```cpp
  class Solution {
    protected:
    char dimension{};

    bool increment(std::string& io_number, size_t i = 1) {
      if (int j = io_number.length() - i; j >= 0) {
        char& d = io_number[j];
        if (d == '9') {
          d = 'A';
        } else {
          ++d;
        }

        if (d < dimension) {
          return true;
        }

        d = '0';
        return increment(io_number, i + 1);
      }
      return false;
    }

    public:
    uint64_t beautifulNumber(size_t i_length) {
      std::string number(i_length / 2, '0');

      std::unordered_map<int32_t, int32_t> distribution{};

      do {
        int32_t sum{};
        for (char ch : number) {
          sum += static_cast<int32_t>(ch);
        }
        ++distribution[sum];
      } while (increment(number));

      uint64_t result{};

      for (const auto& resIt : distribution) {
        result += (resIt.second * resIt.second);
      }

      if (i_length % 2 != 0) {
        auto mul = static_cast<uint64_t>(dimension - '0');
        if (dimension >= 'A') {
          mul -= static_cast<uint64_t>('A' - '9');
          ++mul;
        }
        result *= mul;
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
            // Dimension = '3' = 3
            TestDataType{ InputDataType{ '3', 2 }, OutputDataType{ 3 } },
            TestDataType{ InputDataType{ '3', 3 }, OutputDataType{ 9 } },
            TestDataType{ InputDataType{ '3', 4 }, OutputDataType{ 19 } },
            TestDataType{ InputDataType{ '3', 5 }, OutputDataType{ 57 } },
            TestDataType{ InputDataType{ '3', 13 }, OutputDataType{ 221367 } },

            // Dimension = 'C' = 12
            TestDataType{ InputDataType{ 'C', 2 }, OutputDataType{ 12 } },
            TestDataType{ InputDataType{ 'C', 3 }, OutputDataType{ 144 } },
            TestDataType{ InputDataType{ 'C', 4 }, OutputDataType{ 844 } },
            TestDataType{ InputDataType{ 'C', 5 }, OutputDataType{ 10128 } },
            TestDataType{ InputDataType{ 'C', 13 }, OutputDataType{ 73159939704 } },
            
            // Dimension = 'D' = 13
            TestDataType{ InputDataType{ 'D', 2 }, OutputDataType{ 13 } },
            TestDataType{ InputDataType{ 'D', 3 }, OutputDataType{ 169 } },
            TestDataType{ InputDataType{ 'D', 4 }, OutputDataType{ 1033 } },
            TestDataType{ InputDataType{ 'D', 5 }, OutputDataType{ 13429 } },
            TestDataType{ InputDataType{ 'D', 13 }, OutputDataType{ 198555497257 } },

            // Dimension = 'Z' = 35
            TestDataType{ InputDataType{ 'Z', 2 }, OutputDataType{ 35 } },
            TestDataType{ InputDataType{ 'Z', 3 }, OutputDataType{ 1225 } },
            TestDataType{ InputDataType{ 'Z', 4 }, OutputDataType{ 23331 } },
            TestDataType{ InputDataType{ 'Z', 5 }, OutputDataType{ 816585 } }
            
            // TestDataType{ InputDataType{ 'Z', 13 }, OutputDataType{ ??? } }
    ));
  // clang-format on
  // clang-format on
```