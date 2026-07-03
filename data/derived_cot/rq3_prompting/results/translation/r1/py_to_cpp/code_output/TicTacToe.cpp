#include <vector>
#include <optional>
#include <stdexcept>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char current_player;

public:
    TicTacToe(int N = 3) {
        // Create board with 3 rows and N columns (mimicking the Python bug: columns are N but only indices 0..2 are used)
        board = std::vector<std::vector<char>>(3, std::vector<char>(N, ' '));
        current_player = 'X';
    }

    bool make_move(int row, int col) {
        // Out-of-bounds check to replicate Python IndexError
        if (row < 0 || row >= static_cast<int>(board.size()) ||
            col < 0 || col >= static_cast<int>(board[row].size())) {
            throw std::out_of_range("Index out of bounds");
        }
        if (board[row][col] == ' ') {
            board[row][col] = current_player;
            current_player = (current_player == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    std::optional<char> check_winner() {
        // Check rows
        for (const auto& row : board) {
            if (row[0] == row[1] && row[1] == row[2] && row[0] != ' ') {
                return row[0];
            }
        }
        // Check columns (only first three columns, as in Python)
        for (int col = 0; col < 3; ++col) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ') {
                return board[0][col];
            }
        }
        // Check main diagonal
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return board[0][0];
        }
        // Check anti-diagonal
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            return board[0][2];
        }
        return std::nullopt;
    }

    bool is_board_full() {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};