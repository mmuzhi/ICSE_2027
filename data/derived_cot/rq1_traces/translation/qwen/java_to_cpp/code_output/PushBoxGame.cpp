#include <vector>
#include <utility> // for std::pair
#include <algorithm> // for std::find_if

class PushBoxGame {
private:
    std::vector<std::vector<char>> map;
    int playerRow;
    int playerCol;
    std::vector<std::pair<int, int>> targets;
    std::vector<std::pair<int, int>> boxes;
    int targetCount;
    bool isGameOver;

    void initGame();

    bool isValidMove(int row, int col);
    bool isBoxAt(int row, int col);
    std::pair<int, int> getBoxPosition(int row, int col);
    void moveBox(const std::pair<int, int>& boxPosition, int newRow, int newCol);

public:
    PushBoxGame(const std::vector<std::vector<char>>& map);
    bool checkWin();
    bool move(char direction);
    bool isGameOver() const;
    int getPlayerCol() const;
    int getPlayerRow() const;
    std::vector<std::pair<int, int>> getTargets() const;
    int getTargetCount() const;
    std::vector<std::vector<char>> getMap() const;
    std::vector<std::pair<int, int>> getBoxes() const;
};