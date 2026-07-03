#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <any>

class Order {
public:
    std::vector<std::map<std::string, std::any>> menu;
    std::vector<std::map<std::string, std::any>> selectedDishes;
    std::unordered_map<std::string, double> sales;

    Order() = default;

    bool addDish(const std::map<std::string, std::any>& dish) {
        if (dish.find("dish") == dish.end() ||
            dish.find("price") == dish.end() ||
            dish.find("count") == dish.end()) {
            return false;
        }

        for (auto& menuDish : menu) {
            if (std::any_cast<std::string>(dish.at("dish")) ==
                std::any_cast<std::string>(menuDish.at("dish"))) {
                int dishCount = std::any_cast<int>(dish.at("count"));
                int menuDishCount = std::any_cast<int>(menuDish.at("count"));

                if (menuDishCount < dishCount) {
                    return false;
                } else {
                    menuDish["count"] = menuDishCount - dishCount;
                    selectedDishes.push_back(dish);
                    return true;
                }
            }
        }
        return false;
    }

    double calculateTotal() {
        double total = 0;
        for (auto& dish : selectedDishes) {
            std::string dishName = std::any_cast<std::string>(dish.at("dish"));
            double price = std::any_cast<double>(dish.at("price"));
            int count = std::any_cast<int>(dish.at("count"));
            double sale = 1.0;
            auto it = sales.find(dishName);
            if (it != sales.end()) {
                sale = it->second;
            }
            total += price * count * sale;
        }
        return total;
    }

    std::any checkout() {
        if (selectedDishes.empty()) {
            return false;
        }
        double total = calculateTotal();
        selectedDishes.clear();
        return total;
    }
};