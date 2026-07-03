#include <vector>
#include <queue>
#include <set>
#include <string>
#include <utility>

class EightPuzzle {
private:
    std::vector<std::vector<int>> initial_state;
    std::vector<std::vector<int>> goal_state;

    std::pair<int, int> find_blank(const std::vector<std::vector<int>>& state) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    return std::make_pair(i, j);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) {
        auto [i, j] = find_blank(state);
        std::vector<std::vector<int>> new_state = state;

        if (direction == "up") {
            if (i > 0) {
                std::swap(new_state[i][j], new_state[i-1][j]);
            }
        } else if (direction == "down") {
            if (i < 2) {
                std::swap(new_state[i][j], new_state[i+1][j]);
            }
        } else if (direction == "left") {
            if (j > 0) {
                std::swap(new_state[i][j], new_state[i][j-1]);
            }
        } else if (direction == "right") {
            if (j < 2) {
                std::swap(new_state[i][j], new_state[i][j+1]);
            }
        }

        return new_state;
    }

    std::vector<std::string> get_possible_moves(const std::vector<std::vector<int>>& state) {
        std::vector<std::string> moves;
        auto [i, j] = find_blank(state);

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

public:
    EightPuzzle(const std::vector<std::vector<int>>& initial_state) {
        this->initial_state = initial_state;
        goal_state = {{1,2,3}, {4,5,6}, {7,8,0}};
    }

    std::vector<std::string> solve() {
        std::queue<std::pair<std::vector<std::vector<int>>, std::vector<std::string>>> open_list;
        open_list.push({initial_state, {}});

        std::set<std::vector<std::vector<int>>> closed_list;

        while (!open_list.empty()) {
            auto current = open_list.front();
            open_list.pop();

            if (current.first == goal_state) {
                return current.second;
            }

            for (const auto& move_dir : get_possible_moves(current.first)) {
                std::vector<std::vector<int>> new_state = move(current.first, move_dir);
                if (closed_list.find(new_state) == closed_list.end()) {
                    std::vector<std::string> new_path = current.second;
                    new_path.push_back(move_dir);
                    open_list.push({new_state, new_path});
                }
            }

            closed_list.insert(current.first);
        }

        return {};
    }
};