#include <vector>
#include <string>
#include <random>
#include <stack>
#include <set>
#include <utility>

class MahjongConnect {
private:
    std::mt19937 rng;

public:
    std::vector<int> BOARD_SIZE;
    std::vector<std::string> ICONS;
    std::vector<std::vector<std::string>> board;

    MahjongConnect(const std::vector<int>& BOARD_SIZE, const std::vector<std::string>& ICONS)
        : BOARD_SIZE(BOARD_SIZE), ICONS(ICONS), rng(std::random_device{}())
    {
        board = create_board();
    }

    std::vector<std::vector<std::string>> create_board() {
        std::vector<std::vector<std::string>> newBoard(BOARD_SIZE[0],
            std::vector<std::string>(BOARD_SIZE[1]));
        std::uniform_int_distribution<size_t> dist(0, ICONS.size() - 1);
        for (int i = 0; i < BOARD_SIZE[0]; ++i) {
            for (int j = 0; j < BOARD_SIZE[1]; ++j) {
                newBoard[i][j] = ICONS[dist(rng)];
            }
        }
        return newBoard;
    }

    bool is_valid_move(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        int x1 = pos1.first, y1 = pos1.second;
        int x2 = pos2.first, y2 = pos2.second;

        // Check if positions are within the game board range
        if (x1 < 0 || x1 >= BOARD_SIZE[0] || y1 < 0 || y1 >= BOARD_SIZE[1] ||
            x2 < 0 || x2 >= BOARD_SIZE[0] || y2 < 0 || y2 >= BOARD_SIZE[1]) {
            return false;
        }

        // Check if the two positions are the same
        if (pos1 == pos2) {
            return false;
        }

        // Check if the two positions have the same icon
        if (board[x1][y1] != board[x2][y2]) {
            return false;
        }

        // Check if there is a valid path between the two positions
        if (!has_path(pos1, pos2)) {
            return false;
        }

        return true;
    }

    bool has_path(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        std::set<std::pair<int, int>> visited;
        std::stack<std::pair<int, int>> stack;
        stack.push(pos1);

        while (!stack.empty()) {
            std::pair<int, int> current = stack.top();
            stack.pop();

            if (current == pos2) {
                return true;
            }

            if (visited.count(current)) {
                continue;
            }
            visited.insert(current);

            int x = current.first, y = current.second;
            // Check adjacent positions (up, down, left, right)
            std::vector<std::pair<int, int>> neighbors = {
                {0, 1}, {0, -1}, {1, 0}, {-1, 0}
            };
            for (const auto& dir : neighbors) {
                int new_x = x + dir.first;
                int new_y = y + dir.second;
                if (new_x >= 0 && new_x < BOARD_SIZE[0] && new_y >= 0 && new_y < BOARD_SIZE[1]) {
                    if (visited.count({new_x, new_y}) == 0 &&
                        board[new_x][new_y] == board[x][y]) {
                        stack.push({new_x, new_y});
                    }
                }
            }
        }

        return false;
    }

    void remove_icons(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        board[pos1.first][pos1.second] = " ";
        board[pos2.first][pos2.second] = " ";
    }

    bool is_game_over() {
        for (const auto& row : board) {
            for (const auto& cell : row) {
                if (cell != " ") {
                    return false;
                }
            }
        }
        return true;
    }
};