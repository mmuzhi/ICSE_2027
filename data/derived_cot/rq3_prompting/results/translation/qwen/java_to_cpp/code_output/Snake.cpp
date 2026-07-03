#include <vector>
#include <random>
#include <cstdint>
#include <algorithm>
#include <optional>
#include <functional>

struct Position {
    int x;
    int y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

class Snake {
private:
    int length;
    int screen_width;
    int screen_height;
    int block_size;
    std::vector<Position> positions;
    int score;
    Position food_position;
    std::mt19937 random_engine;

    void generate_food() {
        while (true) {
            int x = random_engine() % (screen_width / block_size) * block_size;
            int y = random_engine() % (screen_height / block_size) * block_size;
            Position new_food(x, y);
            if (!std::find(positions.begin(), positions.end(), new_food) {
                food_position = new_food;
                break;
            }
        }
    }

public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, const Position& foodPosition)
        : screen_width(SCREEN_WIDTH), screen_height(SCREEN_HEIGHT), block_size(BLOCK_SIZE) {
        length = 1;
        positions = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}};
        score = 0;
        food_position = foodPosition;
        std::random_device rd;
        random_engine.seed(rd());
    }

    void move(const Position& direction) {
        Position cur = positions[0];
        int x = direction.x;
        int y = direction.y;

        int newX = (cur.x + x * block_size) % screen_width;
        int newY = (cur.y + y * block_size) % screen_height;
        Position newPosition(newX, newY);

        if (newPosition == food_position) {
            eatFood();
        }

        if (positions.size() > 2) {
            auto it = std::find(positions.begin() + 2, positions.end(), newPosition);
            if (it != positions.end()) {
                reset();
                return;
            }
        }

        positions.insert(positions.begin(), newPosition);
        if (positions.size() > length) {
            positions.pop_back();
        }
    }

    void eatFood() {
        length++;
        score += 100;
        generate_food();
    }

    void reset() {
        length = 1;
        positions.clear();
        positions = {{screen_width / 2, screen_height / 2}};
        score = 0;
        generate_food();
    }

    int getLength() const {
        return length;
    }

    std::vector<Position> getPositions() const {
        return positions;
    }

    int getScore() const {
        return score;
    }

    Position getFoodPosition() const {
        return food_position;
    }
};