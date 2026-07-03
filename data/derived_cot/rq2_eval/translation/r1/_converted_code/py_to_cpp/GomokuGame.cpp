#include <vector>
#include <utility>

using namespace std;

class GomokuGame {
private:
    int board_size;
    vector<vector<char>> board;
    char current_player;

    bool _check_five_in_a_row(int row, int col, pair<int, int> direction) {
        char symbol = board[row][col];
        int dx = direction.first;
        int dy = direction.second;
        for (int step = 1; step < 5; step++) {
            int new_row = row + dx * step;
            int new_col = col + dy * step;
            if (new_row < 0 || new_row >= board_size || new_col < 0 || new_col >= board_size) {
                return false;
            }
            if (board[new_row][new_col] != symbol) {
                return false;
            }
        }
        return true;
    }

public:
    GomokuGame(int size) : board_size(size), current_player('X') {
        board = vector<vector<char>>(board_size, vector<char>(board_size, ' '));
    }

    bool make_move(int row, int col) {
        if (board[row][col] == ' ') {
            board[row][col] = current_player;
            current_player = (current_player == 'X') ? 'O' : 'X';
            return true;
        }
        return false;
    }

    char check_winner() {
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
        for (int row = 0; row < board_size; row++) {
            for (int col = 0; col < board_size; col++) {
                if (board[row][col] != ' ') {
                    for (const auto& dir : directions) {
                        if (_check_five_in_a_row(row, col, dir)) {
                            return board[row][col];
                        }
                    }
                }
            }
        }
        return '\0';
    }
};