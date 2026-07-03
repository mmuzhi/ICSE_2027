#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <optional>
#include <utility>

class EightPuzzle {
private:
    std::vector<std::vector<int>> initialState;
    std::vector<std::vector<int>> goalState;

    struct Node {
        std::vector<std::vector<int>> state;
        std::vector<std::string> path;
    };

    std::pair<int, int> findBlank(const std::vector<std::vector<int>>& state) const {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (state[i][j] == 0)
                    return {i, j};
        // shouldn't happen, but keep compiler happy
        return {-1, -1};
    }

    std::vector<std::vector<int>> deepCopy(const std::vector<std::vector<int>>& original) const {
        std::vector<std::vector<int>> copy(original.size());
        for (std::size_t i = 0; i < original.size(); ++i)
            copy[i] = original[i]; // vector copy is deep
        return copy;
    }

    std::string stateToString(const std::vector<std::vector<int>>& state) const {
        std::ostringstream sb;
        for (const auto& row : state)
            for (int val : row)
                sb << val;
        return sb.str();
    }

public:
    EightPuzzle(const std::vector<std::vector<int>>& initialState)
        : initialState(deepCopy(initialState)),
          goalState({{1,2,3},{4,5,6},{7,8,0}}) {}

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state,
                                       const std::string& direction) const {
        auto [i, j] = findBlank(state);
        std::vector<std::vector<int>> newState = deepCopy(state);

        if (direction == "up" && i > 0) {
            newState[i][j] = newState[i-1][j];
            newState[i-1][j] = 0;
        } else if (direction == "down" && i < 2) {
            newState[i][j] = newState[i+1][j];
            newState[i+1][j] = 0;
        } else if (direction == "left" && j > 0) {
            newState[i][j] = newState[i][j-1];
            newState[i][j-1] = 0;
        } else if (direction == "right" && j < 2) {
            newState[i][j] = newState[i][j+1];
            newState[i][j+1] = 0;
        }
        return newState;
    }

    std::vector<std::string> getPossibleMoves(const std::vector<std::vector<int>>& state) const {
        std::vector<std::string> moves;
        auto [i, j] = findBlank(state);
        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");
        return moves;
    }

    std::optional<std::vector<std::string>> solve() const {
        std::queue<Node> openList;
        std::unordered_set<std::string> closedList;

        openList.push({deepCopy(initialState), {}});

        while (!openList.empty()) {
            Node current = std::move(openList.front());
            openList.pop();

            const auto& currentState = current.state;
            const auto& path = current.path;

            closedList.insert(stateToString(currentState));

            if (currentState == goalState) {
                return path;
            }

            for (const std::string& moveDir : getPossibleMoves(currentState)) {
                std::vector<std::vector<int>> newState = move(currentState, moveDir);
                std::string stateKey = stateToString(newState);
                if (closedList.find(stateKey) == closedList.end()) {
                    std::vector<std::string> newPath = path;
                    newPath.push_back(moveDir);
                    openList.push({std::move(newState), std::move(newPath)});
                }
            }
        }

        return std::nullopt;
    }
};