#include <vector>
#include <utility>
#include <algorithm>

class PushBoxGame {
public:
    std::vector<std::string> map_;
    int player_row_;
    int player_col_;
    std::vector<std::pair<int, int>> targets_;
    std::vector<std::pair<int, int>> boxes_;
    int target_count_;
    bool is_game_over_;

    PushBoxGame(const std::vector<std::string>& map) : 
        map_(map), player_row_(0), player_col_(0), target_count_(0), is_game_over_(false) {
        initGame();
    }

private:
    void initGame() {
        for (int row = 0; row < map_.size(); row++) {
            for (int col = 0; col < map_[row].size(); col++) {
                char c = map_[row][col];
                if (c == 'O') {
                    player_row_ = row;
                    player_col_ = col;
                } else if (c == 'G') {
                    targets_.push_back(std::make_pair(row, col));
                    target_count_++;
                } else if (c == 'X') {
                    boxes_.push_back(std::make_pair(row, col));
                }
            }
        }
    }

public:
    bool checkWin() {
        int boxOnTargetCount = 0;
        for (const auto& box : boxes_) {
            if (std::find(targets_.begin(), targets_.end(), box) != targets_.end()) {
                boxOnTargetCount++;
            }
        }
        if (boxOnTargetCount == target_count_) {
            is_game_over_ = true;
            return true;
        }
        return false;
    }

    bool move(char direction) {
        int new_player_row = player_row_;
        int new_player_col = player_col_;

        switch (direction) {
            case 'w': new_player_row--; break;
            case 's': new_player_row++; break;
            case 'a': new_player_col--; break;
            case 'd': new_player_col++; break;
            default: 
                break;
        }

        if (new_player_row < 0 || new_player_row >= map_.size()) {
            return checkWin();
        }
        if (new_player_col < 0 || new_player_col >= map_[new_player_row].size()) {
            return checkWin();
        }

        if (map_[new_player_row][new_player_col] == '#') {
            return checkWin();
        }

        auto it = std::find(boxes_.begin(), boxes_.end(), std::make_pair(new_player_row, new_player_col));
        if (it != boxes_.end()) {
            int new_box_row = new_player_row + (new_player_row - player_row_);
            int new_box_col = new_player_col + (new_player_col - player_col_);

            if (new_box_row < 0 || new_box_row >= map_.size()) {
                return checkWin();
            }
            if (new_box_col < 0 || new_box_col >= map_[new_box_row].size()) {
                return checkWin();
            }

            if (map_[new_box_row][new_box_col] == '#') {
                return checkWin();
            }

            boxes_.erase(it);
            boxes_.push_back(std::make_pair(new_box_row, new_box_col));

            player_row_ = new_player_row;
            player_col_ = new_player_col;
        } else {
            player_row_ = new_player_row;
            player_col_ = new_player_col;
        }

        return checkWin();
    }
};