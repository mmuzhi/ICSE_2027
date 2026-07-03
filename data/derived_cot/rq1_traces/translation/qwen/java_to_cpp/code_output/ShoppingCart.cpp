#include <iostream>
#include <unordered_map>
#include <string>

class ShoppingCart {
private:
    std::unordered_map<std::string, Item> items;

public:
    ShoppingCart() {}

    void addItem(const std::string& item, double price, int quantity) {
        if (items.find(item) != items.end()) {
            Item& existingItem = items[item];
            existingItem.setPrice(price);
            existingItem.setQuantity(existingItem.getQuantity() + quantity);
        } else {
            items[item] = Item(price, quantity);
        }
    }

    void removeItem(const std::string& item, int quantity) {
        if (items.find(item) != items.end()) {
            Item& existingItem = items[item];
            int newQuantity = existingItem.getQuantity() - quantity;
            if (newQuantity <= 0) {
                items.erase(item);
            } else {
                existingItem.setQuantity(newQuantity);
            }
        }
    }

    std::unordered_map<std::string, Item> viewItems() const {
        return items;
    }

    double totalPrice() const {
        double total = 0.0;
        for (const auto& pair : items) {
            const Item& item = pair.second;
            total += item.getPrice() * item.getQuantity();
        }
        return total;
    }

    class Item {
    private:
        double price;
        int quantity;

    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}

        void setPrice(double price) {
            this->price = price;
        }

        void setQuantity(int quantity) {
            this->quantity = quantity;
        }

        double getPrice() const {
            return price;
        }

        int getQuantity() const {
            return quantity;
        }

        bool operator==(const Item& other) const {
            return price == other.price && quantity == other.quantity;
        }

        struct Hash {
            size_t operator()(const Item& item) const {
                auto hash1 = std::hash<double>{}(item.price);
                auto hash2 = std::hash<int>{}(item.quantity);
                return hash1 ^ (hash2 << 1);
            }
        };
    };
};