// https://leetcode.com/problems/decode-ways

#include "../support.h"
#include <algorithm>
#include <vector>

namespace {
using InputDataType = std::string;
using OutputDataType = int;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

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

        if (size_t j = i + 1; j < s.size()) {
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

struct TestSolution : Solution, testing::TestWithParam<TestDataType>
{
};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
      // from example
      TestDataType{ InputDataType{ "2101" }, OutputDataType{ 1 } },
      TestDataType{ InputDataType{ "10" }, OutputDataType{ 1 } },
      TestDataType{ InputDataType{ "12" }, OutputDataType{ 2 } },
      TestDataType{ InputDataType{ "226" }, OutputDataType{ 3 } },
      TestDataType{ InputDataType{ "06" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "2611017" }, OutputDataType{ 4 } },
      TestDataType{ InputDataType{ "2611055971756562" }, OutputDataType{ 4 } },
      TestDataType{ InputDataType{ "111111111111111111111111111111111111111111111" }, OutputDataType{ 4 } },
      // my tests
      TestDataType{ InputDataType{ "30" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "27" }, OutputDataType{ 1 } },
      TestDataType{ InputDataType{ "310402" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "30" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "0" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "00000" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "10000" }, OutputDataType{ 0 } },
      TestDataType{ InputDataType{ "10001" }, OutputDataType{ 0 } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [encoded_string, expected_decoded_variants] = GetParam();
    ASSERT_EQ(numDecodings(encoded_string), expected_decoded_variants);
}
} // namespace
