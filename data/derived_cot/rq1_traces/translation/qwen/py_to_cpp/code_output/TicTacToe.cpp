#include <vector>
#include <string>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char current_player;

public:
    TicTacToe(int N = 3) {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
        current_player = 'X';
    }

    bool make_move(int row, int col) {
        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            return false;
        }
        if (board[row][col] == ' ') {
            board[row][col] = current_player;
            current_player = (current_player == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    std::string check_winner() {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
                return std::string(1, board[i][0]);
            }
        }

        for (int j = 0; j < 3; j++) {
            if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
                return std::string(1, board[0][j]);
            }
        }

        if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
            return std::string(1, board[0][0]);
        }

        if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
            return std::string(1, board[0][2]);
        }

        return std::string();
    }

    bool is_board_full() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};