#include <iostream>
#include <map>
#include <vector>
#include <string>

struct ItemInfo {
    double price;
    int quantity;
};

class ShoppingCart {
private:
    std::map<std::string, ItemInfo> items;

public:
    ShoppingCart() {}

    void add_item(const std::string& item, double price, int quantity = 1) {
        if (items.find(item) != items.end()) {
            items[item].price = price;
            items[item].quantity = quantity;
        } else {
            items[item] = {price, quantity};
        }
    }

    void remove_item(const std::string& item, int quantity = 1) {
        if (items.find(item) != items.end()) {
            items[item].quantity -= quantity;
        }
    }

    std::map<std::string, ItemInfo> view_items() const {
        return items;
    }

    double total_price() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += static_cast<double>(item.second.quantity) * item.second.price;
        }
        return total;
    }
};

int main() {
    ShoppingCart cart;
    cart.add_item("apple", 1.0, 5);
    cart.add_item("banana", 2.0, 3);
    cart.remove_item("apple", 2);
    
    std::cout << "Total price: " << cart.total_price() << std::endl;
    for (const auto& item : cart.view_items()) {
        std::cout << item.first << ": " << item.second.quantity << " at " << item.second.price << std::endl;
    }
    return 0;
}