#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <optional>
#include <cmath>

class VendingMachine {
private:
    struct Item {
        double price;
        int quantity;
    };
    std::map<std::string, Item> inventory;
    double balance;

    // Helper to format a double like Python's str(price) when used in f-string
    static std::string format_price(double price) {
        std::ostringstream oss;
        // Use default formatting (equivalent to Python's str(float))
        oss << price;
        std::string s = oss.str();
        // Python always shows a decimal point if the float is an integer value (e.g., 1.0 -> "1.0")
        // C++ default omits trailing zero; check if the string contains no '.' and no 'e'
        if (s.find('.') == std::string::npos && s.find('e') == std::string::npos && s.find('E') == std::string::npos) {
            s += ".0";
        }
        return s;
    }

public:
    VendingMachine() : balance(0.0) {}

    void add_item(const std::string& item_name, double price, int quantity) {
        if (!restock_item(item_name, quantity)) {
            // Item not in inventory, add new entry
            inventory[item_name] = {price, quantity};
        }
        // If restock_item succeeded, quantity was already increased, price remains unchanged (same as Python)
    }

    double insert_coin(double amount) {
        balance += amount;
        return balance;
    }

    std::optional<double> purchase_item(const std::string& item_name) {
        auto it = inventory.find(item_name);
        if (it != inventory.end() && it->second.quantity > 0 && balance >= it->second.price) {
            balance -= it->second.price;
            it->second.quantity -= 1;
            return balance;
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
        for (const auto& [name, item] : inventory) {
            if (!first) {
                oss << "\n";
            }
            first = false;
            oss << name << " - $" << format_price(item.price) << " [" << item.quantity << "]";
        }
        return oss.str();
    }
};