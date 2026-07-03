#include <vector>
#include <queue>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <sstream>
#include <iostream>

struct EightPuzzle {
    std::vector<std::vector<int>> initialState;
    std::vector<std::vector<int>> goalState;

    EightPuzzle(const std::vector<std::vector<int>>& initialState) {
        this->initialState = initialState;
        this->goalState = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    }

    std::vector<int> findBlank(const std::vector<std::vector<int>>& state) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (state[i][j] == 0) {
                    return {i, j};
                }
            }
        }
        return {-1, -1}; // Blank not found, though theoretically impossible
    }

    std::vector<std::vector<int>> move(const std::vector<std::vector<int>>& state, const std::string& direction) const {
        auto blank = findBlank(state);
        int i = blank[0], j = blank[1];
        auto newState = state; // Shallow copy; elements are integers.

        if (direction == "up" && i > 0) {
            std::swap(newState[i][j], newState[i-1][j]);
        } else if (direction == "down" && i < 2) {
            std::swap(newState[i][j], newState[i+1][j]);
        } else if (direction == "left" && j > 0) {
            std::swap(newState[i][j], newState[i][j-1]);
        } else if (direction == "right" && j < 2) {
            std::swap(newState[i][j], newState[i][j+1]);
        }
        return newState;
    }

    std::vector<std::string> getPossibleMoves(const std::vector<std::vector<int>>& state) const {
        auto blank = findBlank(state);
        int i = blank[0], j = blank[1];
        std::vector<std::string> moves;

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

    std::vector<std::string> solve() {
        auto stateToString = [](const std::vector<std::vector<int>>& state) {
            std::ostringstream oss;
            for (const auto& row : state) {
                for (int val : row) {
                    oss << val;
                }
            }
            return oss.str();
        };

        struct Node {
            std::vector<std::vector<int>> state;
            std::vector<std::string> path;

            Node(const std::vector<std::vector<int>>& state, const std::vector<std::string>& path)
                : state(state), path(path) {}
        };

        std::queue<Node> openList;
        std::set<std::string, std::function<bool(const std::string&, const std::string&)>> 
            closedList([](const std::string& a, const std::string& b) { return a == b; });

        openList.push(Node(initialState, std::vector<std::string>{}));

        while (!openList.empty()) {
            Node currentNode = openList.front();
            openList.pop();

            if (closedList.find(stateToString(currentNode.state)) != closedList.end()) {
                continue;
            }
            closedList.insert(stateToString(currentNode.state));

            if (stateToString(currentNode.state) == stateToString(goalState)) {
                return currentNode.path;
            }

            for (const std::string& move : getPossibleMoves(currentNode.state)) {
                auto newState = move(currentNode.state, move);
                auto newPath = currentNode.path;
                newPath.push_back(move);
                openList.push(Node(newState, newPath));
            }
        }
        return {}; // No solution found
    }
};