#include <cstddef>  // for size_t, though not strictly needed

class TicTacToe {
private:
    char board[3][3];
    char currentPlayer;

public:
    TicTacToe() : currentPlayer('X') {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    bool makeMove(int row, int col) {
        if (board[row][col] == ' ') {
            board[row][col] = currentPlayer;
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            return true;
        } else {
            return false;
        }
    }

    // Returns 'X' or 'O' if there is a winner, otherwise returns ' ' (null sentinel)
    char checkWinner() {
        // Check rows
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != ' ' &&
                board[i][0] == board[i][1] &&
                board[i][1] == board[i][2]) {
                return board[i][0];
            }
        }
        // Check columns
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] != ' ' &&
                board[0][j] == board[1][j] &&
                board[1][j] == board[2][j]) {
                return board[0][j];
            }
        }
        // Check main diagonal
        if (board[0][0] != ' ' &&
            board[0][0] == board[1][1] &&
            board[1][1] == board[2][2]) {
            return board[0][0];
        }
        // Check anti-diagonal
        if (board[0][2] != ' ' &&
            board[0][2] == board[1][1] &&
            board[1][1] == board[2][0]) {
            return board[0][2];
        }
        return ' ';  // no winner (equivalent to Java null)
    }

    bool isBoardFull() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};