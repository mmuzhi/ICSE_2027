#include <iostream>
#include <vector>
#include <string>

class GomokuGame {
private:
    int boardSize;
    std::vector<std::vector<char>> board;
    char currentPlayer;

    bool _check_five_in_a_row(int row, int col, const std::vector<int>& direction) {
        int dx = direction[0];
        int dy = direction[1];
        int count = 1;
        char symbol = board[row][col];
        for (int i = 1; i < 5; i++) {
            int newRow = row + dx * i;
            int newCol = col + dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                break;
            }
            if (board[newRow][newCol] != symbol) {
                break;
            }
            count++;
        }
        for (int i = 1; i < 5; i++) {
            int newRow = row - dx * i;
            int newCol = col - dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                break;
            }
            if (board[newRow][newCol] != symbol) {
                break;
            }
            count++;
        }
        return count >= 5;
    }

public:
    GomokuGame(int boardSize) : boardSize(boardSize), currentPlayer('X') {
        board.resize(boardSize, std::vector<char>(boardSize, ' '));
    }

    bool make_move(int row, int col) {
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    std::string checkWinner() {
        const std::vector<std::vector<int>> directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                if (board[row][col] != ' ') {
                    for (const auto& direction : directions) {
                        if (checkFiveInARow(row, col, direction)) {
                            return std::string(1, board[row][col]);
                        }
                    }
                }
            }
        }
        return "null";
    }
};

int main() {
    GomokuGame gomokuGame(10);
    std::vector<std::vector<int>> moves = {{5,5}, {0,0}, {5,4}, {0,1}, {5,3}, {0,2}, {5,2}, {0,3}, {5,1}};
    for (const auto& move : moves) {
        gomokuGame.make_move(move[0], move[1]);
    }
    std::cout << gomokuGame.checkWinner() << std::endl;
    return 0;
}