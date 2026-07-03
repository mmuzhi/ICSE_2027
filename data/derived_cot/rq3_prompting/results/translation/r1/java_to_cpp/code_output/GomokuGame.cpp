#include <iostream>
#include <vector>

class GomokuGame {
private:
    int boardSize;
    std::vector<std::vector<char>> board;
    char currentPlayer;

    bool checkFiveInARow(int row, int col, int dx, int dy) {
        int count = 1;
        char symbol = board[row][col];

        // positive direction
        for (int i = 1; i < 5; ++i) {
            int newRow = row + dx * i;
            int newCol = col + dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                break;
            }
            if (board[newRow][newCol] != symbol) {
                break;
            }
            ++count;
        }

        // negative direction
        for (int i = 1; i < 5; ++i) {
            int newRow = row - dx * i;
            int newCol = col - dy * i;
            if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) {
                break;
            }
            if (board[newRow][newCol] != symbol) {
                break;
            }
            ++count;
        }

        return count >= 5;
    }

public:
    GomokuGame(int boardSize) : boardSize(boardSize) {
        board = std::vector<std::vector<char>>(boardSize, std::vector<char>(boardSize, ' '));
        currentPlayer = 'X';
    }

    bool makeMove(int row, int col) {
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    char checkWinner() {
        int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (board[row][col] != ' ') {
                    for (int d = 0; d < 4; ++d) {
                        int dx = directions[d][0];
                        int dy = directions[d][1];
                        if (checkFiveInARow(row, col, dx, dy)) {
                            return board[row][col];
                        }
                    }
                }
            }
        }
        return '\0'; // no winner
    }
};

int main() {
    GomokuGame gomokuGame(10);
    int moves[9][2] = {{5, 5}, {0, 0}, {5, 4}, {0, 1}, {5, 3}, {0, 2}, {5, 2}, {0, 3}, {5, 1}};
    for (int i = 0; i < 9; ++i) {
        gomokuGame.makeMove(moves[i][0], moves[i][1]);
    }
    char winner = gomokuGame.checkWinner();
    if (winner == '\0') {
        std::cout << "null" << std::endl;
    } else {
        std::cout << winner << std::endl;
    }
    return 0;
}