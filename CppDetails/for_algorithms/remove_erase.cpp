#include <algorithm>
#include <map>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
TEST(RemoveFromVector, Scenario1) {
    std::vector<int> collection{1, 4, 6, 3, 6, 9, 4, 3};
    ASSERT_EQ(collection.size(), 8);
    auto it = std::remove_if(collection.begin(), collection.end(), [](const auto& item) { return item != 3; });
    ASSERT_EQ(collection.size(), 8);
    collection.erase(it, collection.end());
    ASSERT_EQ(collection.size(), 2);
}

TEST(EraseFromVector, Scenario1) {
    std::vector<int> collection{1, 4, 6, 3, 6, 9, 4, 3};
    ASSERT_EQ(collection.size(), 8);
    std::erase(collection, 3);
    ASSERT_EQ(collection.size(), 6);
}

TEST(RemoveFromMap, Scenario1) {
    std::map<int, int> collection{{1, 2}, {3, 5}, {4, 1}, {6, 3}, {10, 1}};
    // it's impossible to use remove_if with map because map is tree-like structure
    // std::remove_if(collection, [](const auto& item) { return item.first != 1; });
    std::erase_if(collection, [](const auto& item) { return item.second != 1; });
    ASSERT_EQ(collection.size(), 2);
    ASSERT_TRUE(collection.contains(4));
    ASSERT_TRUE(collection.contains(10));
}
} // namespace
