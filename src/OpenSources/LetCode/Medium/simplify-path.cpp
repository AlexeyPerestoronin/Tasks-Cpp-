// https://leetcode.com/problems/simplify-path

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>
#include <list>

namespace {
using InputDataType = std::string;
using OutputDataType = std::string;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
public:
    std::string simplifyPath(std::string path) {
        path.push_back('/');
        std::vector<std::string> segments{};

        std::string segment{};
        for (auto ch : path) {
            if (ch != '/') {
                segment.push_back(ch);
            } else {
                if (!segment.empty()) {
                    if (segment != "..") {
                        if (segment != ".") {
                            segments.push_back(std::move(segment));
                        }
                    } else {
                        if (!segments.empty()) {
                            segments.pop_back();
                        }
                    }
                }
                segment.clear();
            }
        }

        path.clear();
        for (auto& segment : segments) {
            path.push_back('/');
            path.append(std::move(segment));
        }
        if (path.empty()) {
            path.push_back('/');
        }
        return path;
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
      TestDataType{ InputDataType{ "/home/" }, OutputDataType{ "/home" } },
      TestDataType{ InputDataType{ "/home//foo/" }, OutputDataType{ "/home/foo" } },
      TestDataType{ InputDataType{ "/home/user/Documents/../Pictures" }, OutputDataType{ "/home/user/Pictures" } },
      TestDataType{ InputDataType{ "/../" }, OutputDataType{ "/" } },
      TestDataType{ InputDataType{ "/.../a/../b/c/../d/./" }, OutputDataType{ "/.../b/d" } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [path, simplified_path] = GetParam();
    ASSERT_EQ(simplified_path, simplifyPath(path));
}
} // namespace
