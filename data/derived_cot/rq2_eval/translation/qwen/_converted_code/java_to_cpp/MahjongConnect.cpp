#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>

class MahjongConnect {
private:
    std::vector<int> boardSize;
    std::vector<std::string> icons;
    std::vector<std::vector<std::string>> board;

    bool isValidPosition(int x, int y) const {
        return x >= 0 && x < boardSize[0] && y >= 0 && y < boardSize[1];
    }

    bool dfs(int x, int y, const std::vector<int>& target, std::vector<std::vector<bool>>& visited) {
        if (x == target[0] && y == target[1]) {
            return true;
        }

        if (visited[x][y]) {
            return false;
        }

        visited[x][y] = true;

        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValidPosition(newX, newY) && !visited[newX][newY] && board[newX][newY] == board[x][y]) {
                if (dfs(newX, newY, target, visited)) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    MahjongConnect(const std::vector<int>& boardSize, const std::vector<std::string>& icons) : boardSize(boardSize), icons(icons) {
        this->board = createBoard();
    }

    std::vector<std::vector<std::string>> createBoard() {
        std::vector<std::vector<std::string>> board(boardSize[0], std::vector<std::string>(boardSize[1]));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, icons.size() - 1);

        for (int i = 0; i < boardSize[0]; ++i) {
            for (int j = 0; j < boardSize[1]; ++j) {
                board[i][j] = icons[distrib(gen)];
            }
        }
        return board;
    }

    bool is_valid_move(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        int x1 = pos1[0], y1 = pos1[1];
        int x2 = pos2[0], y2 = pos2[1];

        if (!isValidPosition(x1, y1) || !isValidPosition(x2, y2)) {
            return false;
        }

        if (x1 == x2 && y1 == y2) {
            return false;
        }

        if (board[x1][y1] != board[x2][y2]) {
            return false;
        }

        std::vector<std::vector<bool>> visited(boardSize[0], std::vector<bool>(boardSize[1], false));
        return dfs(x1, y1, {x2, y2}, visited);
    }

    void remove_icons(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        board[pos1[0]][pos1[1]] = " ";
        board[pos2[0]][pos2[1]] = " ";
    }

    bool is_game_over() const {
        for (int i = 0; i < boardSize[0]; ++i) {
            for (int j = 0; j < boardSize[1]; ++j) {
                if (board[i][j] != " ") {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    std::vector<int> boardSize = {4, 4};
    std::vector<std::string> icons = {"a", "b", "c"};

    MahjongConnect mc(boardSize, icons);

    std::vector<int> pos1 = {0, 0};
    std::vector<int> pos2 = {1, 0};

    std::cout << (mc.is_valid_move(pos1, pos2) ? "true" : "false") << std::endl;

    mc.remove_icons(pos1, pos2);

    std::cout << (mc.is_game_over() ? "true" : "false") << std::endl;

    return 0;
}