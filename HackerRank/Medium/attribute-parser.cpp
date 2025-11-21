////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `main`-function
/// @details https://www.hackerrank.com/challenges/attribute-parser/problem
/// This challenge works with a custom-designed markup language HRML.
/// In HRML, each element consists of a starting and ending tag, and there are attributes associated with each tag.
/// Only starting tags can have attributes.
/// We can call an attribute by referencing the tag, followed by a tilde, '~' and the name of the attribute.
/// The tags may also be nested.
///
/// The opening tags follow the format:
///   <tag-name attribute1-name = "value1" attribute2-name = "value2" ...>
///
/// The closing tags follow the format:
///   </tag-name>
///
/// The attributes are referenced as:
///   tag1~value
///   tag1.tag2~name
///
/// Given the source code in HRML format consisting of:
///   lines,answer
///   queries
///     note: for each query, print the value of the attribute specified. Print "Not Found!" if the attribute does not exist.
///
/// Input Format:
///   The first line consists of two space separated integers, N and Q.
///   N - specifies the number of lines in the HRML source program.
///   Q - specifies the number of queries.
///
/// Example-1:
///   HRML listing:
///     <tag1 value = "value">
///     <tag2 name = "name">
///     <tag3 another="another" final="final">
///     </tag3>
///     </tag2>
///     </tag1>
///   Queries:
///     tag1~value
///     tag1.tag2.tag3~name
///     tag1.tag2~value
///
/// Explanation:
///   Here, tag2 is nested within tag1, so attributes of tag2 are accessed as tag1.tag2~<attribute>.
///   Results of the queries are:
///     Query                 Value
///     tag1~value            "value"
///     tag1.tag2.tag3~name   "Not Found!"
///     tag1.tag2.tag3~final  "final"

/// Example-2:
///   Input:
///     4 3
///     <tag1 value = "HelloWorld">
///     <tag2 name = "Name1">
///     </tag2>
///     </tag1>
///     tag1.tag2~name
///     tag1~name
///     tag1~value
///   Output:
///     Name1
///     Not Found!
///     HelloWorld
///
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    5.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include <gtest/gtest-param-test.h>

#define IN_SITE

#include <regex>
#include <ostream>
#include <sstream>
#include <optional>

namespace {
  using InputDataType = std::vector<std::string>;
  using OutputDataType = std::vector<std::string>;
  using TestDataType = std::pair<InputDataType, OutputDataType>;

  struct ParametrizedTest : testing::TestWithParam<TestDataType> {
    std::stringstream cinEmulator{};
    std::stringstream coutEmulator{};

    void SetUp() override {
      std::cin.rdbuf(cinEmulator.rdbuf());
      std::cout.rdbuf(coutEmulator.rdbuf());

      const auto& input = GetParam().first;
      for (const auto& string : input) {
        cinEmulator << string;
        cinEmulator << '\n';
      }
    }

    void TearDown() override {
      const auto& output = GetParam().second;
      std::string message{};
      for (const auto& string : output) {
        ASSERT_FALSE(coutEmulator.eof()) << "Unexpected behaviour: the message \"" << string << "\" is absent!";
        std::getline(coutEmulator, message, '\n');
        EXPECT_STREQ(string.c_str(), message.c_str());
      }

      while (!coutEmulator.eof()) {
        if (std::getline(coutEmulator, message, '\n'); message.empty()) {
          break;
        }
        EXPECT_TRUE(false) << "Unexpected behaviour: the message \"" << message << "\" was not processed!";
      }
    }
  };

  // clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      ParametrizedTest,
      ::testing::Values(
          // from example
          // example-1
          TestDataType{ InputDataType{
                            { "6 3" },
                            { "<tag1 value = \"value\">" },
                            { "<tag2 name = \"name\">" },
                            { "<tag3 another=\"another\" final=\"final\">" },
                            { "</tag3>" },
                            { "</tag2>" },
                            { "</tag1>" },
                            { "tag1~value" },
                            { "tag1.tag2.tag3~name" },
                            { "tag1.tag2.tag3~final" },
                        },
                        OutputDataType{
                            { "value" },
                            { "Not Found!" },
                            { "final" },
                        } },
          // example-2
          TestDataType{ InputDataType{
                            { "4 3" },
                            { "<tag1 value = \"HelloWorld\">" },
                            { "<tag2 name = \"Name1\">" },
                            { "</tag2>" },
                            { "</tag1>" },
                            { "tag1.tag2~name" },
                            { "tag1~name" },
                            { "tag1~value" },
                        },
                        OutputDataType{
                            { "Name1" },
                            { "Not Found!" },
                            { "HelloWorld" },
                        } }
          
          // additional

          // TODO: create additional tests...
          ));
  // clang-format on

#ifndef IN_SITE
  int main()
#else
  TEST_P(ParametrizedTest, Test1)
#endif
  {
    // TODO: implement this function...
  }
} // namespace
