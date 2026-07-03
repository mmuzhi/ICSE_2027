#include <vector>
#include <random>
#include <algorithm>

class Snake {
public:
    class Position {
    public:
        Position(int x, int y) : x(x), y(y) {}
        int getX() const { return x; }
        int getY() const { return y; }
        bool operator==(const Position& other) const {
            return x == other.x && y == other.y;
        }
    private:
        int x, y;
    };

    Snake(int screen_width, int screen_height, int block_size, Position foodPos)
        : SCREEN_WIDTH(screen_width),
          SCREEN_HEIGHT(screen_height),
          BLOCK_SIZE(block_size),
          foodPosition(foodPos),
          gen(std::random_device{}()),
          widthBlocks(screen_width / block_size),
          heightBlocks(screen_height / block_size),
          distribX(0, widthBlocks - 1),
          distribY(0, heightBlocks - 1)
    {
        length = 1;
        positions.push_back(Position(screen_width / 2, screen_height / 2));
        score = 0;
    }

    void move(Position direction) {
        Position cur = positions[0];
        int x = direction.getX();
        int y = direction.getY();

        int newX = (cur.getX() + (x * BLOCK_SIZE)) % SCREEN_WIDTH;
        int newY = (cur.getY() + (y * BLOCK_SIZE)) % SCREEN_HEIGHT;
        if (newX < 0) newX += SCREEN_WIDTH;
        if (newY < 0) newY += SCREEN_HEIGHT;
        Position newPosition(newX, newY);

        if (newPosition == foodPosition) {
            eat_food();
        }

        if (positions.size() > 2) {
            auto begin = positions.begin() + 2;
            auto end = positions.end();
            if (std::find(begin, end, newPosition) != end) {
                reset();
                return;
            }
        }

        positions.insert(positions.begin(), newPosition);
        if (positions.size() > length) {
            positions.pop_back();
        }
    }

    void random_food_position() {
        do {
            int x = distribX(gen) * BLOCK_SIZE;
            int y = distribY(gen) * BLOCK_SIZE;
            foodPosition = Position(x, y);
        } while (std::find(positions.begin(), positions.end(), foodPosition) != positions.end());
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

    Position getFoodPosition() const {
        return foodPosition;
    }

private:
    int length;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const int BLOCK_SIZE;
    std::vector<Position> positions;
    int score;
    Position foodPosition;
    std::mt19937 gen;
    int widthBlocks;
    int heightBlocks;
    std::uniform_int_distribution<int> distribX;
    std::uniform_int_distribution<int> distribY;
};