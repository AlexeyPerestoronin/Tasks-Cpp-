// https://leetcode.com/problems/word-search

#include "../support.h"
#include <algorithm>
#include <map>
#include <vector>

namespace {
using InputDataType = std::pair<std::vector<std::vector<char>>, std::string>;
using OutputDataType = bool;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    using Coordinate = std::pair<size_t, size_t>;
    using Coordinates = std::vector<Coordinate>;
    using LettersMap = std::map<char, Coordinates>;
    using ShortWord = std::vector<std::pair<char, size_t>>;

    LettersMap lettersMap{};

    bool construct(Coordinates possible_result, const ShortWord& short_word) {
        if (possible_result.size() == short_word.size()) {
            return true;
        }

        const auto [next_symbol, quantity] = short_word[possible_result.size()];
        const auto& possible_coordinates = lettersMap[next_symbol];
        auto new_possible_result = possible_result;
        for (const auto& possible_coordinate : possible_coordinates) {
            if (!possible_result.empty()) {
                bool was_used = false;
                for (const auto& existence_coordinate : possible_result) {
                    if (possible_coordinate == existence_coordinate) {
                        was_used = true;
                        break;
                    }
                }

                if (was_used) {
                    continue;
                }

                const auto& [last_i, last_j] = possible_result.back();
                const auto& [possible_i, possible_j] = possible_coordinate;
                if (auto diff_i = std::max(last_i, possible_i) - std::min(last_i, possible_i); diff_i > 1) {
                    continue;
                } else if (auto diff_j = std::max(last_j, possible_j) - std::min(last_j, possible_j); diff_j > 1) {
                    continue;
                } else if (diff_i == 1 && diff_j == 1) {
                    continue;
                }
            }

            new_possible_result.push_back(possible_coordinate);
            if (possible_result.size() + quantity == new_possible_result.size()) {
                if (construct(std::move(new_possible_result), short_word)) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        for (size_t i = 0; i < board.size(); ++i) {
            for (size_t j = 0; j < board[i].size(); ++j) {
                lettersMap[board[i][j]].emplace_back(std::make_pair(i, j));
            }
        }

        ShortWord short_word{};
        for (auto ch : word) {
            if (!short_word.empty()) {
                if (auto& [last_ch, quantity] = short_word.back(); last_ch == ch) {
                    ++quantity;
                    continue;
                }
            }
            short_word.emplace_back(ch, 1);
        }

        return construct(Coordinates{}, short_word);
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
      TestDataType{ InputDataType{ {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "ABCCED" }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "SEE" }, OutputDataType{ true } },
      TestDataType{ InputDataType{ {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}}, "ABCB" }, OutputDataType{ false } },
      TestDataType{ InputDataType{ {{'a','b'},{'c','d'}}, "abcd" }, OutputDataType{ false } },
      TestDataType{ InputDataType{ {{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','A'},{'A','A','A','A','A','B'},{'A','A','A','A','B','A'}}, "AAAAAAAAAAAAABB" }, OutputDataType{ false } }
  ));
// clang-format on

TEST_P(TestSolution, Test1) {
    auto [input_data, result] = GetParam();
    auto& [board, word] = input_data;
    ASSERT_EQ(exist(board, word), result);
}
} // namespace
