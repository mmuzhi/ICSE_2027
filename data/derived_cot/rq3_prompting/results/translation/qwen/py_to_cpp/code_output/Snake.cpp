#include <vector>
#include <deque>
#include <utility> // for std::pair
#include <cstdlib> // for rand()
#include <ctime>   // for srand()

class Snake {
private:
    int length;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BLOCK_SIZE;
    std::deque<std::pair<int, int>> positions;
    int score;
    std::pair<int, int> food_position;

public:
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, const std::pair<int, int>& food_position) {
        this->SCREEN_WIDTH = SCREEN_WIDTH;
        this->SCREEN_HEIGHT = SCREEN_HEIGHT;
        this->BLOCK_SIZE = BLOCK_SIZE;
        this->positions = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}};
        this->score = 0;
        this->food_position = food_position;
    }

    void move(int dx, int dy) {
        auto cur = positions.front();
        int new_x = (cur.first + dx * BLOCK_SIZE) % SCREEN_WIDTH;
        int new_y = (cur.second + dy * BLOCK_SIZE) % SCREEN_HEIGHT;
        auto new_head = std::make_pair(new_x, new_y);

        if (new_head == food_position) {
            eat_food();
            return;
        }

        if (positions.size() > 2) {
            for (auto it = positions.begin() + 1; it != positions.end(); ++it) {
                if (*it == new_head) {
                    reset();
                    return;
                }
            }
        }

        positions.insert(positions.begin(), new_head);
        if (positions.size() > length) {
            positions.pop_back();
        }
    }

    void random_food_position() {
        while (true) {
            int x = (rand() % (SCREEN_WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
            int y = (rand() % (SCREEN_HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
            auto new_pos = std::make_pair(x, y);
            if (new_pos != food_position && std::find(positions.begin(), positions.end(), new_pos) == positions.end()) {
                food_position = new_pos;
                break;
            }
        }
    }

    void reset() {
        length = 1;
        positions.clear();
        positions.push_back(std::make_pair(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
        score = 0;
        random_food_position();
    }

    void eat_food() {
        length++;
        score += 100;
        random_food_position();
    }
};

// Initialize random number generator
void init_random() {
    srand(time(nullptr));
}