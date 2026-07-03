#include <map>
#include <string>
#include <utility>

class ShoppingCart {
private:
    // Stores item name -> {price, quantity}
    std::map<std::string, std::pair<double, int>> items;

public:
    ShoppingCart() = default;

    void add_item(const std::string& item, double price, int quantity = 1) {
        items[item] = {price, quantity};
    }

    void remove_item(const std::string& item, int quantity = 1) {
        auto it = items.find(item);
        if (it != items.end()) {
            it->second.second -= quantity;
        }
    }

    // Returns a mutable reference to the internal map to match Python's behavior
    std::map<std::string, std::pair<double, int>>& view_items() {
        return items;
    }

    double total_price() const {
        double total = 0.0;
        for (const auto& [name, info] : items) {
            total += info.second * info.first;  // quantity * price
        }
        return total;
    }
};