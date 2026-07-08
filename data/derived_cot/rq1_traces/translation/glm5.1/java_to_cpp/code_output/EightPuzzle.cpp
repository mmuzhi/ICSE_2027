#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <optional>
#include <stdexcept>

namespace org::example {

class EightPuzzle {
private:
    std::vector<std::vector<int>> initialState;
    std::vector<std::vector<int>> goalState;

    struct Node {
        std::vector<std::vector<int>> state;
        std::vector<std::string> path;

        Node(std::vector<std::vector<int>> s, std::vector<std::string> p)
            : state(std::move(s)), path(std::move(p)) {}
    };

    std::string stateToString(const std::vector<std::vector<int>>& state) {
        std::string sb;
        for (const auto& row : state) {
            for (int val : row) {
                sb += std::to_string(val);
            }
        }
        return sb;
    }

    std::vector<std::vector<int>> deepCopy(const std::vector<std::vector<int>>& original) {
        std::vector<std::vector<int>> copy(original.size());
        for (size_t i = 0; i < original.size(); i++) {
            copy[i] = std::vector<int>(original[i].begin(), original[i].end());
        }
        return copy;
    }

public:
    EightPuzzle(const std::vector<std::vector<int>>& initialState) {
        this->initialState = deepCopy(initialState);
        this->goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    }

    std::vector<int> findBlank(const std::vector<std::vector<int>>& state) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {}; // Equivalent to null
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) {
        std::vector<int> blank = findBlank(state);
        if (blank.empty()) {
            throw std::runtime_error("Blank position not found"); // Equivalent to NullPointerException
        }
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

    std::vector<std::string> getPossibleMoves(const std::vector<std::vector<int>>& state) {
        std::vector<std::string> moves;
        std::vector<int> blank = findBlank(state);
        if (blank.empty()) {
            throw std::runtime_error("Blank position not found");
        }
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
        openList.push(Node(initialState, {}));

        while (!openList.empty()) {
            Node currentNode = openList.front();
            openList.pop();
            std::vector<std::vector<int>> currentState = currentNode.state;
            std::vector<std::string> path = currentNode.path;
            closedList.insert(stateToString(currentState));

            if (currentState == goalState) { // operator== does a deep equals like Arrays.deepEquals
                return path;
            }

            for (const std::string& moveDir : getPossibleMoves(currentState)) {
                std::vector<std::vector<int>> newState = this->move(currentState, moveDir);
                if (closedList.find(stateToString(newState)) == closedList.end()) {
                    std::vector<std::string> newPath = path;
                    newPath.push_back(moveDir);
                    openList.push(Node(newState, newPath));
                }
            }
        }
        return std::nullopt; // Equivalent to null
    }
};

} // namespace org::example