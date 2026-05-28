# Answer
## Solution
```cpp
class Solution {
  using SetStr = std::set<std::string>;

  public:
  static size_t compute(SetStr::iterator itFrom, SetStr::iterator itTo, const std::string& str) {
    size_t result = str.size();
    if (result < 26)
      for (; itFrom != itTo; ++itFrom) {
        std::string loc = str + *itFrom;
        if (std::sort(loc.begin(), loc.end());
            std::adjacent_find(loc.begin(), loc.end(), [](char ch1, char ch2) { return ch1 == ch2; })
            == loc.end())
          result = std::max(result, compute(std::next(itFrom), itTo, str + *itFrom));
      }
    return result;
  }

  int maxLength(std::vector<std::string>& arr) {
    SetStr strings{};
    for (auto& str : arr)
      if (std::sort(str.begin(), str.end());
          std::adjacent_find(str.begin(), str.end(), [](char ch1, char ch2) { return ch1 == ch2; }) == str.end())
        strings.insert(std::move(str));

    size_t result{ 0 };
    for (auto itBegin = strings.begin(), itEnd = strings.end(); itBegin != itEnd; ++itBegin)
      result = std::max(result, compute(itBegin, itEnd, std::string{}));
    return static_cast<int>(result);
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
        TestDataType{ InputDataType{ "un", "iq", "ue" }, OutputDataType{ 4 } },
        TestDataType{ InputDataType{ "cha", "r", "act", "ers" }, OutputDataType{ 6 } },
        TestDataType{ InputDataType{ "abcdefghijklmnopqrstuvwxyz" }, OutputDataType{ 26 } },
        // additional
        TestDataType{ InputDataType{}, OutputDataType{ 0 } },
        TestDataType{ InputDataType{ "a", "b" }, OutputDataType{ 2 } },
        TestDataType{ InputDataType{ "aa", "b" }, OutputDataType{ 1 } },
        TestDataType{ InputDataType{ "aa", "bb" }, OutputDataType{ 0 } },
        TestDataType{ InputDataType{ "aa", "bb", "c" }, OutputDataType{ 1 } },
        TestDataType{ InputDataType{ "s", "sa", "m", "e", "mu", "ei" }, OutputDataType{ 6 } },
        TestDataType{ InputDataType{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p" }, OutputDataType{ 16 } },
        TestDataType{ InputDataType{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "pyt" }, OutputDataType{ 18 } },
        TestDataType{ InputDataType{ "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "p", "pyt" }, OutputDataType{ 17 } },
        TestDataType{ InputDataType{ "aa", "b", "cc", "d", "ee", "f", "gg", "h", "ii", "j", "kk", "l", "mm", "n", "oo", "pxyz" }, OutputDataType{ 11 } },
        TestDataType{ InputDataType{ "ab", "ba", "cd", "dc", "ef", "fe", "gh", "hg", "ij", "ji", "kl", "lk", "mn", "nm", "op", "po" }, OutputDataType{ 16 } },
        TestDataType{ InputDataType{ "abcdefghijklm","bcdefghijklmn","cdefghijklmno","defghijklmnop","efghijklmnopq","fghijklmnopqr","ghijklmnopqrs","hijklmnopqrst","ijklmnopqrstu","jklmnopqrstuv","klmnopqrstuvw","lmnopqrstuvwx","mnopqrstuvwxy","nopqrstuvwxyz","opqrstuvwxyza","pqrstuvwxyzab"}, OutputDataType{ 26 } }
));
// clang-format on
```