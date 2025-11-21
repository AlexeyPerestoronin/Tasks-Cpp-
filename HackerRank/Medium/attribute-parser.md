# Answer
## MAIN
```cpp
  std::string getNextLine() {
    static std::string nextLine{};
    std::getline(std::cin, nextLine, '\n');
    return std::move(nextLine);
  }

  std::pair<int, int> getNAndQLines() {
    std::smatch sm;
    const std::string nextLine = getNextLine();
    std::regex_match(nextLine, sm, std::regex{ "(\\d+)\\s(\\d+)" });
    return { std::stoi(sm.str(1)), std::stoi(sm.str(2)) };
  }

  struct InputParameter {
    std::unordered_map<std::string, std::string> parameters{};

    void fill(const std::string& message) {
      std::smatch sm{};
      const std::regex reg{ "([\\w\\d]+)\\s?=\\s?\"(.+?)\"" };
      for (std::string mes = message; std::regex_search(mes, sm, reg);
           mes = sm.suffix().str(), std::regex_search(mes, sm, reg)) {
        parameters[sm.str(1)] = sm.str(2);
      }
    }

    std::optional<std::string> find(const std::string& paramKeyValue) {
      if (auto itParam = parameters.find(paramKeyValue); itParam != parameters.end()) {
        return itParam->second;
      }
      return std::nullopt;
    }
  };

#ifndef IN_SITE
  int main()
#else
  TEST_P(ParametrizedTest, Test1)
#endif
  {
    auto [nLines, qLines] = getNAndQLines();

    std::unordered_map<std::string, InputParameter> parameters{};

    std::list<std::string> tags{};
    while (nLines-- > 0) {
      std::string nextLine = getNextLine();

      auto getTag = [&nextLine]() -> std::optional<std::string> {
        std::smatch sm;
        static const std::regex hrml{ "<([\\w\\d]+).*?>" };
        if (std::regex_match(nextLine, sm, hrml)) {
          return sm.str(1);
        }
        return std::nullopt;
      };

      if (auto tagOpt = getTag(); tagOpt) {
        tags.push_back(std::move(tagOpt.value()));
        std::string tag{ tags.front() };
        for (auto itTag = std::next(tags.begin()); itTag != tags.end(); ++itTag) {
          tag.push_back('.');
          tag.append(*itTag);
        }
        parameters[tag].fill(nextLine);
      } else {
        tags.pop_back();
      }
    }

    while (qLines-- > 0) {
      std::string nextLine = getNextLine();

      auto getTagAndParameter = [&nextLine]() -> std::pair<std::string, std::string> {
        std::smatch sm;
        static const std::regex query{ "([\\w\\d\\.]+)~([\\w\\d]+)" };
        std::regex_match(nextLine, sm, query);
        return { sm.str(1), sm.str(2) };
      };

      static const std::string notFound{ "Not Found!" };
      auto [qTag, qParamKey] = getTagAndParameter();
      if (auto itParameter = parameters.find(qTag); itParameter != parameters.end()) {
        std::cout << itParameter->second.find(qParamKey).value_or(notFound) << '\n';
      } else {
        std::cout << notFound << '\n';
      }
    }
  }
```

## Tests
```cpp
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
                        } },
          
          // additional
          // example-3
          TestDataType{ InputDataType{
                            { "10 10" },
                            { "<a value = \"GoodVal\">" },
                            { "<b value = \"BadVal\" size = \"10\">" },
                            { "</b>" },
                            { "<c height = \"auto\">" },
                            { "<d size = \"3\">" },
                            { "<e strength = \"2\">" },
                            { "</e>" },
                            { "</d>" },
                            { "</c>" },
                            { "</a>" },
                            { "a~value" },
                            { "b~value" },
                            { "a.b~size" },
                            { "a.b~value" },
                            { "a.b.c~height" },
                            { "a.c~height" },
                            { "a.d.e~strength" },
                            { "a.c.d.e~strength" },
                            { "d~sze" },
                            { "a.c.d~size" },
                        },
                        OutputDataType{
                            { "GoodVal" },
                            { "Not Found!" },
                            { "10" },
                            { "BadVal" },
                            { "Not Found!" },
                            { "auto" },
                            { "Not Found!" },
                            { "2" },
                            { "Not Found!" },
                            { "3" },
                        } },
          // example-4
          TestDataType{ InputDataType{
                            { "20 19" },
                            { "<tag1 v1 = \"123\" v2 = \"43.4\" v3 = \"hello\">" },
                            { "</tag1>" },
                            { "<tag2 v4 = \"v2\" name = \"Tag2\">" },
                            { "<tag3 v1 = \"Hello\" v2 = \"World!\">" },
                            { "</tag3>" },
                            { "<tag4 v1 = \"Hello\" v2 = \"Universe!\">" },
                            { "</tag4>" },
                            { "</tag2>" },
                            { "<tag5>" },
                            { "<tag7 new_val = \"New\">" },
                            { "</tag7>" },
                            { "</tag5>" },
                            { "<tag6>" },
                            { "<tag8 intval = \"34\" floatval = \"9.845\">" },
                            { "<ntag nv = \"4$\">" },
                            { "<nvtag nv = \"6$\">" },
                            { "</nvtag>" },
                            { "</ntag>" },
                            { "</tag8>" },
                            { "</tag6>" },
                            { "tag1~v1" },
                            { "tag1~v2" },
                            { "tag1~v3" },
                            { "tag4~v2" },
                            { "tag2.tag4~v1" },
                            { "tag2.tag4~v2" },
                            { "tag2.tag3~v2" },
                            { "tag5.tag7~new_val" },
                            { "tag5~new_val" },
                            { "tag7~new_val" },
                            { "tag6.tag8~intval" },
                            { "tag6.tag8~floatval" },
                            { "tag6.tag8~val" },
                            { "tag8~intval" },
                            { "tag6.tag8.ntag~nv" },
                            { "tag6.tag8.ntag.nvtag~nv" },
                            { "tag6.tag8.nvtag~nv" },
                            { "randomtag~nv" },
                            { "tag283.tag21.den~jef" },
                        },
                        OutputDataType{
                            { "123" },
                            { "43.4" },
                            { "hello" },
                            { "Not Found!" },
                            { "Hello" },
                            { "Universe!" },
                            { "World!" },
                            { "New" },
                            { "Not Found!" },
                            { "Not Found!" },
                            { "34" },
                            { "9.845" },
                            { "Not Found!" },
                            { "Not Found!" },
                            { "4$" },
                            { "6$" },
                            { "Not Found!" },
                            { "Not Found!" },
                            { "Not Found!" },
                        } }

          // TODO: create additional tests...
          ));
  // clang-format on
```
