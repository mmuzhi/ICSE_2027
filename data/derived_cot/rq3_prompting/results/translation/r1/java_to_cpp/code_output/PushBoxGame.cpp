#include <vector>
#include <utility>

class PushBoxGame {
private:
    std::vector<std::vector<char>> map_;
    int playerRow_;
    int playerCol_;
    std::vector<std::pair<int,int>> targets_;
    std::vector<std::pair<int,int>> boxes_;
    int targetCount_;
    bool isGameOver_;

    void initGame() {
        for (int row = 0; row < static_cast<int>(map_.size()); ++row) {
            for (int col = 0; col < static_cast<int>(map_[row].size()); ++col) {
                char c = map_[row][col];
                if (c == 'O') {
                    playerRow_ = row;
                    playerCol_ = col;
                } else if (c == 'G') {
                    targets_.emplace_back(row, col);
                    ++targetCount_;
                } else if (c == 'X') {
                    boxes_.emplace_back(row, col);
                }
            }
        }
    }

    bool isValidMove(int row, int col) const {
        return row >= 0 && row < static_cast<int>(map_.size()) &&
               col >= 0 && col < static_cast<int>(map_[row].size()) &&
               map_[row][col] != '#';
    }

    bool isBoxAt(int row, int col) const {
        for (const auto& b : boxes_) {
            if (b.first == row && b.second == col) return true;
        }
        return false;
    }

    std::pair<int,int> getBoxPosition(int row, int col) const {
        for (const auto& b : boxes_) {
            if (b.first == row && b.second == col) return b;
        }
        // Should never happen when called after isBoxAt returns true
        return {-1, -1};
    }

    void moveBox(const std::pair<int,int>& boxPos, int newRow, int newCol) {
        for (auto& b : boxes_) {
            if (b == boxPos) {
                b = {newRow, newCol};
                break;
            }
        }
    }

public:
    PushBoxGame(const std::vector<std::vector<char>>& map)
        : map_(map), playerRow_(0), playerCol_(0), targetCount_(0), isGameOver_(false) {
        initGame();
    }

    bool checkWin() {
        int boxOnTargetCount = 0;
        for (const auto& box : boxes_) {
            for (const auto& target : targets_) {
                if (box == target) {
                    ++boxOnTargetCount;
                    break; // each box can match at most one target
                }
            }
        }
        isGameOver_ = (boxOnTargetCount == targetCount_);
        return isGameOver_;
    }

    bool move(char direction) {
        int newPlayerRow = playerRow_;
        int newPlayerCol = playerCol_;

        if (direction == 'w') {
            newPlayerRow -= 1;
        } else if (direction == 's') {
            newPlayerRow += 1;
        } else if (direction == 'a') {
            newPlayerCol -= 1;
        } else if (direction == 'd') {
            newPlayerCol += 1;
        }

        if (isValidMove(newPlayerRow, newPlayerCol)) {
            if (isBoxAt(newPlayerRow, newPlayerCol)) {
                std::pair<int,int> boxPos = getBoxPosition(newPlayerRow, newPlayerCol);
                int newBoxRow = newPlayerRow + (newPlayerRow - playerRow_);
                int newBoxCol = newPlayerCol + (newPlayerCol - playerCol_);

                if (isValidMove(newBoxRow, newBoxCol) && !isBoxAt(newBoxRow, newBoxCol)) {
                    moveBox(boxPos, newBoxRow, newBoxCol);
                    playerRow_ = newPlayerRow;
                    playerCol_ = newPlayerCol;
                }
            } else {
                playerRow_ = newPlayerRow;
                playerCol_ = newPlayerCol;
            }
        }

        return checkWin();
    }

    bool isGameOver() const {
        return isGameOver_;
    }

    int getPlayerRow() const {
        return playerRow_;
    }

    int getPlayerCol() const {
        return playerCol_;
    }

    const std::vector<std::vector<char>>& getMap() const {
        return map_;
    }

    std::vector<std::pair<int,int>> getTargets() const {
        return targets_;
    }

    int getTargetCount() const {
        return targetCount_;
    }

    std::vector<std::pair<int,int>> getBoxes() const {
        return boxes_;
    }
};