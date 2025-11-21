# Answer
## Solution
```cpp
  class Solution {
    public:
    int divide(int dividend, int divisor) {
      // NOTE: dividend = (quotient) * divisor + remainder
      bool needInverse = (dividend > 0) ^ (divisor > 0);
      dividend = std::abs(dividend);
      divisor = std::abs(divisor);
      int quotient{ 0 };

      if (divisor == 1) {
        quotient = dividend;
      } else {
        while (dividend >= divisor) {
          int offset{ 0 };
          while ((divisor << (offset + 1)) < dividend) {
            ++offset;
          }
          dividend -= divisor << offset;
          quotient += (offset > 0 ? 2 << --offset : 1);
        }
      }

      if (quotient == std::numeric_limits<int>::min()) {
        return needInverse ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
      }
      return needInverse ? -quotient : quotient;
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
          TestDataType{ InputDataType{ 10, 3 }, OutputDataType{ 3 } },
          TestDataType{ InputDataType{ -7, 3 }, OutputDataType{ -2 } },
          // additional
          TestDataType{ InputDataType{ 7, -3 }, OutputDataType{ -2 } },
          TestDataType{ InputDataType{ 1, -1 }, OutputDataType{ -1 } },
          TestDataType{ InputDataType{ -1, 1 }, OutputDataType{ -1 } },
          TestDataType{ InputDataType{ 7, 8 }, OutputDataType{ 0 } },
          TestDataType{ InputDataType{ -7, 8 }, OutputDataType{ 0 } },
          TestDataType{ InputDataType{ 7, -8 }, OutputDataType{ 0 } },
          TestDataType{ InputDataType{ -7, -8 }, OutputDataType{ 0 } },
          TestDataType{ InputDataType{ 1000, 10 }, OutputDataType{ 100 } },
          TestDataType{ InputDataType{ std::numeric_limits<int>::min(), -1 }, OutputDataType{ std::numeric_limits<int>::max() } },
          TestDataType{ InputDataType{ std::numeric_limits<int>::min(), 1 }, OutputDataType{ std::numeric_limits<int>::min() } },
          TestDataType{ InputDataType{ std::numeric_limits<int>::max(), -1 }, OutputDataType{ -std::numeric_limits<int>::max() } },
          TestDataType{ InputDataType{ std::numeric_limits<int>::max(), 1 }, OutputDataType{ std::numeric_limits<int>::max() } }
          // TODO: create additional tests...
  ));
  // clang-format on
```