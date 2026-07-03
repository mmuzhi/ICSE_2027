#include <vector>
#include <string>
#include <utility> // for std::pair
#include <algorithm> // for std::find

class PushBoxGame {
private:
    std::vector<std::string> game_map;
    int player_row;
    int player_col;
    std::vector<std::pair<int, int>> targets;
    std::vector<std::pair<int, int>> boxes;
    int target_count;
    bool is_game_over;

    void init_game();

public:
    PushBoxGame(const std::vector<std::string>& map);
    bool check_win();
    bool move(char direction);
};

PushBoxGame::PushBoxGame(const std::vector<std::string>& map) {
    game_map = map;
    player_row = 0;
    player_col = 0;
    target_count = 0;
    is_game_over = false;
    init_game();
}

void PushBoxGame::init_game() {
    for (int row = 0; row < game_map.size(); row++) {
        for (int col = 0; col < game_map[row].size(); col++) {
            if (game_map[row][col] == 'O') {
                player_row = row;
                player_col = col;
            } else if (game_map[row][col] == 'G') {
                targets.push_back(std::make_pair(row, col));
                target_count++;
            } else if (game_map[row][col] == 'X') {
                boxes.push_back(std::make_pair(row, col));
            }
        }
    }
}

bool PushBoxGame::check_win() {
    int box_on_target_count = 0;
    for (const auto& box : boxes) {
        for (const auto& target : targets) {
            if (box.first == target.first && box.second == target.second) {
                box_on_target_count++;
                break;
            }
        }
    }
    if (box_on_target_count == target_count) {
        is_game_over = true;
    }
    return is_game_over;
}

bool PushBoxGame::move(char direction) {
    int new_player_row = player_row;
    int new_player_col = player_col;

    switch (direction) {
        case 'w': new_player_row--; break;
        case 's': new_player_row++; break;
        case 'a': new_player_col--; break;
        case 'd': new_player_col++; break;
        default: 
            return false;
    }

    if (new_player_row < 0 || new_player_row >= game_map.size() || 
        new_player_col < 0 || new_player_col >= game_map[new_player_row].size() ||
        game_map[new_player_row][new_player_col] == '#') {
        return false;
    }

    auto it = std::find(boxes.begin(), boxes.end(), std::make_pair(new_player_row, new_player_col));
    if (it != boxes.end()) {
        int new_box_row = new_player_row + (new_player_row - player_row);
        int new_box_col = new_player_col + (new_player_col - player_col);

        if (new_box_row < 0 || new_box_row >= game_map.size() || 
            new_box_col < 0 || new_box_col >= game_map[new_box_row].size() ||
            game_map[new_box_row][new_box_col] == '#') {
            return false;
        }

        boxes.erase(it);
        boxes.push_back(std::make_pair(new_box_row, new_box_col));
    }

    player_row = new_player_row;
    player_col = new_player_col;

    return check_win();
}