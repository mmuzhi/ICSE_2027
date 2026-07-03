#include <vector>
#include <string>
#include <queue>
#include <set>
#include <utility>
#include <optional>
#include <algorithm>

class EightPuzzle {
public:
    using State = std::vector<std::vector<int>>;

    EightPuzzle(const State& initial_state)
        : initial_state(initial_state),
          goal_state({{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}) {}

    std::pair<int, int> find_blank(const State& state) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    State move(const State& state, const std::string& direction) const {
        auto [i, j] = find_blank(state);
        State new_state = state;

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

    std::vector<std::string> get_possible_moves(const State& state) const {
        std::vector<std::string> moves;
        auto [i, j] = find_blank(state);

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

    std::optional<std::vector<std::string>> solve() {
        std::queue<std::pair<State, std::vector<std::string>>> open_list;
        std::set<State> closed_list;

        open_list.push({initial_state, {}});

        while (!open_list.empty()) {
            auto [current_state, path] = open_list.front();
            open_list.pop();
            closed_list.insert(current_state);

            if (current_state == goal_state) {
                return path;
            }

            for (const auto& move_dir : get_possible_moves(current_state)) {
                State new_state = move(current_state, move_dir);
                if (closed_list.find(new_state) == closed_list.end()) {
                    std::vector<std::string> new_path = path;
                    new_path.push_back(move_dir);
                    open_list.push({new_state, new_path});
                }
            }
        }

        return std::nullopt;
    }

private:
    State initial_state;
    State goal_state;
};