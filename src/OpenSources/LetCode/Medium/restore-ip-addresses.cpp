// https://leetcode.com/problems/restore-ip-addresses

#include "../support.h"
#include <algorithm>
#include <vector>

namespace {
using InputDataType = std::string;
using OutputDataType = std::vector<std::string>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    void determineIP(size_t i, const std::string& s, std::string address, std::vector<std::string>& determined_addresses) {
        const auto dots = std::count(address.begin(), address.end(), '.');
        if (dots == 4) {
            if (i == s.size()) {
                address.pop_back();
                determined_addresses.emplace_back(std::move(address));
            }
            return;
        }

        if (i + 2 < s.size()) {
            auto part = std::string{s[i], s[i + 1], s[i + 2]};
            if (auto digit = std::stoi(part); digit >= 100 && digit <= 255) {
                part.push_back('.');
                determineIP(i + 3, s, std::string(address).append(std::move(part)), determined_addresses);
            }
        }

        if (i + 1 < s.size()) {
            if (auto part = std::string{s[i], s[i + 1]}; std::stoi(part) >= 10) {
                part.push_back('.');
                determineIP(i + 2, s, std::string(address).append(std::move(part)), determined_addresses);
            }
        }

        if (i < s.size()) {
            auto part = std::string{s[i]};
            part.push_back('.');
            determineIP(i + 1, s, std::string(address).append(std::move(part)), determined_addresses);
        }
    }

public:
    std::vector<std::string> restoreIpAddresses(std::string s) {
        std::vector<std::string> determined_addresses{};
        determineIP(0, s, std::string{}, determined_addresses);
        return determined_addresses;
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
      TestDataType{ InputDataType{ "25525511135" }, OutputDataType{ "255.255.11.135", "255.255.111.35" } },
      TestDataType{ InputDataType{ "101023" }, OutputDataType{ "1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3" } }

  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [ip, expected_addresses] = GetParam();
    auto possible_addresses = restoreIpAddresses(ip);
    std::sort(possible_addresses.begin(), possible_addresses.end());
    std::sort(expected_addresses.begin(), expected_addresses.end());
    Support::compareTwoArray(expected_addresses, possible_addresses);
}
} // namespace
