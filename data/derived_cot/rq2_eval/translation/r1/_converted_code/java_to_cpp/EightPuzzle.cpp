#include <array>
#include <vector>
#include <list>
#include <queue>
#include <unordered_set>
#include <string>
#include <stdexcept>
#include <utility>

using State = std::array<std::array<int, 3>, 3>;

class EightPuzzle {
private:
    State initialState;
    State goalState;

public:
    EightPuzzle(const State& initialState) : initialState(initialState) {
        goalState = { { {1,2,3}, {4,5,6}, {7,8,0} } };
    }

    std::pair<int, int> findBlank(const State& state) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (state[i][j] == 0) {
                    return std::make_pair(i, j);
                }
            }
        }
        throw std::runtime_error("Blank not found");
    }

    State move(const State& state, const std::string& direction) {
        std::pair<int, int> blank = findBlank(state);
        int i = blank.first;
        int j = blank.second;
        State newState = state;

        if (direction == "up") {
            if (i > 0) {
                newState[i][j] = newState[i-1][j];
                newState[i-1][j] = 0;
            }
        } else if (direction == "down") {
            if (i < 2) {
                newState[i][j] = newState[i+1][j];
                newState[i+1][j] = 0;
            }
        } else if (direction == "left") {
            if (j > 0) {
                newState[i][j] = newState[i][j-1];
                newState[i][j-1] = 0;
            }
        } else if (direction == "right") {
            if (j < 2) {
                newState[i][j] = newState[i][j+1];
                newState[i][j+1] = 0;
            }
        }
        return newState;
    }

    std::vector<std::string> getPossibleMoves(const State& state) {
        std::pair<int, int> blank = findBlank(state);
        int i = blank.first;
        int j = blank.second;
        std::vector<std::string> moves;

        if (i > 0) moves.push_back("up");
        if (i < 2) moves.push_back("down");
        if (j > 0) moves.push_back("left");
        if (j < 2) moves.push_back("right");

        return moves;
    }

    std::list<std::string>* solve() {
        struct Node {
            State state;
            std::list<std::string> path;
            Node(const State& s, const std::list<std::string>& p) : state(s), path(p) {}
        };

        std::queue<Node> openList;
        std::unordered_set<std::string> closedList;

        openList.push(Node(initialState, std::list<std::string>()));

        while (!openList.empty()) {
            Node currentNode = openList.front();
            openList.pop();
            State currentState = currentNode.state;
            std::string currentStateString = stateToString(currentState);

            if (closedList.find(currentStateString) != closedList.end()) {
                continue;
            }
            closedList.insert(currentStateString);

            if (currentState == goalState) {
                return new std::list<std::string>(currentNode.path);
            }

            std::vector<std::string> possibleMoves = getPossibleMoves(currentState);
            for (const auto& move : possibleMoves) {
                State newState = move(currentState, move);
                std::string newStateString = stateToString(newState);
                if (closedList.find(newStateString) == closedList.end()) {
                    std::list<std::string> newPath = currentNode.path;
                    newPath.push_back(move);
                    openList.push(Node(newState, newPath));
                }
            }
        }

        return nullptr;
    }

private:
    std::string stateToString(const State& state) {
        std::string s;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                s += ('0' + state[i][j]);
            }
        }
        return s;
    }
};