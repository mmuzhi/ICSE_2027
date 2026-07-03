#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <variant>
#include <utility>

class VendingMachine {
public:
    struct Product {
        double price;
        int quantity;

        Product() : price(0.0), quantity(0) {}
        Product(double price, int quantity) : price(price), quantity(quantity) {}
    };

    VendingMachine() : balance(0.0) {}

    void addItem(const std::string& itemName, double price, int quantity) {
        if (!restockItem(itemName, quantity)) {
            invMap[itemName] = Product(price, quantity);
            invOrder.push_back(itemName);
        }
    }

    double insertCoin(double amount) {
        balance += amount;
        return balance;
    }

    std::variant<double, bool> purchaseItem(const std::string& itemName) {
        auto it = invMap.find(itemName);
        if (it != invMap.end()) {
            Product& item = it->second;
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

    bool restockItem(const std::string& itemName, int quantity) {
        auto it = invMap.find(itemName);
        if (it != invMap.end()) {
            it->second.quantity += quantity;
            return true;
        }
        return false;
    }

    std::variant<std::string, bool> displayItems() const {
        if (invMap.empty()) {
            return false;
        }
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        for (const auto& key : invOrder) {
            const Product& item = invMap.at(key);
            oss << key << " - $" << item.price << " [" << item.quantity << "]\n";
        }
        std::string result = oss.str();
        if (!result.empty()) {
            result.pop_back(); // remove trailing newline to match Java's trim()
        }
        return result;
    }

    std::map<std::string, Product>& getInventory() {
        return invMap;
    }

    void setInventory(const std::map<std::string, Product>& inventory) {
        invMap = inventory;
        invOrder.clear();
        for (const auto& pair : inventory) {
            invOrder.push_back(pair.first);
        }
    }

    double getBalance() const {
        return balance;
    }

    void setBalance(double b) {
        balance = b;
    }

private:
    std::map<std::string, Product> invMap;   // for O(log n) lookup
    std::vector<std::string> invOrder;       // insertion order
    double balance;
};