#include <iostream>
#include <unordered_map>
#include <string>

struct Item {
    float price;
    int quantity;
};

class VendingMachine {
private:
    std::unordered_map<std::string, Item> inventory;
    float balance;

public:
    VendingMachine() : balance(0.0) {}

    bool add_item(const std::string& item_name, float price, int quantity) {
        if (!restock_item(item_name, quantity)) {
            inventory[item_name] = {price, quantity};
            return true;
        }
        return false;
    }

    float insert_coin(float amount) {
        balance += amount;
        return balance;
    }

    bool purchase_item(const std::string& item_name) {
        if (inventory.find(item_name) == inventory.end()) {
            return false;
        }

        Item& item = inventory[item_name];
        if (item.quantity <= 0) {
            return false;
        }

        if (balance < item.price) {
            return false;
        }

        balance -= item.price;
        item.quantity--;
        return true;
    }

    bool restock_item(const std::string& item_name, int quantity) {
        if (inventory.find(item_name) == inventory.end()) {
            return false;
        }
        inventory[item_name].quantity += quantity;
        return true;
    }

    std::string display_items() {
        if (inventory.empty()) {
            return "False";
        }

        std::string result;
        for (const auto& entry : inventory) {
            const std::string& name = entry.first;
            const Item& item = entry.second;
            result += name + " - $" + std::to_string(item.price) + " [" + std::to_string(item.quantity) + "]\n";
        }
        return result;
    }
};