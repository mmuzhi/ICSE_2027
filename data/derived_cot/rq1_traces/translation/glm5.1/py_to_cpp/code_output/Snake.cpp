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
    std::mt19937 rng{std::random_device{}()};

    // Python-style modulo (always non-negative when divisor > 0)
    static int mod(int a, int b) {
        return ((a % b) + b) % b;
    }

public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, std::pair<int, int> food_position)
        : length(1),
          SCREEN_WIDTH(SCREEN_WIDTH),
          SCREEN_HEIGHT(SCREEN_HEIGHT),
          BLOCK_SIZE(BLOCK_SIZE),
          positions{{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}},
          score(0),
          food_position(food_position) {}

    void move(std::pair<int, int> direction) {
        auto cur = positions[0];
        int x = direction.first;
        int y = direction.second;

        std::pair<int, int> new_pos = {
            mod(cur.first + x * BLOCK_SIZE, SCREEN_WIDTH),
            mod(cur.second + y * BLOCK_SIZE, SCREEN_HEIGHT)
        };

        if (new_pos == food_position) {
            eat_food();
        }

        if (positions.size() > 2) {
            bool collision = false;
            for (size_t i = 2; i < positions.size(); ++i) {
                if (new_pos == positions[i]) {
                    collision = true;
                    break;
                }
            }
            if (collision) {
                reset();
                return;
            }
        }

        positions.insert(positions.begin(), new_pos);
        if (positions.size() > static_cast<size_t>(length)) {
            positions.pop_back();
        }
    }

    void random_food_position() {
        while (std::find(positions.begin(), positions.end(), food_position) != positions.end()) {
            int max_x = SCREEN_WIDTH / BLOCK_SIZE - 1;
            int max_y = SCREEN_HEIGHT / BLOCK_SIZE - 1;
            std::uniform_int_distribution<int> dist_x(0, max_x);
            std::uniform_int_distribution<int> dist_y(0, max_y);
            food_position = {dist_x(rng) * BLOCK_SIZE, dist_y(rng) * BLOCK_SIZE};
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