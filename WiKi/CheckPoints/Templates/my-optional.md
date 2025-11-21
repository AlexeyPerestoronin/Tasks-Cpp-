# Answer
```cpp
template<class DataType>
struct my_optional : std::optional<DataType> {
  using base_type = std::optional<DataType>;

  using base_type::base_type;
};

template<class DataType>
struct my_optional<DataType&> : std::optional<std::reference_wrapper<DataType>> {
  using DataTypeRW = std::reference_wrapper<DataType>;
  using base_type = std::optional<DataTypeRW>;

  my_optional(DataType& i_data)
      : base_type{ DataTypeRW{ i_data } } {}

  DataType& value() {
    return base_type::value().get();
  }
};
```