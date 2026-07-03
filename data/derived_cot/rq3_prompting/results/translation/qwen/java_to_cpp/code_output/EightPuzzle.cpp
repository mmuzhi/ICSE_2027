#include <vector>
#include <queue>
#include <set>
#include <string>
#include <utility> // for std::pair
#include <algorithm> // for std::equal

class EightPuzzle {
private:
    std::vector<std::vector<int>> initialState;
    std::vector<std::vector<int>> goalState;

public:
    EightPuzzle(const std::vector<std::vector<int>>& initialState) {
        this->initialState = deepCopy(initialState);
        this->goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    }

    std::pair<int, int> findBlank(const std::vector<std::vector<int>>& state) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) {
        auto blank = findBlank(state);
        int i = blank.first;
        int j = blank.second;
        auto newState = deepCopy(state);

        switch (direction[0]) {
            case 'u': // up
                if (i > 0) {
                    newState[i][j] = newState[i-1][j];
                    newState[i-1][j] = 0;
                }
                break;
            case 'd': // down
                if (i < 2) {
                    newState[i][j] = newState[i+1][j];
                    newState[i+1][j] = 0;
                }
                break;
            case 'l': // left
                if (j > 0) {
                    newState[i][j] = newState[i][j-1];
                    newState[i][j-1] = 0;
                }
                break;
            case 'r': // right
                if (j < 2) {
                    newState[i][j] = newState[i][j+1];
                    newState[i][j+1] = 0;
                }
                break;
        }
        return newState;
    }

    std::vector<std::string> getPossibleMoves(const std::vector<std::vector<int>>& state) {
        auto blank = findBlank(state);
        int i = blank.first;
        int j = blank.second;
        std::vector<std::string> moves;

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

    std::vector<std::string> solve() {
        std::queue<Node> openList;
        std::set<std::string> closedList;
        openList.push(Node(initialState, std::vector<std::string>{}));

        while (!openList.empty()) {
            Node currentNode = openList.front();
            openList.pop();
            const auto& currentState = currentNode.state;
            auto path = currentNode.path;

            if (stateToString(currentState) == goalStateString) {
                return path;
            }

            closedList.insert(stateToString(currentState));

            for (const auto& move : getPossibleMoves(currentState)) {
                auto newState = move(currentState, move);
                if (closedList.find(stateToString(newState)) == closedList.end()) {
                    auto newPath = path;
                    newPath.push_back(move);
                    openList.push(Node(newState, newPath));
                }
            }
        }
        return {};
    }

    std::string goalStateString() const {
        std::ostringstream oss;
        for (const auto& row : goalState) {
            for (int val : row) {
                oss << val;
            }
        }
        return oss.str();
    }

    private:
        std::string stateToString(const std::vector<std::vector<int>>& state) {
            std::ostringstream oss;
            for (const auto& row : state) {
                for (int val : row) {
                    oss << val;
                }
            }
            return oss.str();
        }

        std::vector<std::vector<int>> deepCopy(const std::vector<std::vector<int>>& original) {
            std::vector<std::vector<int>> copy;
            for (const auto& row : original) {
                copy.push_back(row);
            }
            return copy;
        }

        struct Node {
            std::vector<std::vector<int>> state;
            std::vector<std::string> path;

            Node(const std::vector<std::vector<int>>& state, const std::vector<std::string>& path) 
                : state(state), path(path) {}
        };
};