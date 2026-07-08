#include <unordered_map>
#include <string>
#include <cmath>
#include <functional>

class ShoppingCart {
public:
    class Item {
    private:
        double price;
        int quantity;

        // Helper to strictly mimic Java's Double.compare(a, b) == 0
        static bool doubleEquals(double a, double b) {
            bool aIsNaN = std::isnan(a);
            bool bIsNaN = std::isnan(b);
            if (aIsNaN && bIsNaN) return true;
            if (aIsNaN || bIsNaN) return false;
            if (a == 0.0 && b == 0.0) return std::signbit(a) == std::signbit(b);
            return a == b;
        }

    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const { return price; }
        void setPrice(double price) { this->price = price; }
        
        int getQuantity() const { return quantity; }
        void setQuantity(int quantity) { this->quantity = quantity; }

        // Equivalent to Java's equals(Object o)
        bool operator==(const Item& other) const {
            return doubleEquals(price, other.price) && quantity == other.quantity;
        }

        bool operator!=(const Item& other) const {
            return !(*this == other);
        }
    };

private:
    std::unordered_map<std::string, Item> items;

public:
    ShoppingCart() = default;

    void addItem(const std::string& item, double price, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            Item& existingItem = it->second;
            existingItem.setPrice(price);
            existingItem.setQuantity(existingItem.getQuantity() + quantity);
        } else {
            items.emplace(item, Item(price, quantity));
        }
    }

    void removeItem(const std::string& item, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            Item& existingItem = it->second;
            int newQuantity = existingItem.getQuantity() - quantity;
            if (newQuantity <= 0) {
                items.erase(it);
            } else {
                existingItem.setQuantity(newQuantity);
            }
        }
    }

    // Returns a copy of the map, identical to Java's "return new HashMap<>(items);"
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
};

// Equivalent to Java's Objects.hash(price, quantity)
namespace std {
    template<>
    struct hash<ShoppingCart::Item> {
        size_t operator()(const ShoppingCart::Item& i) const noexcept {
            size_t h = 1;
            h = 31 * h + hash<double>{}(i.getPrice());
            h = 31 * h + hash<int>{}(i.getQuantity());
            return h;
        }
    };
}