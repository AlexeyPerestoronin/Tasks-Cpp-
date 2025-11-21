# Answer
## Solution 1 (Brute Force, $O$($n^2$))
```cpp
class Solution {
    public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        //create a result vector
        vector<int> res;

        //for each number
        for(int i = 0; i < nums.size(); i++)
        {
            //for each other subsequent number
            for(int j = i + 1; j < nums.size(); j++)
            {
                //if the difference is our target, store it and return it
                if(target - nums[j] == nums[i])
                {
                    res.push_back(i);
                    res.push_back(j);
                    return res;
                }
            }
        }

        //if we didn't find an answer the vector will be empty
        return res;
    }
};
```
## Solution 2 (Faster, $O$($Kn$))
```cpp
class Solution {
    public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) 
    {
        //create a map where we will store the already visited and non valid answers
        std::unordered_map<int, int> counted;

        //for every number
        for(int i = 0; i < nums.size(); i++)
        {
            //compute it's complement
            int complement = target - nums[i];

            //if the complement is stored in our map
            if(counted.count(complement))
                //return it along with the index of the current iteration
                return {counted.at(complement), i};
            
            //add value as visited
            counted[nums[i]] = i;
        }

        //if we didn't find an answer we return an empty vector
        return {};
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
      TestDataType{ InputDataType{ {2, 7, 11, 15}, 9}, OutputDataType{ 0, 1 } },
      TestDataType{ InputDataType{ {3, 2, 4}, 6 }, OutputDataType{ 1, 2} },
      TestDataType{ InputDataType{ {3, 3}, 6 }, OutputDataType{ 0, 1} }
      // additional
      // TODO: create additional tests...
  ));
```