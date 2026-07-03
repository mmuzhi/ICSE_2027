#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

class MahjongConnect {
public:
    std::vector<int> BOARD_SIZE;
    std::vector<std::string> ICONS;
    std::vector<std::vector<std::string>> board;

    // Constructor
    MahjongConnect(const std::vector<int>& BOARD_SIZE, const std::vector<std::string>& ICONS)
        : BOARD_SIZE(BOARD_SIZE), ICONS(ICONS) {
        board = createBoard();
    }

    // Create board with random icons
    std::vector<std::vector<std::string>> createBoard() {
        std::vector<std::vector<std::string>> board(
            BOARD_SIZE[0], std::vector<std::string>(BOARD_SIZE[1]));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, ICONS.size() - 1);
        for (int i = 0; i < BOARD_SIZE[0]; ++i) {
            for (int j = 0; j < BOARD_SIZE[1]; ++j) {
                board[i][j] = ICONS[dis(gen)];
            }
        }
        return board;
    }

    // Check if a move is valid
    bool isValidMove(const std::vector<int>& pos1, const std::vector<int>& pos2) {
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

        return hasPath(pos1, pos2);
    }

private:
    // Check if a position is within board bounds
    bool isValidPosition(int x, int y) {
        return x >= 0 && x < BOARD_SIZE[0] && y >= 0 && y < BOARD_SIZE[1];
    }

public:
    // Check if there is a path between two positions (same icon, adjacent via same icon cells)
    bool hasPath(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        int x1 = pos1[0], y1 = pos1[1];
        int x2 = pos2[0], y2 = pos2[1];

        if (!isValidPosition(x1, y1) || !isValidPosition(x2, y2)) {
            return false;
        }

        std::vector<std::vector<bool>> visited(
            BOARD_SIZE[0], std::vector<bool>(BOARD_SIZE[1], false));
        return dfs(x1, y1, pos2, visited);
    }

private:
    // Depth-first search for path
    bool dfs(int x, int y, const std::vector<int>& target, std::vector<std::vector<bool>>& visited) {
        if (x == target[0] && y == target[1]) {
            return true;
        }

        if (visited[x][y]) {
            return false;
        }

        visited[x][y] = true;

        // Directions: right, left, down, up
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (isValidPosition(newX, newY) && !visited[newX][newY] &&
                board[newX][newY] == board[x][y]) {
                if (dfs(newX, newY, target, visited)) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    // Remove icons at two positions (set to space)
    void removeIcons(const std::vector<int>& pos1, const std::vector<int>& pos2) {
        board[pos1[0]][pos1[1]] = " ";
        board[pos2[0]][pos2[1]] = " ";
    }

    // Check if game is over (all cells are space)
    bool isGameOver() {
        for (int i = 0; i < BOARD_SIZE[0]; ++i) {
            for (int j = 0; j < BOARD_SIZE[1]; ++j) {
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
    std::cout << std::boolalpha << mc.isValidMove({0, 0}, {1, 0}) << std::endl;
    mc.removeIcons({0, 0}, {1, 0});
    std::cout << std::boolalpha << mc.isGameOver() << std::endl;

    return 0;
}