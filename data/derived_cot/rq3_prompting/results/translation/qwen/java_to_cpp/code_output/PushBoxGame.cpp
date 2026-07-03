#include <vector>
#include <utility> // for std::pair
#include <algorithm> // for std::find_if

class PushBoxGame {
private:
    std::vector<std::vector<char>> map;
    int playerRow, playerCol;
    std::vector<std::pair<int, int>> targets;
    std::vector<std::pair<int, int>> boxes;
    bool isGameOver;

    void initGame();

    bool isValidMove(int row, int col) {
        if (row < 0 || row >= map.size() || col < 0 || col >= map[row].size()) 
            return false;
        return map[row][col] != '#';
    }

    bool isBoxAt(int row, int col) {
        return std::any_of(boxes.begin(), boxes.end(), 
            [row, col](const auto& box) { return box == std::make_pair(row, col); });
    }

    std::pair<int, int> getBoxPosition(int row, int col) {
        auto it = std::find_if(boxes.begin(), boxes.end(),
            [row, col](const auto& box) { return box == std::make_pair(row, col); });
        return it != boxes.end() ? *it : std::make_pair(-1, -1);
    }

    void moveBox(int row, int col, int newRow, int newCol) {
        auto it = std::find_if(boxes.begin(), boxes.end(),
            [row, col](const auto& box) { return box == std::make_pair(row, col); });
        if (it != boxes.end()) {
            it->first = newRow;
            it->second = newCol;
        }
    }

public:
    PushBoxGame(const std::vector<std::vector<char>>& map) {
        map_ = map;
        playerRow = 0;
        playerCol = 0;
        targets.clear();
        boxes.clear();
        isGameOver = false;
        initGame();
    }

    bool checkWin() {
        int boxOnTargetCount = 0;
        for (const auto& box : boxes) {
            if (std::find_if(targets.begin(), targets.end(),
                [&box](const auto& target) { return target == box; }) != targets.end()) {
                boxOnTargetCount++;
            }
        }
        isGameOver = (boxOnTargetCount == targets.size());
        return isGameOver;
    }

    bool move(char direction) {
        int newPlayerRow = playerRow;
        int newPlayerCol = playerCol;

        switch(direction) {
            case 'w': newPlayerRow--; break;
            case 's': newPlayerRow++; break;
            case 'a': newPlayerCol--; break;
            case 'd': newPlayerCol++; break;
            default: return checkWin();
        }

        if (isValidMove(newPlayerRow, newPlayerCol)) {
            if (isBoxAt(newPlayerRow, newPlayerCol)) {
                auto boxPos = getBoxPosition(newPlayerRow, newPlayerCol);
                int newBoxRow = newPlayerRow + (newPlayerRow - playerRow);
                int newBoxCol = newPlayerCol + (newPlayerCol - playerCol);

                if (isValidMove(newBoxRow, newBoxCol) && !isBoxAt(newBoxRow, newBoxCol)) {
                    moveBox(newPlayerRow, newPlayerCol, newBoxRow, newBoxCol);
                    playerRow = newPlayerRow;
                    playerCol = newPlayerCol;
                }
            } else {
                playerRow = newPlayerRow;
                playerCol = newPlayerCol;
            }
        }

        return checkWin();
    }

    bool isGameOver() const { return isGameOver; }

    int getPlayerRow() const { return playerRow; }
    int getPlayerCol() const { return playerCol; }

    std::vector<std::pair<int, int>> getTargets() const {
        return targets;
    }

    int getTargetCount() const { return targets.size(); }

    std::vector<std::vector<char>> getMap() const {
        return map;
    }

    std::vector<std::pair<int, int>> getBoxes() const {
        return boxes;
    }

private:
    std::vector<std::vector<char>> map_;
};