#include <vector>
#include <utility> // for std::pair
#include <cstdlib> // for rand()
#include <ctime>    // for srand()

class Snake {
public:
    // Constructor
    Snake(int SCREEN_WIDTH, int SCREEN_HEIGHT, int BLOCK_SIZE, 
          int food_x, int food_y) {
        length = 1;
        this->SCREEN_WIDTH = SCREEN_WIDTH;
        this->SCREEN_HEIGHT = SCREEN_HEIGHT;
        this->BLOCK_SIZE = BLOCK_SIZE;
        positions.push_back(std::make_pair(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0));
        score = 0;
        food_position = std::make_pair(food_x, food_y);
    }

    // Move the snake in the specified direction
    void move(int dx, int dy) {
        double cur_x = positions[0].first;
        double cur_y = positions[0].second;
        double new_x = ((cur_x + dx * BLOCK_SIZE) % SCREEN_WIDTH + SCREEN_WIDTH) % SCREEN_WIDTH;
        double new_y = ((cur_y + dy * BLOCK_SIZE) % SCREEN_HEIGHT + SCREEN_HEIGHT) % SCREEN_HEIGHT;

        if (new_x == food_position.first && new_y == food_position.second) {
            eat_food();
        }

        if (positions.size() > 2) {
            if (positions[0].first == new_x && positions[0].second == new_y) {
                // Check if the new head position is in the body
                for (int i = 2; i < positions.size(); i++) {
                    if (positions[i].first == new_x && positions[i].second == new_y) {
                        reset();
                        return;
                    }
                }
            }
        }

        positions.insert(positions.begin(), std::make_pair(new_x, new_y));
        if (positions.size() > length) {
            positions.pop_back();
        }
    }

    // Randomly generate a new food position not on the snake
    void random_food_position() {
        int grid_width = static_cast<int>(SCREEN_WIDTH / BLOCK_SIZE);
        int grid_height = static_cast<int>(SCREEN_HEIGHT / BLOCK_SIZE);
        
        while (true) {
            int x = rand() % grid_width;
            int y = rand() % grid_height;
            double food_x = x * BLOCK_SIZE;
            double food_y = y * BLOCK_SIZE;
            
            bool is_on_snake = false;
            for (const auto& pos : positions) {
                if (pos.first == food_x && pos.second == food_y) {
                    is_on_snake = true;
                    break;
                }
            }
            
            if (!is_on_snake) {
                food_position = std::make_pair(food_x, food_y);
                break;
            }
        }
    }

    // Reset the snake to its initial state
    void reset() {
        length = 1;
        positions.clear();
        positions.push_back(std::make_pair(SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0));
        score = 0;
        random_food_position();
    }

    // Increase snake length and score
    void eat_food() {
        length++;
        score += 100;
        random_food_position();
    }

private:
    int length;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int BLOCK_SIZE;
    std::vector<std::pair<double, double>> positions;
    int score;
    std::pair<double, double> food_position;
};