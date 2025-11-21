#include <thread>

#include <gtest/gtest.h>

TEST(Thread, Test1) {
  auto t1 = std::thread([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{3});
    std::cout << std::this_thread::get_id() << "\t: t1..." << std::endl;
    return 1;
  });

  auto t2 = std::thread([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{2});
    std::cout << std::this_thread::get_id() << "\t: t2..." << std::endl;
    return 1;
  });

  auto t3 = std::thread([]() -> int {
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::cout << std::this_thread::get_id() << "\t: t3..." << std::endl;
    return 1;
  });

  t1.join();
  t2.join();
  t3.join();
}