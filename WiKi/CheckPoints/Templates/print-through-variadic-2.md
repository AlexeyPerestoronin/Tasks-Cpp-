# Answer
```cpp
template<class Arg>
void print(const Arg& i_arg) {
    if constexpr (std::is_trivial_v<std::decay_t<Arg>>)
        std::cout << i_arg << ' ';
    else
        for (const auto& value : i_arg)
            std::cout << value << ' ';
}
```

```cpp
template <typename C> struct is_vector : std::false_type {};
template <typename T, typename A> struct is_vector< std::vector<T, A> > : std::true_type {};
template <typename C> inline constexpr bool is_vector_v = is_vector<C>::value;

template <typename C> struct is_set : std::false_type {};
template <typename T, typename A> struct is_set< std::set<T, A> > : std::true_type {};
template <typename C> inline constexpr bool is_set_v = is_set<C>::value;

template<class Arg>
void print(const Arg& i_arg) {
  if constexpr (is_vector_v<Arg> || is_set_v<Arg>)
  {
    for (const auto& value : i_arg)
      std::cout << value << ' ';
  }
  else
    std::cout << i_arg << ' ';
}
```