#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <iostream>

struct Dish {
    std::string name;
    double price;
    int count;
};

class Order {
private:
    std::vector<Dish> menu;
    std::vector<Dish> selectedDishes;
    std::unordered_map<std::string, double> sales;

public:
    Order() : menu(), selectedDishes(), sales() {}

    bool add_dish(const std::unordered_map<std::string, std::any>& dish) {
        if (dish.find("dish") == dish.end() || 
            dish.find("price") == dish.end() || 
            dish.find("count") == dish.end()) {
            return false;
        }

        Dish tempDish;
        try {
            tempDish.name = std::any_cast<std::string>(dish.at("dish"));
            tempDish.price = std::any_cast<double>(dish.at("price"));
            tempDish.count = std::any_cast<int>(dish.at("count"));
        } catch (const std::exception& e) {
            return false;
        }

        for (auto& menuDish : menu) {
            if (menuDish.name == tempDish.name) {
                if (menuDish.count < tempDish.count) {
                    return false;
                } else {
                    menuDish.count -= tempDish.count;
                    selectedDishes.push_back(tempDish);
                    return true;
                }
            }
        }
        return false;
    }

    double calculate_total() {
        double total = 0.0;
        for (const auto& dish : selectedDishes) {
            auto it = sales.find(dish.name);
            double sale = 1.0;
            if (it != sales.end()) {
                sale = it->second;
            }
            total += dish.price * dish.count * sale;
        }
        return total;
    }

    std::any checkout() {
        if (selectedDishes.empty()) {
            return false;
        }
        double total = calculate_total();
        selectedDishes.clear();
        return total;
    }
};