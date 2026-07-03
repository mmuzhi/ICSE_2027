#include <vector>
#include <optional>
#include <algorithm>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    char current_player;

public:
    // Note: The original Python code creates a 3xN board (hardcoding 3 for rows, using N for columns).
    // This behavior is preserved exactly here.
    TicTacToe(int N = 3) : board(3, std::vector<char>(N, ' ')), current_player('X') {}

    bool make_move(int row, int col) {
        // .at() is used to mimic Python's IndexError for out-of-bounds access
        if (board.at(row).at(col) == ' ') {
            board.at(row).at(col) = current_player;
            current_player = (current_player == 'X') ? 'O' : 'X';
            return true;
        } else {
            return false;
        }
    }

    // std::optional<char> perfectly maps to Python's "str or None" return type
    std::optional<char> check_winner() const {
        for (const auto& row : board) {
            if (row.at(0) == row.at(1) && row.at(1) == row.at(2) && row.at(0) != ' ') {
                return row.at(0);
            }
        }
        for (int col = 0; col < 3; ++col) {
            if (board.at(0).at(col) == board.at(1).at(col) && board.at(1).at(col) == board.at(2).at(col) && board.at(0).at(col) != ' ') {
                return board.at(0).at(col);
            }
        }
        if (board.at(0).at(0) == board.at(1).at(1) && board.at(1).at(1) == board.at(2).at(2) && board.at(0).at(0) != ' ') {
            return board.at(0).at(0);
        }
        if (board.at(0).at(2) == board.at(1).at(1) && board.at(1).at(1) == board.at(2).at(0) && board.at(0).at(2) != ' ') {
            return board.at(0).at(2);
        }
        return std::nullopt;
    }

    bool is_board_full() const {
        for (const auto& row : board) {
            // std::find mimics Python's `' ' in row`
            if (std::find(row.begin(), row.end(), ' ') != row.end()) {
                return false;
            }
        }
        return true;
    }
};