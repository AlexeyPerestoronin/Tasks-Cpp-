# Answer
```cpp
TEST(Closure1, Test1) {
    int a1{ 1 };
    int a2{ 2 };

    EXPECT_EQ(a1, 1);
    EXPECT_EQ(a2, 2);

    [&]() {
        ++a1;
        ++a2;
    }();

    EXPECT_EQ(a1, 2);
    EXPECT_EQ(a2, 3);

    [=]() mutable {
        ++a1;
        ++a2;
    }();

    EXPECT_EQ(a1, 2);
    EXPECT_EQ(a2, 3);
}
```