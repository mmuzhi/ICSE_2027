#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

struct Dish {
    std::string dish;
    double price;
    int count;
};

class Order {
public:
    std::vector<Dish> menu;
    std::vector<Dish> selected_dishes;
    std::unordered_map<std::string, double> sales;

    Order() = default;

    bool add_dish(const Dish& dish) {
        for (auto& menu_dish : menu) {
            if (dish.dish == menu_dish.dish) {
                if (menu_dish.count < dish.count) {
                    return false;
                } else {
                    menu_dish.count -= dish.count;
                    break;
                }
            }
        }
        selected_dishes.push_back(dish);
        return true;
    }

    double calculate_total() {
        double total = 0;
        for (const auto& dish : selected_dishes) {
            total += dish.price * dish.count * sales.at(dish.dish);
        }
        return total;
    }

    std::variant<double, bool> checkout() {
        if (selected_dishes.empty()) {
            return false;
        }
        double total = calculate_total();
        selected_dishes.clear();
        return total;
    }
};