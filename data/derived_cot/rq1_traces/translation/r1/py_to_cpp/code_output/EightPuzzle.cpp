#include <vector>
#include <queue>
#include <set>
#include <array>
#include <utility>
#include <string>

class EightPuzzle {
private:
    using State2D = std::vector<std::vector<int>>;
    State2D initial_state;
    State2D goal_state;

    std::array<int, 9> flattenState(const State2D& state) const {
        std::array<int, 9> arr;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                arr[i*3 + j] = state[i][j];
            }
        }
        return arr;
    }

public:
    EightPuzzle(State2D initialState) : initial_state(initialState), goal_state({{1, 2, 3}, {4, 5, 6}, {7, 8, 0}}) {}

    std::pair<int, int> find_blank(const State2D& state) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    State2D move(const State2D& state, const std::string& direction) const {
        auto [i, j] = find_blank(state);
        State2D new_state = state;

        if (direction == "up") {
            new_state[i][j] = state[i-1][j];
            new_state[i-1][j] = 0;
        } else if (direction == "down") {
            new_state[i][j] = state[i+1][j];
            new_state[i+1][j] = 0;
        } else if (direction == "left") {
            new_state[i][j] = state[i][j-1];
            new_state[i][j-1] = 0;
        } else if (direction == "right") {
            new_state[i][j] = state[i][j+1];
            new_state[i][j+1] = 0;
        }

        return new_state;
    }

    std::vector<std::string> get_possible_moves(const State2D& state) const {
        auto [i, j] = find_blank(state);
        std::vector<std::string> moves;

        if (i > 0) {
            moves.push_back("up");
        }
        if (i < 2) {
            moves.push_back("down");
        }
        if (j > 0) {
            moves.push_back("left");
        }
        if (j < 2) {
            moves.push_back("right");
        }

        return moves;
    }

    std::vector<std::string> solve() {
        std::queue<std::pair<State2D, std::vector<std::string>>> open_list;
        std::set<std::array<int, 9>> closed_set;

        open_list.push({initial_state, {}});

        while (!open_list.empty()) {
            auto current = open_list.front();
            open_list.pop();
            State2D current_state = current.first;
            std::vector<std::string> current_path = current.second;

            if (current_state == goal_state) {
                return current_path;
            }

            std::array<int, 9> flat_current = flattenState(current_state);
            closed_set.insert(flat_current);

            std::vector<std::string> moves = get_possible_moves(current_state);
            for (const std::string& move_dir : moves) {
                State2D new_state = move(current_state, move_dir);
                std::array<int, 9> flat_new = flattenState(new_state);

                if (closed_set.find(flat_new) == closed_set.end()) {
                    std::vector<std::string> new_path = current_path;
                    new_path.push_back(move_dir);
                    open_list.push({new_state, new_path});
                }
            }
        }

        return {};
    }
};