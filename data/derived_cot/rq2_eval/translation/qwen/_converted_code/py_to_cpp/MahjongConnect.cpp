#include <vector>
#include <utility>
#include <set>
#include <random>
#include <chrono>

class MahjongConnect {
private:
    int rows, cols;
    std::vector<std::vector<char>> board;
    std::vector<char> icons;

    static std::mt19937 rng;

    char random_icon() {
        std::uniform_int_distribution<size_t> dist(0, icons.size() - 1);
        return icons[dist(rng)];
    }

public:
    MahjongConnect(const std::vector<int>& BOARD_SIZE, const std::vector<char>& ICONS) {
        rows = BOARD_SIZE[0];
        cols = BOARD_SIZE[1];
        icons = ICONS;
        create_board();
    }

    void create_board() {
        board.clear();
        for (int i = 0; i < rows; i++) {
            std::vector<char> row;
            for (int j = 0; j < cols; j++) {
                row.push_back(random_icon());
            }
            board.push_back(row);
        }
    }

    bool is_valid_move(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        int x1 = pos1.first, y1 = pos1.second;
        int x2 = pos2.first, y2 = pos2.second;

        // Check if positions are within bounds
        if (!(0 <= x1 && x1 < rows && 0 <= y1 && y1 < cols && 
              0 <= x2 && x2 < rows && 0 <= y2 && y2 < cols)) {
            return false;
        }

        // Check if positions are the same
        if (pos1 == pos2) {
            return false;
        }

        // Check if icons match
        if (board[x1][y1] != board[x2][y2]) {
            return false;
        }

        // Check for a valid path
        return has_path(pos1, pos2);
    }

    bool has_path(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        std::set<std::pair<int, int>> visited;
        std::vector<std::pair<int, int>> stack = { pos1 };

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
            int x = current.first, y = current.second;

            // Check adjacent positions (up, down, left, right)
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (0 <= nx && nx < rows && 0 <= ny && ny < cols) {
                    auto neighbor = std::make_pair(nx, ny);
                    if (visited.find(neighbor) == visited.end() && 
                        board[nx][ny] == board[x][y]) {
                        stack.push_back(neighbor);
                    }
                }
            }
        }

        return false;
    }

    void remove_icons(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        int x1 = pos1.first, y1 = pos1.second;
        int x2 = pos2.first, y2 = pos2.second;
        board[x1][y1] = ' ';
        board[x2][y2] = ' ';
    }

    bool is_game_over() {
        for (const auto& row : board) {
            for (char c : row) {
                if (c != ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

// Initialize static member
std::mt19937 MahjongConnect::rng(std::random_device{}());