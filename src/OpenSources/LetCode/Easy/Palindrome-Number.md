# Answer
## Solution
```cpp
class Solution {
    public:
    bool isPalindrome(int x) 
    {
        //negative numbers are not palindrome
        // numbers ending with 0 neither
        if(x < 0 || (x % 10 == 0 && x != 0))
            return false;
        
        int reverted = 0, unit = 0;
        while(x > reverted)
        {
            unit = x % 10;
            
            reverted = reverted * 10 + unit;
            
            x /= 10;
        }
        
        // this is for the case when digit count is odd, 
        // to remove the number in the middle
        return x == reverted || x == reverted / 10;
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
      TestDataType{ InputDataType{ 121 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ -121 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ 10 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ -1001 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ 10 }, OutputDataType{ false } },
      TestDataType{ InputDataType{ 101 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ 123321 }, OutputDataType{ true } },
      TestDataType{ InputDataType{ -123321 }, OutputDataType{ false } }
      // additional
      // TODO: create additional tests...
  ));
```