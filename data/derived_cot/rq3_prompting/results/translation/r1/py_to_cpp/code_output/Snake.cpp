#include <vector>
#include <utility>
#include <random>
#include <cmath>
#include <cstddef>

class Snake {
public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE,
          std::pair<double, double> food_position)
        : length(1),
          SCREEN_WIDTH(SCREEN_WIDTH),
          SCREEN_HEIGHT(SCREEN_HEIGHT),
          BLOCK_SIZE(BLOCK_SIZE),
          positions({std::make_pair(static_cast<double>(SCREEN_WIDTH) / 2,
                                   static_cast<double>(SCREEN_HEIGHT) / 2)}),
          score(0),
          food_position(food_position)
    {}

    void move(std::pair<double, double> direction) {
        auto cur = positions[0];
        double newX = cur.first + direction.first * BLOCK_SIZE;
        double newY = cur.second + direction.second * BLOCK_SIZE;

        // Python-style modulo (always non-negative)
        newX = std::fmod(newX, static_cast<double>(SCREEN_WIDTH));
        if (newX < 0) newX += SCREEN_WIDTH;
        newY = std::fmod(newY, static_cast<double>(SCREEN_HEIGHT));
        if (newY < 0) newY += SCREEN_HEIGHT;

        // Check if food is eaten
        if (newX == food_position.first && newY == food_position.second) {
            eat_food();
        }

        // Check self-collision (skip first two elements, i.e. positions[2:])
        bool collision = false;
        if (positions.size() > 2) {
            for (auto it = positions.begin() + 2; it != positions.end(); ++it) {
                if (it->first == newX && it->second == newY) {
                    collision = true;
                    break;
                }
            }
        }

        if (collision) {
            reset();
        } else {
            positions.insert(positions.begin(), std::make_pair(newX, newY));
            if (positions.size() > static_cast<std::size_t>(length)) {
                positions.pop_back();
            }
        }
    }

    void random_food_position() {
        static std::mt19937 rng(std::random_device{}());
        int maxX = SCREEN_WIDTH / BLOCK_SIZE;
        int maxY = SCREEN_HEIGHT / BLOCK_SIZE;
        std::uniform_int_distribution<int> distX(0, maxX - 1);
        std::uniform_int_distribution<int> distY(0, maxY - 1);

        bool on_snake;
        do {
            food_position.first = distX(rng) * BLOCK_SIZE;
            food_position.second = distY(rng) * BLOCK_SIZE;
            on_snake = false;
            for (const auto& pos : positions) {
                if (pos.first == food_position.first &&
                    pos.second == food_position.second) {
                    on_snake = true;
                    break;
                }
            }
        } while (on_snake);
    }

    void reset() {
        length = 1;
        positions.clear();
        positions.push_back(std::make_pair(static_cast<double>(SCREEN_WIDTH) / 2,
                                           static_cast<double>(SCREEN_HEIGHT) / 2));
        score = 0;
        random_food_position();
    }

    void eat_food() {
        length += 1;
        score += 100;
        random_food_position();
    }

    // Accessors (for testing or extension)
    int get_length() const { return length; }
    int get_score() const { return score; }
    const std::vector<std::pair<double, double>>& get_positions() const {
        return positions;
    }
    std::pair<double, double> get_food_position() const {
        return food_position;
    }

private:
    int length;
    int SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE;
    std::vector<std::pair<double, double>> positions;
    int score;
    std::pair<double, double> food_position;
};