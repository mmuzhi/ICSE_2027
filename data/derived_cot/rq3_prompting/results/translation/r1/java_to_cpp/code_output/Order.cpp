#include <vector>
#include <unordered_map>
#include <string>
#include <any>
#include <memory>
#include <stdexcept>

class Order {
public:
    std::vector<std::shared_ptr<std::unordered_map<std::string, std::any>>> menu;
    std::vector<std::shared_ptr<std::unordered_map<std::string, std::any>>> selectedDishes;
    std::unordered_map<std::string, double> sales;

    Order() {}

    bool addDish(std::shared_ptr<std::unordered_map<std::string, std::any>> dish) {
        if (!dish ||
            dish->find("dish") == dish->end() ||
            dish->find("price") == dish->end() ||
            dish->find("count") == dish->end()) {
            return false;
        }
        std::string dishName = std::any_cast<std::string>((*dish)["dish"]);
        int dishCount = std::any_cast<int>((*dish)["count"]);

        for (auto& menuDishPtr : menu) {
            auto& menuDish = *menuDishPtr;
            if (menuDish.find("dish") != menuDish.end() &&
                std::any_cast<std::string>(menuDish["dish"]) == dishName) {
                int menuCount = std::any_cast<int>(menuDish["count"]);
                if (menuCount < dishCount) {
                    return false;
                } else {
                    menuDish["count"] = menuCount - dishCount;
                    selectedDishes.push_back(dish);
                    return true;
                }
            }
        }
        return false;
    }

    double calculateTotal() {
        double total = 0.0;
        for (const auto& dishPtr : selectedDishes) {
            auto& dish = *dishPtr;
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
            return std::any(false);
        }
        double total = calculateTotal();
        selectedDishes.clear();
        return std::any(total);
    }
};