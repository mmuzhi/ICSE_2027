#include <vector>
#include <string>
#include <set>
#include <utility>
#include <algorithm>

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
        return std::make_pair(0, 0);
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) {
        int i, j;
        std::tie(i, j) = find_blank(state);

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
        int i, j;
        std::tie(i, j) = find_blank(state);

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

public:
    EightPuzzle(const std::vector<std::vector<int>>& initial_state) : initial_state(initial_state) {
        goal_state = {{1,2,3},{4,5,6},{7,8,0}};
    }

    std::vector<std::string> solve() {
        std::vector<std::pair<std::vector<std::vector<int>>, std::vector<std::string>>> open_list;
        std::set<std::string> closed_set;

        std::string goal_str = "";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                goal_str += ('0' + goal_state[i][j]);
            }
        }

        open_list.push_back({initial_state, {}});
        closed_set.insert(goal_str);

        while (!open_list.empty()) {
            auto current = open_list[0];
            open_list.erase(open_list.begin());
            auto current_state = current.first;
            auto path = current.second;

            std::string current_str = "";
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    current_str += ('0' + current_state[i][j]);
                }
            }

            if (current_str == goal_str) {
                return path;
            }

            if (closed_set.find(current_str) != closed_set.end()) {
                continue;
            }

            closed_set.insert(current_str);

            for (const auto& move_str : get_possible_moves(current_state)) {
                auto new_state = move(current_state, move_str);
                std::string new_str = "";
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        new_str += ('0' + new_state[i][j]);
                    }
                }

                if (closed_set.find(new_str) == closed_set.end()) {
                    closed_set.insert(new_str);
                    open_list.push_back({new_state, path + {move_str}});
                }
            }
        }

        return std::vector<std::string>();
    }
};