#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <optional>

class Order {
private:
    std::vector<std::unordered_map<std::string, std::any>> menu;
    std::vector<std::unordered_map<std::string, std::any>> selectedDishes;
    std::unordered_map<std::string, double> sales;

public:
    Order() = default;

    bool addDish(std::unordered_map<std::string, std::any> dish) {
        if (dish.empty() || !dish.contains("dish") || !dish.contains("price") || !dish.contains("count")) {
            return false;
        }

        for (auto& menuDish : menu) {
            if (std::any_cast<std::string>(dish["dish"]) == std::any_cast<std::string>(menuDish["dish"])) {
                int dishCount = std::any_cast<int>(dish["count"]);
                int menuDishCount = std::any_cast<int>(menuDish["count"]);

                if (menuDishCount < dishCount) {
                    return false;
                }

                menuDish["count"] = menuDishCount - dishCount;
                selectedDishes.push_back(dish);
                return true;
            }
        }
        return false;
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& dish : selectedDishes) {
            std::string dishName = std::any_cast<std::string>(dish.at("dish"));
            double price = std::any_cast<double>(dish.at("price"));
            int count = std::any_cast<int>(dish.at("count"));
            double sale = sales.at(dishName);

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