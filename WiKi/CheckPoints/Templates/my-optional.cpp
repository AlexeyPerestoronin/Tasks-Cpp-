////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Testing of understanding a C++ template-classes' redefinition mechanism
/// @details Improve the `my_optional`-class and pass the tests
/// @author  Alexey Perestoronin: aperestoronin@aligntech.com
/// @date    05.11.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <optional>

#include <gtest/gtest.h>

template<class DataType>
struct my_optional : std::optional<DataType> {
  using base_type = std::optional<DataType>;

  using base_type::base_type;
};

// TODO: try to provide a possibility working with reference-types to `my_optional`-class

TEST(MyOptional, Test1) {
  int value{ 4 };

  // // TODO: need to un-commit and pass the tests
  // my_optional<int&> valueOptRef{ value };
  // ASSERT_EQ(++valueOptRef.value(), 5);
  // ASSERT_EQ(value, 5);
}
