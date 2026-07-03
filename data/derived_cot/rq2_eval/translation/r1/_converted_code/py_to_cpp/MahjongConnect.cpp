#include <vector>
#include <set>
#include <random>
#include <stdexcept>
#include <utility>

class MahjongConnect {
private:
    std::vector<int> board_size;
    std::vector<std::string> icons;
    std::vector<std::vector<std::string>> board;

public:
    MahjongConnect(std::vector<int> board_size, std::vector<std::string> icons)
        : board_size(board_size), icons(icons) {
        board = create_board();
    }

    std::vector<std::vector<std::string>> create_board() {
        int rows = board_size[0];
        int cols = board_size[1];
        std::vector<std::vector<std::string>> new_board(rows, std::vector<std::string>(cols));

        if (icons.empty()) {
            throw std::invalid_argument("ICONS list must not be empty");
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, icons.size() - 1);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int index = dist(gen);
                new_board[i][j] = icons[index];
            }
        }

        return new_board;
    }

    bool is_valid_move(std::pair<int, int> pos1, std::pair<int, int> pos2) {
        int x1 = pos1.first;
        int y1 = pos1.second;
        int x2 = pos2.first;
        int y2 = pos2.second;

        if (x1 < 0 || x1 >= board_size[0] || y1 < 0 || y1 >= board_size[1] ||
            x2 < 0 || x2 >= board_size[0] || y2 < 0 || y2 >= board_size[1]) {
            return false;
        }

        if (pos1 == pos2) {
            return false;
        }

        if (board[x1][y1] != board[x2][y2]) {
            return false;
        }

        if (!has_path(pos1, pos2)) {
            return false;
        }

        return true;
    }

    bool has_path(std::pair<int, int> pos1, std::pair<int, int> pos2) {
        std::set<std::pair<int, int>> visited;
        std::vector<std::pair<int, int>> stack;
        stack.push_back(pos1);

        while (!stack.empty()) {
            auto current = stack.back();
            stack.pop_back();

            if (current == pos2) {
                return true;
            }

            if (visited.find(current) != visited.end()) {
                continue;
            }

            visited.insert(current);

            int x = current.first;
            int y = current.second;
            std::vector<std::pair<int, int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};

            for (const auto& dir : directions) {
                int new_x = x + dir.first;
                int new_y = y + dir.second;

                if (new_x >= 0 && new_x < board_size[0] && new_y >= 0 && new_y < board_size[1]) {
                    std::pair<int, int> neighbor = {new_x, new_y};
                    if (visited.find(neighbor) == visited.end() && board[new_x][new_y] == board[x][y]) {
                        stack.push_back(neighbor);
                    }
                }
            }
        }

        return false;
    }

    void remove_icons(std::pair<int, int> pos1, std::pair<int, int> pos2) {
        board[pos1.first][pos1.second] = " ";
        board[pos2.first][pos2.second] = " ";
    }

    bool is_game_over() {
        for (int i = 0; i < board_size[0]; i++) {
            for (int j = 0; j < board_size[1]; j++) {
                if (board[i][j] != " ") {
                    return false;
                }
            }
        }
        return true;
    }
};