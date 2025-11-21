# Answer
## Solution
```cpp
  class Solution {
    public:
        void rotate(std::vector<std::vector<int>>& matrix) {
        //First compute the transposed matrix.
        for (unsigned int row = 0; row < matrix.size(); ++row)
          for (unsigned int col = row; col < matrix[row].size(); ++col)
            std::swap(matrix[col][row], matrix[row][col]);
                           // 0 0 <-> 0 0
                           // 0 1 <-> 1 0
                           // 0 2 <-> 2 0
         //Next reverse line values.
        for (int row = 0; row < matrix.size(); ++row)
          std::reverse(matrix[row].begin(), matrix[row].end());
      }
  };
```
