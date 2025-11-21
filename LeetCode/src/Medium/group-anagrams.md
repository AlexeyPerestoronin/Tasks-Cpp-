# Answer
## Solution
```cpp
  class Solution {
    public:
    std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
      using MappedResultType = std::map<std::multiset<char>, std::vector<std::string>>;
      MappedResultType mappedResults{};
      for (auto& str : strs)
        mappedResults[{ str.begin(), str.end() }].push_back(std::move(str));

      std::vector<std::vector<std::string>> results{};
      std::transform(
          mappedResults.begin(), mappedResults.end(), std::back_inserter(results),
          [](MappedResultType::value_type& mappedResult) -> std::vector<std::string> {
            return std::move(mappedResult.second);
          });

      return results;
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
        TestDataType{ InputDataType{ "eat", "tea", "tan", "ate", "nat", "bat" }, OutputDataType{ { "bat" }, { "nat", "tan" }, { "ate", "eat", "tea" } } },
        TestDataType{ InputDataType{ "" }, OutputDataType{ { "" } } },
        TestDataType{ InputDataType{ "a" }, OutputDataType{ { "a" } } },
        // additional
        TestDataType{ InputDataType{ "", "" }, OutputDataType{ { "", "" } } },
        TestDataType{ InputDataType{ "abba", "baab", "", "aabb", "", "cdff" }, OutputDataType{ { "abba", "baab", "aabb" }, { "", "" }, { "cdff" } } },
        TestDataType{ InputDataType{ "ddddddddddg", "dgggggggggg" }, OutputDataType{ { "ddddddddddg" }, { "dgggggggggg" } } }
        // TODO: create additional tests...
));
// clang-format on
```