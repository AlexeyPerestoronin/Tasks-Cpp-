/// https://leetcode.com/problems/count-and-say/

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <string>
#include <utility>

namespace {
using InputDataType = int;
using OutputDataType = std::string;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    std::string RLE(std::string str) {
        std::string result{};

        auto symbol = char{str[0]};
        auto quantity = unsigned{1};

        for (size_t i{1}; i < str.size(); ++i) {
            if (str[i] == symbol) {
                ++quantity;
            } else {
                result.append(std::to_string(quantity));
                result.push_back(symbol);
                symbol = str[i];
                quantity = 1;
            }
        }

        result.append(std::to_string(quantity));
        result.push_back(symbol);

        return result;
    }

    public:
    std::string countAndSay(int n) {
        std::string result{"1"};
        while (--n != 0) {
            result = RLE(std::move(result));
        }
        return result;
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
      TestDataType{ InputDataType{ 1 }, OutputDataType{ "1" } },
      TestDataType{ InputDataType{ 2 }, OutputDataType{ "11" } },
      TestDataType{ InputDataType{ 3 }, OutputDataType{ "21" } },
      TestDataType{ InputDataType{ 4 }, OutputDataType{ "1211" } },
      TestDataType{ InputDataType{ 5 }, OutputDataType{ "111221" } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [inputData, outputData] = GetParam();
    ASSERT_EQ(countAndSay(inputData), outputData);
}
} // namespace
