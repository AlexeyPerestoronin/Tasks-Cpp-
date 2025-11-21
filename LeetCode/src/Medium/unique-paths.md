# Solution №1 - Time Limit Exceed
```cpp
class Solution {
    int unique_paths{};

    void detect(int i, int j, int I, int J) {
        if (i == I && j == J) {
            ++unique_paths;
        } else {
            if (i < I) {
                detect(i + 1, j, I, J);
            }

            if (j < J) {
                detect(i, j + 1, I, J);
            }
        }
    }

public:
    int uniquePaths(int m, int n) {
        detect(0, 0, m - 1, n - 1);
        return unique_paths;
    }
};
```