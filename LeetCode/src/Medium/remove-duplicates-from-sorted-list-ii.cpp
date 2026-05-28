// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

#include "../support.h"
#include <cassert>
#include <cstddef>
#include <gtest/gtest.h>
#include <vector>

namespace {
struct ListNode
{
    int val;
    ListNode* next;

    ~ListNode() noexcept {
        if (next) {
            delete next;
        }
    }

    static std::unique_ptr<ListNode> from(const std::vector<int>& array) {
        std::unique_ptr<ListNode> begin{};
        if (!array.empty()) {
            begin.reset(new ListNode{array[0], nullptr});
            ListNode* last_node = begin.get();
            for (size_t i = 1; i < array.size(); ++i) {
                last_node->next = new ListNode{array[i], nullptr};
                last_node = last_node->next;
            }
        }
        return begin;
    }

    std::vector<int> to() const {
        std::vector<int> result{};
        const ListNode* current = this;
        while (current) {
            result.push_back(current->val);
            current = current->next;
        }
        return result;
    }
};

using InputDataType = std::vector<int>;
using OutputDataType = std::vector<int>;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *begin_node{}, *last_node{};
        if (!head) {
            return begin_node;
        }

        std::map<int, int> encounter{};
        for (ListNode* active = head; active != nullptr; active = active->next) {
            ++encounter[active->val];
        }

        for (const auto& [value, quantity] : encounter) {
            if (quantity == 1) {
                if (!begin_node) {
                    begin_node = new ListNode{value, nullptr};
                    last_node = begin_node;
                } else {
                    last_node->next = new ListNode{value, nullptr};
                    last_node = last_node->next;
                }
            }
        }
        return begin_node;
    }
};

struct TestSolution : Solution, testing::TestWithParam<TestDataType>
{
};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
    GeneralTestData,
    TestSolution,
    ::testing::Values(
      // from example
      TestDataType{ InputDataType{}, OutputDataType{} },
      TestDataType{ InputDataType{1}, OutputDataType{1}},
      TestDataType{ InputDataType{1,1}, OutputDataType{}},
      TestDataType{ InputDataType{1,1,1,2,2,3}, OutputDataType{ 3}},
      TestDataType{ InputDataType{1,1,1,2,3}, OutputDataType{ 2, 3}},
      TestDataType{ InputDataType{1,2,3,3,4,4,5}, OutputDataType{1,2,5}}
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_array, output_expected_array] = GetParam();
    auto input_list = ListNode::from(input_array);
    auto output_list = deleteDuplicates(input_list.get());
    auto output_array = output_list ? output_list->to() : std::vector<int>{};
    Support::compareTwoArray(output_expected_array, output_array);
    delete output_list;
}
} // namespace