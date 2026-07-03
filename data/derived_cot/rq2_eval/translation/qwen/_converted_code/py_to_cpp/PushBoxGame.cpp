#include <vector>
#include <string>
#include <unordered_set>
#include <utility> // for std::pair

class PushBoxGame {
private:
    std::vector<std::string> map_;
    int player_row;
    int player_col;
    std::unordered_set<std::pair<int, int>> targets;
    std::unordered_set<std::pair<int, int>> boxes;
    int target_count;
    bool is_game_over;

    void init_game();

public:
    PushBoxGame(const std::vector<std::string>& map);
    bool check_win();
    bool move(char direction);
};

PushBoxGame::PushBoxGame(const std::vector<std::string>& map)
    : map_(map), player_row(0), player_col(0), target_count(0), is_game_over(false) {
    init_game();
}

void PushBoxGame::init_game() {
    for (int row = 0; row < map_.size(); ++row) {
        for (int col = 0; col < map_[row].size(); ++col) {
            if (map_[row][col] == 'O') {
                player_row = row;
                player_col = col;
            } else if (map_[row][col] == 'G') {
                targets.insert(std::make_pair(row, col));
                target_count++;
            } else if (map_[row][col] == 'X') {
                boxes.insert(std::make_pair(row, col));
            }
        }
    }
}

bool PushBoxGame::check_win() {
    is_game_over = true;
    for (const auto& box : boxes) {
        if (targets.find(box) == targets.end()) {
            is_game_over = false;
            break;
        }
    }
    return is_game_over;
}

bool PushBoxGame::move(char direction) {
    int new_player_row = player_row;
    int new_player_col = player_col;

    switch(direction) {
        case 'w': new_player_row--; break;
        case 's': new_player_row++; break;
        case 'a': new_player_col--; break;
        case 'd': new_player_col++; break;
        default: return false;
    }

    if (new_player_row < 0 || new_player_row >= map_.size() || 
        new_player_col < 0 || new_player_col >= map_[new_player_row].size() ||
        map_[new_player_row][new_player_col] == '#') {
        return check_win();
    }

    if (boxes.find(std::make_pair(new_player_row, new_player_col)) != boxes.end()) {
        int new_box_row = new_player_row + (new_player_row - player_row);
        int new_box_col = new_player_col + (new_player_col - player_col);

        if (new_box_row < 0 || new_box_row >= map_.size() || 
            new_box_col < 0 || new_box_col >= map_[new_box_row].size() ||
            map_[new_box_row][new_box_col] == '#') {
            return check_win();
        }

        boxes.erase(std::make_pair(new_player_row, new_player_col));
        boxes.insert(std::make_pair(new_box_row, new_box_col));
    }

    player_row = new_player_row;
    player_col = new_player_col;

    return check_win();
}