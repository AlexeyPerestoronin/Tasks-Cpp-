////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing of understanding a C++ inheritance mechanism for template-classes
/// @details Look into unit-tests, fix `ASSERT_EQ`-statements in all unit-tests and achieve the green-output
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    05.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>

using namespace std::string_literals;

template<class ElementType>
struct Class1 {
  virtual ~Class1() = default;

  [[maybe_unused]] virtual std::string getMessage() const {
    return "Class1::getMessage"s;
  }
};

template<class ElementType>
struct Class2 : Class1<ElementType> {
  [[maybe_unused]] std::string getMessage() const override {
    return "Class2::getMessage"s;
  }
};

TEST(Inheritance2, Test1) {
  std::shared_ptr<Class1<int>> ptr = std::make_shared<Class2<int>>();
  ASSERT_EQ(ptr->getMessage(), "TODO: write right answer..."s);
}

TEST(Inheritance2, Test2) {
  std::shared_ptr<Class2<int>> ptr = std::make_shared<Class2<int>>();
  ASSERT_EQ(ptr->getMessage(), "TODO: write right answer..."s);
}
