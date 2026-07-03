#include <vector>
#include <random>

class Position {
public:
    int x, y;

    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Snake {
private:
    int length;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const int BLOCK_SIZE;
    std::vector<Position> positions;
    int score;
    Position foodPosition;

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> distX;
    std::uniform_int_distribution<int> distY;

    Position getRandomPosition() {
        return Position(distX(gen), distY(gen));
    }

public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, const Position& foodPosition) : 
        SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), BLOCK_SIZE(BLOCK_SIZE),
        length(1), score(0), foodPosition(foodPosition),
        gen(rd()), distX(0, SCREEN_WIDTH / BLOCK_SIZE), distY(0, SCREEN_HEIGHT / BLOCK_SIZE) {
        positions.push_back(Position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    }

    void move(const Position& direction) {
        Position cur = positions[0];
        int x = direction.x;
        int y = direction.y;

        int newX = (cur.x + (x * BLOCK_SIZE)) % SCREEN_WIDTH;
        int newY = (cur.y + (y * BLOCK_SIZE)) % SCREEN_HEIGHT;

        Position newPosition(newX, newY);

        if (newPosition == foodPosition) {
            eat_food();
        }

        if (positions.size() > 2) {
            bool collision = false;
            for (size_t i = 2; i < positions.size(); i++) {
                if (positions[i] == newPosition) {
                    collision = true;
                    break;
                }
            }
            if (collision) {
                reset();
            } else {
                positions.insert(positions.begin(), newPosition);
                if (positions.size() > length) {
                    positions.pop_back();
                }
            }
        } else {
            positions.insert(positions.begin(), newPosition);
            if (positions.size() > length) {
                positions.pop_back();
            }
        }
    }

    void random_food_position() {
        Position candidate;
        do {
            candidate = getRandomPosition() * BLOCK_SIZE;
        } while (std::find(positions.begin(), positions.end(), candidate) != positions.end());
        foodPosition = candidate;
    }

    void reset() {
        length = 1;
        positions.clear();
        positions.push_back(Position(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
        score = 0;
        random_food_position();
    }

    void eat_food() {
        length++;
        score += 100;
        random_food_position();
    }

    int get_length() const {
        return length;
    }

    const std::vector<Position>& getPositions() const {
        return positions;
    }

    int get_score() const {
        return score;
    }

    const Position& getFoodPosition() const {
        return foodPosition;
    }
};