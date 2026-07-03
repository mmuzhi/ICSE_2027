#include <string>
#include <unordered_map>
#include <variant>
#include <sstream>
#include <vector>

struct ItemInfo {
    double price;
    int quantity;
};

class VendingMachine {
private:
    std::unordered_map<std::string, ItemInfo> inventory;
    double balance;

public:
    VendingMachine() : inventory(), balance(0.0) {}

    void add_item(const std::string& item_name, double price, int quantity) {
        if (!restock_item(item_name, quantity)) {
            inventory[item_name] = {price, quantity};
        }
    }

    double insert_coin(double amount) {
        balance += amount;
        return balance;
    }

    std::variant<double, bool> purchase_item(const std::string& item_name) {
        auto it = inventory.find(item_name);
        if (it != inventory.end()) {
            if (it->second.quantity > 0 && balance >= it->second.price) {
                balance -= it->second.price;
                it->second.quantity -= 1;
                return balance;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool restock_item(const std::string& item_name, int quantity) {
        auto it = inventory.find(item_name);
        if (it != inventory.end()) {
            it->second.quantity += quantity;
            return true;
        } else {
            return false;
        }
    }

    std::variant<std::string, bool> display_items() {
        if (inventory.empty()) {
            return false;
        } else {
            std::vector<std::string> items;
            for (const auto& [item_name, item_info] : inventory) {
                std::ostringstream oss;
                oss << item_name << " - $" << item_info.price << " [" << item_info.quantity << "]";
                items.push_back(oss.str());
            }
            std::string result;
            for (size_t i = 0; i < items.size(); ++i) {
                if (i > 0) result += "\n";
                result += items[i];
            }
            return result;
        }
    }
};