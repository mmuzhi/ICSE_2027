#include <vector>
#include <string>
#include <random>
#include <utility>
#include <set>
#include <stack>

class MahjongConnect {
private:
    int board_size[2];
    std::vector<std::string> icons;
    std::vector<std::vector<char>> board;

    // Helper function to convert first character of each icon string
    std::vector<char> get_icon_chars() const {
        std::vector<char> chars;
        for (const auto& icon : icons) {
            if (!icon.empty()) {
                chars.push_back(icon[0]);
            } else {
                // Handle empty strings by skipping
                continue;
            }
        }
        return chars;
    }

public:
    MahjongConnect(int BOARD_SIZE[2], const std::vector<std::string>& ICONS) {
        board_size[0] = BOARD_SIZE[0];
        board_size[1] = BOARD_SIZE[1];
        icons = ICONS;
        board = std::vector<std::vector<char>>(board_size[0], std::vector<char>(board_size[1], ' '));
        create_board();
    }

    void create_board() {
        if (icons.empty()) return;
        std::vector<char> icon_chars = get_icon_chars();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, icon_chars.size() - 1);

        for (int i = 0; i < board_size[0]; ++i) {
            for (int j = 0; j < board_size[1]; ++j) {
                board[i][j] = icon_chars[distrib(gen)];
            }
        }
    }

    bool is_valid_move(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) const {
        int x1 = pos1.first, y1 = pos1.second;
        int x2 = pos2.first, y2 = pos2.second;

        // Check if positions are within bounds
        if (x1 < 0 || x1 >= board_size[0] || y1 < 0 || y1 >= board_size[1] ||
            x2 < 0 || x2 >= board_size[0] || y2 < 0 || y2 >= board_size[1]) {
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

        // Check if there's a valid path
        return has_path(pos1, pos2);
    }

    bool has_path(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) const {
        std::set<std::pair<int, int>> visited;
        std::stack<std::pair<int, int>> stack;
        stack.push(pos1);
        visited.insert(pos1);

        while (!stack.empty()) {
            auto current = stack.top();
            stack.pop();
            int x = current.first, y = current.second;

            if (current == pos2) {
                return true;
            }

            // Check adjacent positions
            int dx[4] = {0, 0, 1, -1};
            int dy[4] = {1, -1, 0, 0};
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < board_size[0] && ny >= 0 && ny < board_size[1]) {
                    auto neighbor = std::make_pair(nx, ny);
                    if (visited.find(neighbor) == visited.end() && board[nx][ny] == board[x][y]) {
                        visited.insert(neighbor);
                        stack.push(neighbor);
                    }
                }
            }
        }

        return false;
    }

    void remove_icons(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
        int x1 = pos1.first, y1 = pos1.second;
        int x2 = pos2.first, y2 = pos2.second;

        // Validate positions and icons before removal
        if (x1 < 0 || x1 >= board_size[0] || y1 < 0 || y1 >= board_size[1] ||
            x2 < 0 || x2 >= board_size[0] || y2 < 0 || y2 >= board_size[1]) {
            return;
        }

        if (board[x1][y1] != board[x2][y2]) {
            return;
        }

        board[x1][y1] = ' ';
        board[x2][y2] = ' ';
    }

    bool is_game_over() const {
        for (int i = 0; i < board_size[0]; ++i) {
            for (int j = 0; j < board_size[1]; ++j) {
                if (board[i][j] != ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};