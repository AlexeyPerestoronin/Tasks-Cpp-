#include <future>

#include <gtest/gtest.h>

TEST(Future, Test1) {
  auto f1 = std::async([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{3});
    std::cout << std::this_thread::get_id() << "\t: f1..." << std::endl;
    return 1;
  });

  auto f2 = std::async([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{2});
    std::cout << std::this_thread::get_id() << "\t: f2..." << std::endl;
    return 2;
  });

  auto f3 = std::async([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::cout << std::this_thread::get_id() << "\t: f3..." << std::endl;
    return 3;
  });

  ASSERT_EQ(1, f1.get());
  ASSERT_EQ(2, f2.get());
  ASSERT_EQ(3, f3.get());
}
