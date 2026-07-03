#include <vector>
#include <string>
#include <unordered_map>
#include <optional>
#include <stdexcept>

struct Dish {
    std::string dish;
    double price;
    int count;
};

class Order {
public:
    Order() = default;

    bool add_dish(const Dish& dish) {
        bool found = false;
        for (auto& menu_dish : menu) {
            if (menu_dish.dish == dish.dish) {
                found = true;
                if (menu_dish.count < dish.count) {
                    return false;
                }
                menu_dish.count -= dish.count;
                break;
            }
        }
        // If dish was not found, or found and decremented, we add it to selected_dishes.
        selected_dishes.push_back(dish);
        return true;
    }

    double calculate_total() {
        double total = 0.0;
        for (const auto& dish : selected_dishes) {
            total += dish.price * dish.count * sales.at(dish.dish);
        }
        return total;
    }

    std::optional<double> checkout() {
        if (selected_dishes.empty()) {
            return std::nullopt;
        }
        double total = calculate_total();
        selected_dishes.clear();
        return total;
    }

    std::vector<Dish> menu;
    std::vector<Dish> selected_dishes;
    std::unordered_map<std::string, double> sales;
};