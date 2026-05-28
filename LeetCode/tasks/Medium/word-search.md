# Solution-1 = Time Limit Exceeded
```cpp
class Solution {
    using Coordinate = std::pair<size_t, size_t>;
    using Coordinates = std::vector<Coordinate>;
    using LettersMap = std::map<char, Coordinates>;
    LettersMap lettersMap{};

    bool construct(Coordinates possible_result, const std::string& word) {
        if (possible_result.size() == word.size()) {
            return true;
        }

        const char& next_symbol = word[possible_result.size()];
        const auto& possible_coordinates = lettersMap[next_symbol];
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

            auto new_possible_result = possible_result;
            new_possible_result.push_back(possible_coordinate);
            if (construct(std::move(new_possible_result), word)) {
                return true;
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

        return construct(Coordinates{}, word);
    }
};
```