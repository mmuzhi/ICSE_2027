#include <vector>
#include <random>
#include <algorithm>

class Snake {
public:
    class Position {
    public:
        Position(int x, int y) : x_(x), y_(y) {}
        int getX() const { return x_; }
        int getY() const { return y_; }
        bool operator==(const Position& other) const {
            return x_ == other.x_ && y_ == other.y_;
        }
    private:
        int x_;
        int y_;
    };

    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, Position foodPosition)
        : SCREEN_WIDTH_(SCREEN_WIDTH)
        , SCREEN_HEIGHT_(SCREEN_HEIGHT)
        , BLOCK_SIZE_(BLOCK_SIZE)
        , foodPosition_(foodPosition)
        , length_(1)
        , score_(0)
        , rng_(std::random_device{}())
    {
        positions_.emplace_back(SCREEN_WIDTH_ / 2, SCREEN_HEIGHT_ / 2);
    }

    void move(const Position& direction) {
        Position cur = positions_.front();
        int x = direction.getX();
        int y = direction.getY();

        int newX = (cur.getX() + (x * BLOCK_SIZE_)) % SCREEN_WIDTH_;
        int newY = (cur.getY() + (y * BLOCK_SIZE_)) % SCREEN_HEIGHT_;
        Position newPosition(newX, newY);

        if (newPosition == foodPosition_) {
            eatFood();
        }

        // Check collision with body (skip head)
        if (positions_.size() > 2) {
            auto it = std::find(positions_.begin() + 2, positions_.end(), newPosition);
            if (it != positions_.end()) {
                reset();
                return;
            }
        }

        positions_.insert(positions_.begin(), newPosition);
        if (positions_.size() > length_) {
            positions_.pop_back();
        }
    }

    void randomFoodPosition() {
        int maxX = SCREEN_WIDTH_ / BLOCK_SIZE_;
        int maxY = SCREEN_HEIGHT_ / BLOCK_SIZE_;
        std::uniform_int_distribution<int> distX(0, maxX - 1);
        std::uniform_int_distribution<int> distY(0, maxY - 1);

        do {
            int x = distX(rng_) * BLOCK_SIZE_;
            int y = distY(rng_) * BLOCK_SIZE_;
            foodPosition_ = Position(x, y);
        } while (std::find(positions_.begin(), positions_.end(), foodPosition_) != positions_.end());
    }

    void reset() {
        length_ = 1;
        positions_.clear();
        positions_.emplace_back(SCREEN_WIDTH_ / 2, SCREEN_HEIGHT_ / 2);
        score_ = 0;
        randomFoodPosition();
    }

    void eatFood() {
        length_++;
        score_ += 100;
        randomFoodPosition();
    }

    int getLength() const { return length_; }
    std::vector<Position>& getPositions() { return positions_; }
    const std::vector<Position>& getPositions() const { return positions_; }
    int getScore() const { return score_; }
    Position& getFoodPosition() { return foodPosition_; }
    const Position& getFoodPosition() const { return foodPosition_; }

private:
    int length_;
    const int SCREEN_WIDTH_;
    const int SCREEN_HEIGHT_;
    const int BLOCK_SIZE_;
    std::vector<Position> positions_;
    int score_;
    Position foodPosition_;
    std::mt19937 rng_;
};