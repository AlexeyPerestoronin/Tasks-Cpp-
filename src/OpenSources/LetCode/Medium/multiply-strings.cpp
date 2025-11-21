/// https://leetcode.com/problems/multiply-strings/

#include <list>
#include <string>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
struct InputDataType {
  std::string left;
  std::string right;
};

using OutputDataType = std::string;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
  using Uint = uint32_t;
  struct LongDigit : std::list<Uint> {
    LongDigit() = default;

    LongDigit(const std::string &source) {
      for (const auto &ch : source) {
        this->push_back(static_cast<Uint>(ch - '0'));
      }
    }

    LongDigit operator+(const LongDigit &other) const {
      if (this->size() < other.size()) {
        return other + *this;
      }

      LongDigit res{};
      auto cache = Uint{0};
      auto it2 = other.rbegin();
      auto it1 = this->rbegin();

      while (it2 != other.rend()) {
        Uint sum = (*it1) + (*it2) + cache;
        cache = sum / 10;
        res.push_front(sum % 10);
        ++it2;
        ++it1;
      }

      while (it1 != this->rend()) {
        Uint sum = (*it1) + cache;
        cache = sum / 10;
        res.push_front(sum % 10);
        ++it1;
      }

      if (cache != 0) {
        res.push_front(cache);
      }

      return res;
    }

    LongDigit operator*(Uint digit) const {
      LongDigit res{};
      auto cache = Uint{0};
      auto it1 = this->rbegin();

      while (it1 != this->rend()) {
        Uint mul = (*it1) * digit + cache;
        cache = mul / 10;
        res.push_front(mul % 10);
        ++it1;
      }

      if (cache != 0) {
        res.push_front(cache);
      }

      return res;
    }

    LongDigit operator*(const LongDigit &other) const {
      if (this->size() < other.size()) {
        return other * *this;
      }

      LongDigit res{};
      for (auto [index, it2] = std::make_pair(size_t{0}, other.rbegin());
           it2 != other.rend(); ++index, ++it2) {
        auto part = *this * (*it2);
        for (int i = 0; i < index; ++i) {
          part.push_back(0);
        }
        res = res + part;
      }

      return res;
    }

    operator std::string() const {
      std::string res{};
      res.reserve(this->size());
      for (const auto &digit : *this) {
        res.push_back(static_cast<char>(digit) + '0');
      }

      return res;
    }
  };

  std::string multiply(std::string num1, std::string num2) {
    if (num1 == "0" || num2 == "0") {
      return "0";
    }
    return LongDigit(num1) * LongDigit(num2);
  }
};

struct TestSolution : Solution, testing::TestWithParam<TestDataType> {};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      TestSolution,
      ::testing::Values(
          TestDataType{ InputDataType{ "1", "2" }, OutputDataType{ "2" } },
          TestDataType{ InputDataType{ "0", "52" }, OutputDataType{ "0" } },
          TestDataType{ InputDataType{ "9999", "0" }, OutputDataType{ "0" } },
          TestDataType{ InputDataType{ "9", "99" }, OutputDataType{ "891" } },
          TestDataType{ InputDataType{ "123", "456" }, OutputDataType{ "56088" } },
          TestDataType{ InputDataType{ "123456789", "987654321" }, OutputDataType{ "121932631112635269" } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
  const auto &[input, expected_output] = GetParam();
  const auto &[left, right] = input;
  ASSERT_EQ(multiply(left, right), expected_output);
}
} // namespace
