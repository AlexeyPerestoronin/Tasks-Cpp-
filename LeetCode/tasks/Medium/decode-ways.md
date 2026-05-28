# Solution 2 = Memory Limit Exceeded
```cpp
class Solution {
    int decoder(size_t i, const std::string s) {
        if (size_t size = s.size(); i == size) {
            return 1;
        } else if (i > size) {
            return 0;
        }

        char ch = s[i];
        if (ch == '0') {
            return 0;
        }

        int res = decoder(i + 1, s);

        if (size_t j = i + 1; j < s.size())
        {
            if (ch == '1' || (ch == '2' && s[j] <= '6')) {
                res += decoder(j + 1, s);
            }
        }

        return res;
    }

public:
    int numDecodings(std::string s) {
        return decoder(0, s);
    }
};

```

# Solution 1 = Time Limit Exceeded
```cpp
class Solution {
    int possible_decoding_results{};

    void decodePossibleCombination(std::string::iterator it_begin, const std::string::iterator& it_end, char prev_ch) {
        if (prev_ch == '0') {
            return;
        }

        if (it_begin == it_end) {
            ++possible_decoding_results;
            return;
        }

        char current_char = *it_begin;
        if (int digit = std::stoi(std::string{prev_ch, current_char}); digit == 10 || digit == 20) {
            if (it_begin + 1 != it_end) {
                decodePossibleCombination(it_begin + 2, it_end, *(it_begin + 1));
            } else {
                ++possible_decoding_results;
            }
        } else if (digit <= 26) {
            decodePossibleCombination(it_begin + 1, it_end, current_char);
            if (it_begin + 1 != it_end) {
                decodePossibleCombination(it_begin + 2, it_end, *(it_begin + 1));
            } else {
                ++possible_decoding_results;
            }
        } else {
            decodePossibleCombination(it_begin + 1, it_end, current_char);
        }
    }

public:
    int numDecodings(std::string s) {
        decodePossibleCombination(++s.begin(), s.end(), s.front());
        return possible_decoding_results;
    }
};
```