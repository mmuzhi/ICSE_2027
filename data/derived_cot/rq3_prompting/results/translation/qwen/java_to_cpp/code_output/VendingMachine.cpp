#include <map>
#include <string>
#include <variant>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

class VendingMachine {
private:
    struct Product {
        double price;
        int quantity;

        Product(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const { return price; }
        void setPrice(double price) { this->price = price; }

        int getQuantity() const { return quantity; }
        void setQuantity(int quantity) { this->quantity = quantity; }
    };

    std::map<std::string, Product> inventory;
    double balance;

public:
    VendingMachine() : balance(0.0) {}

    void addItem(const std::string& itemName, double price, int quantity) {
        if (!restockItem(itemName, quantity)) {
            inventory[itemName] = Product(price, quantity);
        }
    }

    double insertCoin(double amount) {
        balance += amount;
        return balance;
    }

    std::variant<double, bool> purchaseItem(const std::string& itemName) {
        if (inventory.find(itemName) != inventory.end()) {
            Product& item = inventory[itemName];
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
        if (inventory.find(itemName) != inventory.end()) {
            Product& item = inventory[itemName];
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
            std::ostringstream oss;
            for (const auto& entry : inventory) {
                const auto& [name, item] = entry;
                oss << std::fixed << std::setprecision(2)
                    << name << " - $" << item.getPrice() << " [" << item.getQuantity() << "]\n";
            }
            std::string result = oss.str();
            // Trim leading/trailing whitespace
            auto start = result.find_first_not_of(" ");
            auto end = result.find_last_not_of(" ");
            if (start == std::string::npos) {
                return false; // empty string after trim
            }
            return result.substr(start, end - start + 1);
        }
    }

    // Accessor methods
    const std::map<std::string, Product>& getInventory() const {
        return inventory;
    }

    void setInventory(const std::map<std::string, Product>& inventory) {
        this->inventory = inventory;
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }
};