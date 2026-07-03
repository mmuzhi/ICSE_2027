#include <iostream>
#include <map>
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

    void add_item(const std::string& item, double price, int quantity=1) {
        items[item] = ItemInfo{price, quantity};
    }

    void remove_item(const std::string& item, int quantity=1) {
        auto it = items.find(item);
        if (it != items.end()) {
            it->second.quantity -= quantity;
        }
    }

    std::map<std::string, ItemInfo>& view_items() {
        return items;
    }

    double total_price() {
        double total = 0.0;
        for (const auto& kv : items) {
            total += kv.second.quantity * kv.second.price;
        }
        return total;
    }
};