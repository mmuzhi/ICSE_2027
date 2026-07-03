#include <vector>
#include <string>
#include <deque>
#include <algorithm>
#include <utility>

class EightPuzzle {
public:
    EightPuzzle(const std::vector<std::vector<int>>& initial_state)
        : initial_state(initial_state),
          goal_state{{1, 2, 3}, {4, 5, 6}, {7, 8, 0}} {}

    std::pair<int, int> find_blank(const std::vector<std::vector<int>>& state) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // should never happen
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) const {
        auto [i, j] = find_blank(state);
        std::vector<std::vector<int>> new_state = state; // deep copy

        if (direction == "up") {
            std::swap(new_state[i][j], new_state[i - 1][j]);
        } else if (direction == "down") {
            std::swap(new_state[i][j], new_state[i + 1][j]);
        } else if (direction == "left") {
            std::swap(new_state[i][j], new_state[i][j - 1]);
        } else if (direction == "right") {
            std::swap(new_state[i][j], new_state[i][j + 1]);
        }
        return new_state;
    }

    std::vector<std::string> get_possible_moves(const std::vector<std::vector<int>>& state) const {
        auto [i, j] = find_blank(state);
        std::vector<std::string> moves;
        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");
        return moves;
    }

    std::vector<std::string> solve() {
        std::deque<std::pair<std::vector<std::vector<int>>, std::vector<std::string>>> open_list;
        open_list.push_back({initial_state, {}});
        std::vector<std::vector<std::vector<int>>> closed_list;

        while (!open_list.empty()) {
            auto current = open_list.front();
            open_list.pop_front();
            auto& current_state = current.first;
            auto& path = current.second;
            closed_list.push_back(current_state);

            if (current_state == goal_state) {
                return path;
            }

            for (const auto& move_dir : get_possible_moves(current_state)) {
                auto new_state = move(current_state, move_dir);
                if (std::find(closed_list.begin(), closed_list.end(), new_state) == closed_list.end()) {
                    auto new_path = path;
                    new_path.push_back(move_dir);
                    open_list.push_back({new_state, new_path});
                }
            }
        }

        return {}; // no solution
    }

private:
    std::vector<std::vector<int>> initial_state;
    std::vector<std::vector<int>> goal_state;
};