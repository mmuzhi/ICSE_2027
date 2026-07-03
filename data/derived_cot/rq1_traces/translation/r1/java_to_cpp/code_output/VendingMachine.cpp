#include <vector>
#include <string>
#include <variant>
#include <cstdio>

class VendingMachine {
public:
    class Product {
    private:
        double price;
        int quantity;

    public:
        Product(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const {
            return price;
        }

        void setPrice(double price) {
            this->price = price;
        }

        int getQuantity() const {
            return quantity;
        }

        void setQuantity(int quantity) {
            this->quantity = quantity;
        }
    };

    using InventoryVector = std::vector<std::pair<std::string, Product>>;
    using PurchaseResult = std::variant<double, bool>;
    using DisplayResult = std::variant<std::string, bool>;

private:
    InventoryVector inventory;
    double balance;

public:
    VendingMachine() : balance(0.0) {}

    void addItem(const std::string& itemName, double price, int quantity) {
        for (auto& item : inventory) {
            if (item.first == itemName) {
                item.second.setQuantity(item.second.getQuantity() + quantity);
                return;
            }
        }
        inventory.push_back(std::make_pair(itemName, Product(price, quantity)));
    }

    double insertCoin(double amount) {
        balance += amount;
        return balance;
    }

    PurchaseResult purchaseItem(const std::string& itemName) {
        for (auto& item : inventory) {
            if (item.first == itemName) {
                Product& product = item.second;
                if (product.getQuantity() > 0 && balance >= product.getPrice()) {
                    balance -= product.getPrice();
                    product.setQuantity(product.getQuantity() - 1);
                    return balance;
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    bool restockItem(const std::string& itemName, int quantity) {
        for (auto& item : inventory) {
            if (item.first == itemName) {
                Product& product = item.second;
                product.setQuantity(product.getQuantity() + quantity);
                return true;
            }
        }
        return false;
    }

    DisplayResult displayItems() {
        if (inventory.empty()) {
            return false;
        } else {
            std::string items;
            for (const auto& item : inventory) {
                char buffer[100];
                std::snprintf(buffer, sizeof(buffer), "%s - $%.2f [%d]",
                              item.first.c_str(), item.second.getPrice(), item.second.getQuantity());
                items += buffer;
                items += '\n';
            }
            if (!items.empty() && items.back() == '\n') {
                items.pop_back();
            }
            return items;
        }
    }

    InventoryVector getInventory() const {
        return inventory;
    }

    void setInventory(const InventoryVector& newInventory) {
        inventory = newInventory;
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double newBalance) {
        balance = newBalance;
    }
};