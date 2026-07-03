#include <vector>
#include <optional>

class GomokuGame {
private:
    int board_size;
    std::vector<std::vector<char>> board;
    char current_player;

    bool is_valid_position(int row, int col) const {
        return row >= 0 && row < board_size && col >= 0 && col < board_size;
    }

    bool _check_five_in_a_row(int row, int col, int dx, int dy) const {
        char symbol = board[row][col];
        int count = 1;

        for (int i = 1; i < 5; ++i) {
            int new_row = row + dx * i;
            int new_col = col + dy * i;
            if (!is_valid_position(new_row, new_col) || board[new_row][new_col] != symbol) {
                return false;
            }
            ++count;
        }
        return count == 5;
    }

public:
    GomokuGame(int board_size) : 
        board_size(board_size),
        board(board_size, std::vector<char>(board_size, ' ')),
        current_player('X') {}

    bool make_move(int row, int col) {
        if (!is_valid_position(row, col) || board[row][col] != ' ') {
            return false;
        }

        board[row][col] = current_player;
        current_player = (current_player == 'X') ? 'O' : 'X';
        return true;
    }

    std::optional<char> check_winner() const {
        const int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

        for (int row = 0; row < board_size; ++row) {
            for (int col = 0; col < board_size; ++col) {
                if (board[row][col] != ' ') {
                    for (const int* dir : directions) {
                        if (_check_five_in_a_row(row, col, dir[0], dir[1])) {
                            return board[row][col];
                        }
                    }
                }
            }
        }
        return std::nullopt;
    }
};