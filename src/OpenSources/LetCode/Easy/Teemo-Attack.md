# Answer
## Solution
```cpp
class Solution {
    public:
    int findPoisonedDuration(std::vector<int>& timeSeries, int duration) {
      //implement solution here
      int result = duration;
      for (int i = 0; i < timeSeries.size() - 1; ++i) {
        if (timeSeries[i] + duration > timeSeries[i + 1])
          result += timeSeries[i + 1] - timeSeries[i];
        else
          result += duration;
      }
      return result;
    }
  };
```

## Tests
```
INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
      // from example
      TestDataType{ InputDataType{ {1, 4} ,2 }, OutputDataType{ 4 } },
      TestDataType{ InputDataType{ {1, 2}, 2 }, OutputDataType{ 3 } },
      TestDataType{ InputDataType{ {1, 4, 6, 8}, 3 }, OutputDataType{ 10 } }
      // additional
      // TODO: create additional tests...
  ));
```