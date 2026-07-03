#include <iostream>
#include <map>
#include <string>
#include <vector>

class ShoppingCart {
private:
    std::map<std::string, struct Item> items;

    struct Item {
        double price;
        int quantity;
    };

public:
    ShoppingCart() {}

    void addItem(const std::string& item, double price, int quantity = 1) {
        items[item] = {price, quantity};
    }

    void removeItem(const std::string& item, int quantity = 1) {
        auto it = items.find(item);
        if (it != items.end()) {
            if (it->second.quantity > quantity) {
                it->second.quantity -= quantity;
            } else {
                items.erase(it);
            }
        }
    }

    std::map<std::string, struct Item> viewItems() {
        return items;
    }

    double totalPrice() {
        double total = 0.0;
        for (const auto& pair : items) {
            total += pair.second.price * pair.second.quantity;
        }
        return total;
    }
};

int main() {
    ShoppingCart cart;
    cart.addItem("apple", 1.0, 5);
    cart.addItem("banana", 2.0, 3);
    cart.removeItem("apple", 3);
    
    std::cout << "Total Price: " << cart.totalPrice() << std::endl;
    return 0;
}