You are given a string s and an array of strings words. All the strings of words are of the same length.

A concatenated substring in s is a substring that contains all the strings of any permutation of words concatenated.
For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated substring because it is not the concatenation of any permutation of words.
Return the starting indices of all the concatenated substrings in s. You can return the answer in any order.

 

Example 1:

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Since words.length == 2 and words[i].length == 3, the concatenated substring has to be of length 6.
The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.
The output order does not matter. Returning [9,0] is fine too.

Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []
Explanation: Since words.length == 4 and words[i].length == 4, the concatenated substring has to be of length 16.
There is no substring of length 16 is s that is equal to the concatenation of any permutation of words.
We return an empty array.

Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
Explanation: Since words.length == 3 and words[i].length == 3, the concatenated substring has to be of length 9.
The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"] which is a permutation of words.
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"] which is a permutation of words.
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"] which is a permutation of words.

 

Constraints:

    1 <= s.length <= 104
    1 <= words.length <= 5000
    1 <= words[i].length <= 30
    s and words[i] consist of lowercase English letters.



# Answer
## Solution-1
```cpp
  class Solution {
    public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
      if (words[0].length() > s.length()) {
        return {};
      }

      std::set<int> result{};
      std::string previousSubstring{};
      std::sort(words.begin(), words.end());
      do {
        std::string substring{};
        for (const auto& word : words) {
          substring.append(word);
        }

        if (substring != previousSubstring) {
          for (size_t offset = s.find(substring, 0); offset != std::string::npos;
               offset = s.find(substring, ++offset)) {
            result.emplace(offset);
          }
        }

        previousSubstring = std::move(substring);
      } while (std::next_permutation(words.begin(), words.end()));

      return std::vector<int>{ result.begin(), result.end() };
    }
  };
```

## Solution-2
```cpp
  class Solution {
    public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
      const size_t wordLength = words[0].length();
      const size_t substringLenth = wordLength * words.size();
      if (substringLenth > s.length()) {
        return {};
      }

      std::unordered_map<std::string_view, std::pair<int, int>> subsequences{};
      for (auto& word : words) {
        ++(subsequences[word].first);
      }

      std::set<int> result{};
      std::string_view stringV{ s };
      for (size_t stingIndex = substringLenth; stingIndex <= stringV.size(); ++stingIndex) {
        for (auto& subsequence : subsequences)
          subsequence.second.second = subsequence.second.first;
        bool isAllowed{ true };
        auto fistIndexOfOccurence = stingIndex - substringLenth;
        auto substringV = stringV.substr(fistIndexOfOccurence, substringLenth);
        for (size_t substringIndex = wordLength; substringIndex <= substringV.size(); substringIndex += wordLength) {
          auto wordV = substringV.substr(substringIndex - wordLength, wordLength);
          if (auto itSubsequence = subsequences.find(wordV); itSubsequence != subsequences.end()) {
            if (--itSubsequence->second.second >= 0) {
              continue;
            }
          }
          isAllowed = false;
          break;
        }

        if (isAllowed) {
          result.emplace(fistIndexOfOccurence);
        }
      }

      return std::vector<int>{ result.begin(), result.end() };
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
          TestDataType{ InputDataType{ "barfoothefoobarman", { "foo", "bar" }  }, OutputDataType{ 0, 9 } },
          TestDataType{ InputDataType{ "wordgoodgoodgoodbestword", { "word", "good", "best", "word" }  }, OutputDataType{} },
          TestDataType{ InputDataType{ "barfoofoobarthefoobarman", { "bar", "foo", "the" }  }, OutputDataType{ 6, 9, 12 } },
          // additional
          TestDataType{ InputDataType{ "barfoothefoobarman", { "foo", "bar", "the" }  }, OutputDataType{ 0, 6 } },
          TestDataType{ InputDataType{ "aaaaaa", { "a", "a", "a" }  }, OutputDataType{ 0, 1, 2, 3 } },
          TestDataType{ InputDataType{ "aaaaaaaa", { "aa", "aa", "aa" }  }, OutputDataType{ 0, 1, 2 } },
          TestDataType{ InputDataType{ "pjzkrkevzztxductzzxmxsvwjkxpvukmfjywwetvfnujhweiybwvvsrfequzkhossmootkmyxgjgfordrpapjuunmqnxxdrqrfgkrsjqbszgiqlcfnrpjlcwdrvbumtotzylshdvccdmsqoadfrpsvnwpizlwszrtyclhgilklydbmfhuywotjmktnwrfvizvnmfvvqfiokkdprznnnjycttprkxpuykhmpchiksyucbmtabiqkisgbhxngmhezrrqvayfsxauampdpxtafniiwfvdufhtwajrbkxtjzqjnfocdhekumttuqwovfjrgulhekcpjszyynadxhnttgmnxkduqmmyhzfnjhducesctufqbumxbamalqudeibljgbspeotkgvddcwgxidaiqcvgwykhbysjzlzfbupkqunuqtraxrlptivshhbihtsigtpipguhbhctcvubnhqipncyxfjebdnjyetnlnvmuxhzsdahkrscewabejifmxombiamxvauuitoltyymsarqcuuoezcbqpdaprxmsrickwpgwpsoplhugbikbkotzrtqkscekkgwjycfnvwfgdzogjzjvpcvixnsqsxacfwndzvrwrycwxrcismdhqapoojegggkocyrdtkzmiekhxoppctytvphjynrhtcvxcobxbcjjivtfjiwmduhzjokkbctweqtigwfhzorjlkpuuliaipbtfldinyetoybvugevwvhhhweejogrghllsouipabfafcxnhukcbtmxzshoyyufjhzadhrelweszbfgwpkzlwxkogyogutscvuhcllphshivnoteztpxsaoaacgxyaztuixhunrowzljqfqrahosheukhahhbiaxqzfmmwcjxountkevsvpbzjnilwpoermxrtlfroqoclexxisrdhvfsindffslyekrzwzqkpeocilatftymodgztjgybtyheqgcpwogdcjlnlesefgvimwbxcbzvaibspdjnrpqtyeilkcspknyylbwndvkffmzuriilxagyerjptbgeqgebiaqnvdubrtxibhvakcyotkfonmseszhczapxdlauexehhaireihxsplgdgmxfvaevrbadbwjbdrkfbbjjkgcztkcbwagtcnrtqryuqixtzhaakjlurnumzyovawrcjiwabuwretmdamfkxrgqgcdgbrdbnugzecbgyxxdqmisaqcyjkqrntxqmdrczxbebemcblftxplafnyoxqimkhcykwamvdsxjezkpgdpvopddptdfbprjustquhlazkjfluxrzopqdstulybnqvyknrchbphcarknnhhovweaqawdyxsqsqahkepluypwrzjegqtdoxfgzdkydeoxvrfhxusrujnmjzqrrlxglcmkiykldbiasnhrjbjekystzilrwkzhontwmehrfsrzfaqrbbxncphbzuuxeteshyrveamjsfiaharkcqxefghgceeixkdgkuboupxnwhnfigpkwnqdvzlydpidcljmflbccarbiegsmweklwngvygbqpescpeichmfidgsjmkvkofvkuehsmkkbocgejoiqcnafvuokelwuqsgkyoekaroptuvekfvmtxtqshcwsztkrzwrpabqrrhnlerxjojemcxel", { "dhvf", "sind", "ffsl", "yekr", "zwzq", "kpeo", "cila", "tfty", "modg", "ztjg", "ybty", "heqg", "cpwo", "gdcj", "lnle", "sefg", "vimw", "bxcb" }  }, OutputDataType{ 935 } }
          // TODO: create additional tests...
  ));
  // clang-format on
```