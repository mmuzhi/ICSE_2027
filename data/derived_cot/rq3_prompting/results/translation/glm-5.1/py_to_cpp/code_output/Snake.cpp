#include <vector>
#include <utility>
#include <random>
#include <algorithm>

class Snake {
public:
    int length;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BLOCK_SIZE;
    std::vector<std::pair<int, int>> positions;
    int score;
    std::pair<int, int> food_position;

private:
    std::mt19937 rng;

    static int mod(int a, int b) {
        return ((a % b) + b) % b;
    }

public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, std::pair<int, int> food_position)
        : length(1),
          SCREEN_WIDTH(SCREEN_WIDTH),
          SCREEN_HEIGHT(SCREEN_HEIGHT),
          BLOCK_SIZE(BLOCK_SIZE),
          positions({{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}}),
          score(0),
          food_position(food_position),
          rng(std::random_device{}()) {}

    void move(std::pair<int, int> direction) {
        auto cur = positions[0];
        int x = direction.first;
        int y = direction.second;

        auto new_pos = std::make_pair(
            mod(cur.first + x * BLOCK_SIZE, SCREEN_WIDTH),
            mod(cur.second + y * BLOCK_SIZE, SCREEN_HEIGHT)
        );

        if (new_pos == food_position) {
            eat_food();
        }

        if (positions.size() > 2) {
            bool found = false;
            for (size_t i = 2; i < positions.size(); ++i) {
                if (positions[i] == new_pos) {
                    found = true;
                    break;
                }
            }
            if (found) {
                reset();
                return;
            }
        }

        positions.insert(positions.begin(), new_pos);
        if (static_cast<int>(positions.size()) > length) {
            positions.pop_back();
        }
    }

    void random_food_position() {
        std::uniform_int_distribution<int> dist_x(0, SCREEN_WIDTH / BLOCK_SIZE - 1);
        std::uniform_int_distribution<int> dist_y(0, SCREEN_HEIGHT / BLOCK_SIZE - 1);
        while (std::find(positions.begin(), positions.end(), food_position) != positions.end()) {
            food_position = std::make_pair(dist_x(rng) * BLOCK_SIZE, dist_y(rng) * BLOCK_SIZE);
        }
    }

    void reset() {
        length = 1;
        positions = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}};
        score = 0;
        random_food_position();
    }

    void eat_food() {
        length += 1;
        score += 100;
        random_food_position();
    }
};