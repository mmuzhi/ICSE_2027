#include <unordered_map>
#include <string>
#include <cstddef>
#include <functional>

class ShoppingCart {
public:
    class Item {
    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}
        
        double getPrice() const { return price; }
        void setPrice(double p) { price = p; }
        int getQuantity() const { return quantity; }
        void setQuantity(int q) { quantity = q; }

        bool operator==(const Item& other) const {
            return price == other.price && quantity == other.quantity;
        }

        bool operator!=(const Item& other) const {
            return !(*this == other);
        }

        size_t hashCode() const {
            // Simple combination, not identical to Java's Objects.hash but preserves existence of the method.
            return std::hash<double>()(price) ^ (std::hash<int>()(quantity) << 1);
        }

    private:
        double price;
        int quantity;
    };

    ShoppingCart() = default;

    void addItem(const std::string& item, double price, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            Item& existing = it->second;
            existing.setPrice(price);
            existing.setQuantity(existing.getQuantity() + quantity);
        } else {
            items.emplace(item, Item(price, quantity));
        }
    }

    void removeItem(const std::string& item, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            Item& existing = it->second;
            int newQty = existing.getQuantity() - quantity;
            if (newQty <= 0) {
                items.erase(it);
            } else {
                existing.setQuantity(newQty);
            }
        }
    }

    std::unordered_map<std::string, Item> viewItems() const {
        return items; // returns a copy
    }

    double totalPrice() const {
        double total = 0.0;
        for (const auto& pair : items) {
            const Item& item = pair.second;
            total += item.getPrice() * item.getQuantity();
        }
        return total;
    }

private:
    std::unordered_map<std::string, Item> items;
};

// std::hash specialization for Item (optional, enables use as key in unordered containers)
namespace std {
    template<>
    struct hash<ShoppingCart::Item> {
        size_t operator()(const ShoppingCart::Item& item) const {
            return item.hashCode();
        }
    };
}