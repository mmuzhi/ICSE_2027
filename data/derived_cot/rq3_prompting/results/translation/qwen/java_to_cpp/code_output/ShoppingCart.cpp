#include <iostream>
#include <unordered_map>
#include <string>

class ShoppingCart {
private:
    std::unordered_map<std::string, Item> items;

public:
    ShoppingCart() = default;

    void addItem(const std::string& item, double price, int quantity) {
        if (auto it = items.find(item); it != items.end()) {
            it->second.setPrice(price);
            it->second.setQuantity(it->second.getQuantity() + quantity);
        } else {
            items[item] = Item(price, quantity);
        }
    }

    void removeItem(const std::string& item, int quantity) {
        if (auto it = items.find(item); it != items.end()) {
            int newQuantity = it->second.getQuantity() - quantity;
            if (newQuantity <= 0) {
                items.erase(it);
            } else {
                it->second.setQuantity(newQuantity);
            }
        }
    }

    std::unordered_map<std::string, Item> viewItems() const {
        return items;
    }

    double totalPrice() const {
        double total = 0.0;
        for (const auto& entry : items) {
            total += entry.second.getPrice() * entry.second.getQuantity();
        }
        return total;
    }

    class Item {
    private:
        double price;
        int quantity;

    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const { return price; }
        void setPrice(double price) { this->price = price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int quantity) { this->quantity = quantity; }
    };
};