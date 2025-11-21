# Answer
## Solution
```cpp
class Solution {
  using Str = std::string;
  using RegExrType = std::pair<std::optional<char>, bool>;
  using VecRegExrType = std::vector<RegExrType>;

  public:
  bool isMatch(Str::iterator sFrom, Str::iterator sTo, VecRegExrType::iterator pFrom, VecRegExrType::iterator pTo) {
    if (sFrom == sTo) {
      if (pFrom != pTo) {
        if (pFrom->second) {
          return isMatch(sFrom, sTo, std::next(pFrom), pTo);
        } else {
          return false;
        }
      }
      return true;
    }

    if (sFrom != sTo && pFrom != pTo)
      if (!pFrom->second) {
        if (char ch = *sFrom; ch == pFrom->first.value_or(ch)) {
          return isMatch(std::next(sFrom), sTo, std::next(pFrom), pTo);
        }
      } else {
        if (char ch = *sFrom; ch == pFrom->first.value_or(ch)) {
          if (!isMatch(std::next(sFrom), sTo, pFrom, pTo) && !isMatch(sFrom, sTo, std::next(pFrom), pTo)) {
            return isMatch(std::next(sFrom), sTo, std::next(pFrom), pTo);
          }
          return true;
        } else {
          return isMatch(sFrom, sTo, std::next(pFrom), pTo);
        }
      }

    return false;
  }

  bool isMatch(std::string s, std::string p) {
    VecRegExrType reg{};
    for (size_t i{ 0 }; i < p.length(); ++i) {
      if (p[i] != '*') {
        if (char ch = p[i]; ch != '.') {
          reg.emplace_back(ch, false);
        } else {
          reg.emplace_back(std::nullopt, false);
        }
      } else {
        auto last = reg.rbegin();
        last->second = true;
        if (auto previous = std::next(last); previous != reg.rend())
          if (previous->first == last->first && previous->second == last->second)
            reg.pop_back();
      }
    }

    return isMatch(s.begin(), s.end(), reg.begin(), reg.end());
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
        TestDataType{ InputDataType{ "aa", "a" }, OutputDataType{ false } },
        TestDataType{ InputDataType{ "aa", "a*" }, OutputDataType{ true } },
        // additional
        TestDataType{ InputDataType{ "aa", "." }, OutputDataType{ false } },
        TestDataType{ InputDataType{ "aa", "." }, OutputDataType{ false } },
        TestDataType{ InputDataType{ "aa", ".." }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aa", ".*" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "a", "ab*" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "ab", ".*c" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aaa", ".." }, OutputDataType{ false } },
        TestDataType{ InputDataType{ "aaa", "..." }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aac", "a*c" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aac", "a*." }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "a", "ab*c*" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aabbcc", ".*" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "bbbd", "a*.*d" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aabbcc", ".*d" }, OutputDataType{ false } },
        TestDataType{ InputDataType{ "bbbba", ".*a*a" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "bbbba", ".*a*a*a" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*b" }, OutputDataType{ true } },
        TestDataType{ InputDataType{ "aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c" }, OutputDataType{ false } }
        // TODO: create additional tests...
));
// clang-format on
```