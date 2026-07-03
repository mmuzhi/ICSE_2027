#pragma once
#include <string>
#include <vector>
#include <variant>
#include <algorithm>
#include <cstdio>

class VendingMachine {
public:
    class Product {
    private:
        double price;
        int quantity;

    public:
        Product(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const { return price; }
        void setPrice(double p) { price = p; }
        int getQuantity() const { return quantity; }
        void setQuantity(int q) { quantity = q; }
    };

    using Inventory = std::vector<std::pair<std::string, Product>>;

private:
    Inventory inventory;
    double balance;

    Inventory::iterator findItem(const std::string& itemName) {
        return std::find_if(inventory.begin(), inventory.end(),
            [&](const auto& p) { return p.first == itemName; });
    }

    Inventory::const_iterator findItem(const std::string& itemName) const {
        return std::find_if(inventory.begin(), inventory.end(),
            [&](const auto& p) { return p.first == itemName; });
    }

public:
    VendingMachine() : balance(0) {}

    void addItem(const std::string& itemName, double price, int quantity) {
        if (!restockItem(itemName, quantity)) {
            inventory.emplace_back(itemName, Product(price, quantity));
        }
    }

    double insertCoin(double amount) {
        balance += amount;
        return balance;
    }

    std::variant<double, bool> purchaseItem(const std::string& itemName) {
        auto it = findItem(itemName);
        if (it != inventory.end()) {
            Product& item = it->second;
            if (item.getQuantity() > 0 && balance >= item.getPrice()) {
                balance -= item.getPrice();
                item.setQuantity(item.getQuantity() - 1);
                return balance;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool restockItem(const std::string& itemName, int quantity) {
        auto it = findItem(itemName);
        if (it != inventory.end()) {
            Product& item = it->second;
            item.setQuantity(item.getQuantity() + quantity);
            return true;
        } else {
            return false;
        }
    }

    std::variant<std::string, bool> displayItems() {
        if (inventory.empty()) {
            return false;
        } else {
            std::string items;
            for (const auto& entry : inventory) {
                const Product& item = entry.second;
                char buf[256];
                std::snprintf(buf, sizeof(buf), "%s - $%.2f [%d]\n",
                    entry.first.c_str(), item.getPrice(), item.getQuantity());
                items += buf;
            }
            while (!items.empty() && items.back() == '\n')
                items.pop_back();
            return items;
        }
    }

    Inventory& getInventory() { return inventory; }
    void setInventory(const Inventory& inv) { inventory = inv; }

    double getBalance() const { return balance; }
    void setBalance(double b) { balance = b; }
};