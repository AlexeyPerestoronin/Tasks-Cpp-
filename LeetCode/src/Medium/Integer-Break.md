# Answer
## Solution
```cpp
class Solution {
  public:
  int integerBreak(int n) 
    {
        //basic cases
        if(n == 2)
            return 1;
        if(n == 3)
            return 2;
        
        int prod = 1;
        
        //factorizing with smaller numbers will give a higher multiplied value
        //we omit the 1s because they don't modify the final solution
        while(n > 0)
        {
            if(n == 4)
            {
                prod *= 4;
                n -= 4;
            }
            else if(n == 2)
            {
                prod *= 2;
                n -= 2;
            }
            else
            {
                prod *= 3;
                n -= 3;
            }
        }
        return prod;
    }
};
```

## Tests
```cpp
INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
      // from example
      TestDataType{ InputDataType{ 2 }, OutputDataType{ 1 } },
      TestDataType{ InputDataType{ 10 }, OutputDataType{ 36 } },
      TestDataType{ InputDataType{ 6 }, OutputDataType{ 9 } },
      TestDataType{ InputDataType{ 20 }, OutputDataType{ 1458 } },
      TestDataType{ InputDataType{ 15 }, OutputDataType{ 243 } },
      TestDataType{ InputDataType{ 50 }, OutputDataType{ 86093442 } }
      // additional
      // TODO: create additional tests...
  ));
```