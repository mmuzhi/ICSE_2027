#include <string>
#include <unordered_map>
#include <cmath>

class ShoppingCart {
public:
    class Item {
    private:
        double price;
        int quantity;

        static bool doubleEquals(double a, double b) {
            if (std::isnan(a) && std::isnan(b)) return true;
            return a == b && std::signbit(a) == std::signbit(b);
        }

    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const { return price; }
        void setPrice(double price) { this->price = price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int quantity) { this->quantity = quantity; }

        bool operator==(const Item& other) const {
            return doubleEquals(this->price, other.price) && this->quantity == other.quantity;
        }
    };

private:
    std::unordered_map<std::string, Item> items;

public:
    ShoppingCart() = default;

    void addItem(const std::string& item, double price, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            it->second.setPrice(price);
            it->second.setQuantity(it->second.getQuantity() + quantity);
        } else {
            items.emplace(item, Item(price, quantity));
        }
    }

    void removeItem(const std::string& item, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            int newQuantity = it->second.getQuantity() - quantity;
            if (newQuantity <= 0) {
                items.erase(it);
            } else {
                it->second.setQuantity(newQuantity);
            }
        }
    }

    std::unordered_map<std::string, Item> viewItems() const {
        return items; // Returns a copy
    }

    double totalPrice() const {
        double total = 0.0;
        for (const auto& pair : items) {
            total += pair.second.getPrice() * pair.second.getQuantity();
        }
        return total;
    }
};