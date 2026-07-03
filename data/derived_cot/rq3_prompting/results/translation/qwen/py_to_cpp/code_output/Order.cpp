#include <vector>
#include <unordered_map>
#include <string>

struct Dish {
    std::string name;
    double price;
    int count;
};

class Order {
private:
    std::vector<Dish> menu;
    std::vector<Dish> selected_dishes;
    std::unordered_map<std::string, double> sales;

public:
    Order() {}

    bool add_dish(Dish dish) {
        for (auto& menu_dish : menu) {
            if (dish.name == menu_dish.name) {
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
            total += dish.price * dish.count * sales[dish.name];
        }
        return total;
    }

    double checkout() {
        if (selected_dishes.empty()) {
            return -1.0;
        }
        double total = calculate_total();
        selected_dishes.clear();
        return total;
    }
};