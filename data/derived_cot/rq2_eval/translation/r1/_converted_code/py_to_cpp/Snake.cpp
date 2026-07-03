#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#include <random>

class Snake {
private:
    int length;
    double SCREEN_WIDTH;
    double SCREEN_HEIGHT;
    double BLOCK_SIZE;
    std::vector<std::pair<double, double>> positions;
    int score;
    std::pair<double, double> food_position;

    double wrap(double value, double modulus) {
        double mod = std::fmod(value, modulus);
        if (mod < 0) {
            mod += modulus;
        }
        return mod;
    }

public:
    Snake(double SCREEN_WIDTH, double SCREEN_HEIGHT, double BLOCK_SIZE, std::pair<double, double> food_position)
        : length(1), SCREEN_WIDTH(SCREEN_WIDTH), SCREEN_HEIGHT(SCREEN_HEIGHT), BLOCK_SIZE(BLOCK_SIZE),
          positions( { std::make_pair(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) } ),
          score(0), food_position(food_position) {}

    void move(std::pair<int, int> direction) {
        auto cur = positions[0];
        double x = direction.first * BLOCK_SIZE;
        double y = direction.second * BLOCK_SIZE;

        double new_x = wrap(cur.first + x, SCREEN_WIDTH);
        double new_y = wrap(cur.second + y, SCREEN_HEIGHT);
        std::pair<double, double> new_position = { new_x, new_y };

        if (new_position == food_position) {
            eat_food();
        }

        if (positions.size() > 2) {
            auto start = positions.begin() + 2;
            auto end = positions.end();
            if (std::find(start, end, new_position) != end) {
                reset();
                return;
            }
        }

        positions.insert(positions.begin(), new_position);
        if (positions.size() > length) {
            positions.pop_back();
        }
    }

    void random_food_position() {
        static std::mt19937 rng(std::random_device{}());

        int num_blocks_x = static_cast<int>(SCREEN_WIDTH / BLOCK_SIZE);
        int num_blocks_y = static_cast<int>(SCREEN_HEIGHT / BLOCK_SIZE);

        if (num_blocks_x <= 0 || num_blocks_y <= 0) {
            return;
        }

        std::uniform_int_distribution<int> dist_x(0, num_blocks_x - 1);
        std::uniform_int_distribution<int> dist_y(0, num_blocks_y - 1);

        while (true) {
            double food_x = dist_x(rng) * BLOCK_SIZE;
            double food_y = dist_y(rng) * BLOCK_SIZE;
            std::pair<double, double> new_food(food_x, food_y);

            if (std::find(positions.begin(), positions.end(), new_food) == positions.end()) {
                food_position = new_food;
                break;
            }
        }
    }

    void reset() {
        length = 1;
        positions = { std::make_pair(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) };
        score = 0;
        random_food_position();
    }

    void eat_food() {
        length += 1;
        score += 100;
        random_food_position();
    }
};