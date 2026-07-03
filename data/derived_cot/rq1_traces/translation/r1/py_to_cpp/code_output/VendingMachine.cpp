#include <unordered_map>
#include <string>
#include <optional>
#include <sstream>

class VendingMachine {
private:
    struct Item {
        double price;
        int quantity;
    };
    std::unordered_map<std::string, Item> inventory;
    double balance;

public:
    VendingMachine() : balance(0.0) {}

    void add_item(const std::string& item_name, double price, int quantity) {
        if (!restock_item(item_name, quantity)) {
            inventory[item_name] = {price, quantity};
        }
    }

    double insert_coin(double amount) {
        balance += amount;
        return balance;
    }

    std::optional<double> purchase_item(const std::string& item_name) {
        auto it = inventory.find(item_name);
        if (it != inventory.end()) {
            Item& item = it->second;
            if (item.quantity > 0 && balance >= item.price) {
                balance -= item.price;
                item.quantity--;
                return balance;
            }
        }
        return std::nullopt;
    }

    bool restock_item(const std::string& item_name, int quantity) {
        auto it = inventory.find(item_name);
        if (it != inventory.end()) {
            it->second.quantity += quantity;
            return true;
        }
        return false;
    }

    std::optional<std::string> display_items() {
        if (inventory.empty()) {
            return std::nullopt;
        }
        std::ostringstream oss;
        bool first = true;
        for (const auto& pair : inventory) {
            if (!first) {
                oss << '\n';
            }
            first = false;
            oss << pair.first << " - $" << pair.second.price << " [" << pair.second.quantity << "]";
        }
        return oss.str();
    }
};