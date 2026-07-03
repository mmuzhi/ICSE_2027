#include <vector>
#include <string>

class TicTacToe {
private:
    int N;
    char current_player;
    std::vector<std::vector<char>> board;

public:
    TicTacToe(int N = 3);

    bool make_move(int row, int col);

    char check_winner();

    bool is_board_full();
};