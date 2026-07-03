#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

class MahjongConnect {
private:
    std::vector<int> BOARD_SIZE;
    std::vector<std::string> ICONS;
    std::vector<std::vector<std::string>> board;

    bool isValidPosition(int x, int y) {
        return x >= 0 && x < BOARD_SIZE[0] && y >= 0 && y < BOARD_SIZE[1];
    }

    bool dfs(int x, int y, const std::vector<int>& target, std::vector<std::vector<bool>>& visited) {
        if (x == target[0] && y == target[1]) {
            return true;
        }

        if (visited[x][y]) {
            return false;
        }

        visited[x][y] = true;

        const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const auto& dir : directions) {
            int newX = x + dir[0];
            int newY = y + dir[1];
            if (isValidPosition(newX, newY) && !visited[newX][newY] && board[newX][newY] == board[x][y]) {
                if (dfs(newX, newY, target, visited)) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    MahjongConnect(const std::vector<int>& BOARD_SIZE, const std::vector<std::string>& ICONS) {
        this->BOARD_SIZE = BOARD_SIZE;
        this->ICONS = ICONS;
        this->board = createBoard();
    }

    std::vector<std::vector<std::string>> createBoard() {
        std::vector<std::vector<std::string>> board(BOARD_SIZE[0], std::vector<std::string>(BOARD_SIZE[1]));
        std::srand(std::time(0)); // Seed the random number generator
        for (int i = 0; i < BOARD_SIZE[0]; ++i) {
            for (int j = 0; j < BOARD_SIZE[1]; ++j) {
                board[i][j] = ICONS[std::rand() % ICONS.size()];
            }
        }
        return board;
    }

    bool isValidMove(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        if (!isValidPosition(pos1[0], pos1[1]) || !isValidPosition(pos2[0], pos2[1])) {
            return false;
        }

        if (pos1[0] == pos2[0] && pos1[1] == pos2[1]) {
            return false;
        }

        if (board[pos1[0]][pos1[1]] != board[pos2[0]][pos2[1]]) {
            return false;
        }

        std::vector<std::vector<bool>> visited(BOARD_SIZE[0], std::vector<bool>(BOARD_SIZE[1], false));
        return dfs(pos1[0], pos1[1], {pos2[0], pos2[1]}, visited);
    }

    void removeIcons(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        board[pos1[0]][pos1[1]] = " ";
        board[pos2[0]][pos2[1]] = " ";
    }

    bool isGameOver() {
        for (int i = 0; i < BOARD_SIZE[0]; ++i) {
            for (int j = 0; j < BOARD_SIZE[1]; ++j++) {
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
    std::cout << (mc.isValidMove({0, 0}, {1, 0}) ? "true" : "false") << std::endl;
    mc.removeIcons({0, 0}, {1, 0});
    std::cout << (mc.isGameOver() ? "true" : "false") << std::endl;

    return 0;
}