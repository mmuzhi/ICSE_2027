#include <iostream>
#include <unordered_map>
#include <string>
#include <variant>

struct Item {
    double price;
    int quantity;
};

class VendingMachine {
private:
    std::unordered_map<std::string, Item> inventory;
    double balance;

public:
    VendingMachine() : balance(0) {}

    void add_item(const std::string& item_name, double price, int quantity) {
        if (!restock_item(item_name, quantity)) {
            inventory[item_name] = {price, quantity};
        }
    }

    double insert_coin(double amount) {
        balance += amount;
        return balance;
    }

    bool restock_item(const std::string& item_name, int quantity) {
        if (inventory.find(item_name) != inventory.end()) {
            inventory[item_name].quantity += quantity;
            return true;
        }
        return false;
    }

    std::variant<double, bool> purchase_item(const std::string& item_name) {
        if (inventory.find(item_name) != inventory.end()) {
            Item& item = inventory[item_name];
            if (item.quantity > 0 && balance >= item.price) {
                balance -= item.price;
                item.quantity -= 1;
                return balance;
            }
        }
        return false;
    }

    std::variant<bool, std::string> display_items() {
        if (inventory.empty()) {
            return false;
        }
        std::string result;
        for (const auto& [name, item] : inventory) {
            if (!result.empty()) {
                result += "\n";
            }
            result += name + " - $" + std::to_string(item.price) + " [" + std::to_string(item.quantity) + "]";
        }
        return result;
    }
};