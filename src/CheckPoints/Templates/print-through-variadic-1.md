# Answer
```cpp
template<class... Args>
void print(const Args&... i_args) {
    ((std::cout << i_args), ...);
}
```
