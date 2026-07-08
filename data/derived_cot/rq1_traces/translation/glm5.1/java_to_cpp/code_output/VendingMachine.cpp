#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <string>
#include <vector>
#include <utility>
#include <any>
#include <sstream>
#include <iomanip>

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

private:
    // LinkedHashMap preserves insertion order; vector of pairs replicates that
    std::vector<std::pair<std::string, Product>> inventory;
    double balance;

    int findItemIndex(const std::string& itemName) const {
        for (size_t i = 0; i < inventory.size(); i++) {
            if (inventory[i].first == itemName) {
                return static_cast<int>(i);
            }
        }
        return -1;
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

    std::any purchaseItem(const std::string& itemName) {
        int idx = findItemIndex(itemName);
        if (idx >= 0) {
            Product& item = inventory[idx].second;
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
        int idx = findItemIndex(itemName);
        if (idx >= 0) {
            Product& item = inventory[idx].second;
            item.setQuantity(item.getQuantity() + quantity);
            return true;
        } else {
            return false;
        }
    }

    std::any displayItems() {
        if (inventory.empty()) {
            return false;
        } else {
            std::ostringstream items;
            for (const auto& entry : inventory) {
                const Product& item = entry.second;
                items << entry.first << " - $"
                      << std::fixed << std::setprecision(2) << item.getPrice()
                      << " [" << item.getQuantity() << "]\n";
            }
            std::string result = items.str();
            // Replicate Java's trim() — only trailing '\n' exists here
            if (!result.empty() && result.back() == '\n') {
                result.pop_back();
            }
            return result;
        }
    }

    std::vector<std::pair<std::string, Product>>& getInventory() {
        return inventory;
    }

    void setInventory(const std::vector<std::pair<std::string, Product>>& inv) {
        inventory = inv;
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double b) {
        balance = b;
    }
};

#endif