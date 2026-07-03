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

    void add_item(const std::string& item, double price, int quantity = 1) {
        items[item] = {price, quantity};
    }

    void remove_item(const std::string& item, int quantity = 1) {
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

    double total_price() {
        double total = 0.0;
        for (const auto& pair : items) {
            total += pair.second.price * pair.second.quantity;
        }
        return total;
    }
};

int main() {
    ShoppingCart cart;
    cart.add_item("apple", 1.0, 5);
    cart.add_item("banana", 2.0, 3);
    cart.remove_item("apple", 3);
    
    std::cout << "Total Price: " << cart.total_price() << std::endl;
    return 0;
}