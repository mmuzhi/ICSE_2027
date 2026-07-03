#include <vector>
#include <utility>

class PushBoxGame {
private:
    std::vector<std::vector<char>> map;
    int playerRow;
    int playerCol;
    std::vector<std::pair<int, int>> targets;
    std::vector<std::pair<int, int>> boxes;
    int targetCount;
    bool isGameOver;

    void initGame() {
        for (int row = 0; row < map.size(); row++) {
            for (int col = 0; col < map[row].size(); col++) {
                if (map[row][col] == 'O') {
                    playerRow = row;
                    playerCol = col;
                } else if (map[row][col] == 'G') {
                    targets.push_back(std::make_pair(row, col));
                    targetCount++;
                } else if (map[row][col] == 'X') {
                    boxes.push_back(std::make_pair(row, col));
                }
            }
        }
    }

    bool isValidMove(int row, int col) {
        if (row < 0 || row >= map.size()) return false;
        if (col < 0 || col >= map[row].size()) return false;
        return map[row][col] != '#';
    }

    bool isBoxAt(int row, int col) {
        for (const auto& box : boxes) {
            if (box == std::make_pair(row, col)) {
                return true;
            }
        }
        return false;
    }

    void moveBox(int oldRow, int oldCol, int newRow, int newCol) {
        for (auto& box : boxes) {
            if (box == std::make_pair(oldRow, oldCol)) {
                box = std::make_pair(newRow, newCol);
                break;
            }
        }
    }

public:
    PushBoxGame(const std::vector<std::vector<char>>& map) : map(map) {
        playerRow = 0;
        playerCol = 0;
        targetCount = 0;
        isGameOver = false;
        initGame();
    }

    bool checkWin() {
        int boxOnTargetCount = 0;
        for (const auto& box : boxes) {
            for (const auto& target : targets) {
                if (box == target) {
                    boxOnTargetCount++;
                }
            }
        }
        isGameOver = (boxOnTargetCount == targetCount);
        return isGameOver;
    }

    bool move(char direction) {
        int newPlayerRow = playerRow;
        int newPlayerCol = playerCol;

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

    bool isGameOver() const {
        return isGameOver;
    }

    int getPlayerCol() const {
        return playerCol;
    }

    int getPlayerRow() const {
        return playerRow;
    }

    std::vector<std::pair<int, int>>& getTargets() {
        return targets;
    }

    int getTargetCount() const {
        return targetCount;
    }

    std::vector<std::vector<char>>& getMap() {
        return map;
    }

    std::vector<std::pair<int, int>>& getBoxes() {
        return boxes;
    }
};