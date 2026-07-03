#include <vector>
#include <iostream>
#include <stdexcept>

class GomokuGame {
private:
    int boardSize;
    std::vector<std::vector<char>> board;
    char currentPlayer;

    bool _check_five_in_a_row(int row, int col, int dx, int dy) {
        int count = 1;
        char symbol = board[row][col];
        // Check in the positive direction
        for (int i = 1; i < 5; ++i) {
            int newRow = row + dx * i;
            int newCol = col + dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) break;
            if (board[newRow][newCol] != symbol) break;
            ++count;
        }
        // Check in the negative direction
        for (int i = 1; i < 5; ++i) {
            int newRow = row - dx * i;
            int newCol = col - dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) break;
            if (board[newRow][newCol] != symbol) break;
            ++count;
        }
        return count >= 5;
    }

public:
    GomokuGame(int boardSize) : boardSize(boardSize) {
        board = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, ' '));
        currentPlayer = 'X';
    }

    bool make_move(int row, int col) {
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize) {
            throw std::out_of_range("Invalid board index");
        }
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    char* checkWinner() {
        static const int directions[][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (board[row][col] != ' ') {
                    for (const auto& dir : directions) {
                        if (checkFiveInARow(row, col, dir[0], dir[1])) {
                            return &board[row][col];
                        }
                    }
                }
            }
        }
        return nullptr;
    }

    static void main() {
        GomokuGame gomokuGame(10);
        int moves[][2] = {{5, 5}, {0, 0}, {5, 4}, {0, 1}, {5, 3}, {0, 2}, {5, 2}, {0, 3}, {5, 1}};
        for (auto& move : moves) {
            gomokuGame.make_move(move[0], move[1]);
        }
        char* winner = gomokuGame.checkWinner();
        if (winner) {
            std::cout << *winner << std::endl;
        } else {
            std::cout << "null" << std::endl;
        }
    }
};

int main() {
    GomokuGame::main();
    return 0;
}