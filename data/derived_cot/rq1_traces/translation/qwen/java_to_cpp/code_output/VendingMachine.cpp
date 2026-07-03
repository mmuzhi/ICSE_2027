#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <optional>

class VendingMachine;

class Product {
public:
    double price;
    int quantity;

    Product(double price, int quantity) : price(price), quantity(quantity) {}

    double getPrice() const { return price; }
    void setPrice(double price) { this->price = price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int quantity) { this->quantity = quantity; }
};

class VendingMachine {
private:
    std::shared_ptr<std::unordered_map<std::string, Product>> inventory;
    double balance;
    std::vector<std::string> insertionOrder;

    using PurchaseResult = std::variant<bool, double>;
    using DisplayResult = std::variant<bool, std::string>;

public:
    VendingMachine() : balance(0.0) {
        inventory = std::make_shared<std::unordered_map<std::string, Product>>();
    }

    void addItem(const std::string& itemName, double price, int quantity) {
        if (!restockItem(itemName, quantity)) {
            inventory->emplace(itemName, Product(price, quantity));
            insertionOrder.push_back(itemName);
        }
    }

    double insertCoin(double amount) {
        balance += amount;
        return balance;
    }

    PurchaseResult purchaseItem(const std::string& itemName) {
        auto it = inventory->find(itemName);
        if (it != inventory->end()) {
            Product& item = it->second;
            if (item.quantity > 0 && balance >= item.price) {
                balance -= item.price;
                item.quantity--;
                return balance;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool restockItem(const std::string& itemName, int quantity) {
        auto it = inventory->find(itemName);
        if (it != inventory->end()) {
            it->second.quantity += quantity;
            return true;
        } else {
            return false;
        }
    }

    DisplayResult displayItems() {
        if (inventory->empty()) {
            return false;
        } else {
            std::string result;
            for (const auto& itemName : insertionOrder) {
                auto it = inventory->find(itemName);
                if (it != inventory->end()) {
                    const Product& item = it->second;
                    result += (itemName + " - " + std::to_string(item.price) + " [" + std::to_string(item.quantity) + "]\n");
                }
            }
            return result;
        }
    }
};

int main() {
    VendingMachine vm;
    vm.addItem("Soda", 1.50, 5);
    vm.addItem("Chips", 0.99, 10);
    vm.insertCoin(2.00);
    auto purchaseResult = vm.purchaseItem("Soda");
    if (std::holds_alternative<double>(purchaseResult)) {
        std::cout << "Purchase successful. Balance: " << std::get<double>(purchaseResult) << std::endl;
    } else {
        std::cout << "Purchase failed." << std::endl;
    }
    std::cout << "Inventory: " << vm.displayItems() << std::endl;
    return 0;
}