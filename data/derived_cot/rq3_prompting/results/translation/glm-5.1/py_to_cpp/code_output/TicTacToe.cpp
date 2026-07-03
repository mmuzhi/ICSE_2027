#include <vector>
#include <optional>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char current_player;

public:
    TicTacToe(int N = 3) : board(3, std::vector<char>(N, ' ')), current_player('X') {}

    bool make_move(int row, int col) {
        if (board[row][col] == ' ') {
            board[row][col] = current_player;
            current_player = (current_player == 'X') ? 'O' : 'X';
            return true;
        } else {
            return false;
        }
    }

    std::optional<char> check_winner() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                return board[i][0];
            }
        }
        for (int j = 0; j < 3; ++j) {
            if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
                return board[0][j];
            }
        }
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return board[0][0];
        }
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