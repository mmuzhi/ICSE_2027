#include <string>
#include <unordered_map>
#include <variant>
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
            inventory[item_name] = Item{price, quantity};
        }
    }

    double insert_coin(double amount) {
        balance += amount;
        return balance;
    }

    std::variant<double, bool> purchase_item(const std::string& item_name) {
        auto it = inventory.find(item_name);
        if (it != inventory.end()) {
            Item& item = it->second;
            if (item.quantity > 0 && balance >= item.price) {
                balance -= item.price;
                item.quantity -= 1;
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

    std::variant<bool, std::string> display_items() {
        if (inventory.empty()) {
            return false;
        } else {
            std::string result = "";
            bool first = true;
            
            for (const auto& pair : inventory) {
                if (!first) {
                    result += "\n";
                }
                first = false;
                
                // Format the price to match Python's f-string behavior
                std::ostringstream oss;
                oss << pair.second.price;
                std::string price_str = oss.str();
                
                // If there is no decimal point (e.g., "1"), append ".0" to match Python's "1.0"
                if (price_str.find('.') == std::string::npos && price_str.find('e') == std::string::npos) {
                    price_str += ".0";
                }
                
                result += pair.first + " - $" + price_str + " [" + std::to_string(pair.second.quantity) + "]";
            }
            return result;
        }
    }
};