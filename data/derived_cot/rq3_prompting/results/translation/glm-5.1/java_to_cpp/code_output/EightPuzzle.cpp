#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <optional>

class EightPuzzle {
private:
    std::vector<std::vector<int>> initialState;
    std::vector<std::vector<int>> goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    struct Node {
        std::vector<std::vector<int>> state;
        std::vector<std::string> path;
    };

    static std::vector<std::vector<int>> deepCopy(const std::vector<std::vector<int>>& original) {
        return original;
    }

    static std::string stateToString(const std::vector<std::vector<int>>& state) {
        std::string result;
        for (const auto& row : state) {
            for (int val : row) {
                result += std::to_string(val);
            }
        }
        return result;
    }

    static bool equals(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b) {
        return a == b;
    }

public:
    EightPuzzle(const std::vector<std::vector<int>>& initialState)
        : initialState(deepCopy(initialState)) {}

    std::vector<int> findBlank(const std::vector<std::vector<int>>& state) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {};
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) const {
        std::vector<int> blank = findBlank(state);
        int i = blank[0], j = blank[1];
        std::vector<std::vector<int>> newState = deepCopy(state);

        if (direction == "up") {
            if (i > 0) {
                newState[i][j] = newState[i - 1][j];
                newState[i - 1][j] = 0;
            }
        } else if (direction == "down") {
            if (i < 2) {
                newState[i][j] = newState[i + 1][j];
                newState[i + 1][j] = 0;
            }
        } else if (direction == "left") {
            if (j > 0) {
                newState[i][j] = newState[i][j - 1];
                newState[i][j - 1] = 0;
            }
        } else if (direction == "right") {
            if (j < 2) {
                newState[i][j] = newState[i][j + 1];
                newState[i][j + 1] = 0;
            }
        }
        return newState;
    }

    std::vector<std::string> getPossibleMoves(const std::vector<std::vector<int>>& state) const {
        std::vector<std::string> moves;
        std::vector<int> blank = findBlank(state);
        int i = blank[0], j = blank[1];

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

    std::optional<std::vector<std::string>> solve() {
        std::queue<Node> openList;
        std::unordered_set<std::string> closedList;
        openList.push({initialState, {}});

        while (!openList.empty()) {
            Node currentNode = openList.front();
            openList.pop();

            closedList.insert(stateToString(currentNode.state));

            if (equals(currentNode.state, goalState)) {
                return currentNode.path;
            }

            for (const std::string& mv : getPossibleMoves(currentNode.state)) {
                std::vector<std::vector<int>> newState = this->move(currentNode.state, mv);
                if (closedList.find(stateToString(newState)) == closedList.end()) {
                    std::vector<std::string> newPath = currentNode.path;
                    newPath.push_back(mv);
                    openList.push({newState, newPath});
                }
            }
        }
        return std::nullopt;
    }
};