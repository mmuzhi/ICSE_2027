#include <unordered_map>
#include <string>
#include <memory>

class ShoppingCart {
public:
    class Item {
    public:
        Item(double price, int quantity) : price(price), quantity(quantity) {}

        double getPrice() const {
            return price;
        }

        void setPrice(double price) {
            this->price = price;
        }

        int getQuantity() const {
            return quantity;
        }

        void setQuantity(int quantity) {
            this->quantity = quantity;
        }

    private:
        double price;
        int quantity;
    };

    ShoppingCart() = default;

    void add_item(const std::string& item, double price, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            auto& existingItem = it->second;
            existingItem->setPrice(price);
            existingItem->setQuantity(existingItem->getQuantity() + quantity);
        } else {
            items[item] = std::make_shared<Item>(price, quantity);
        }
    }

    void remove_item(const std::string& item, int quantity) {
        auto it = items.find(item);
        if (it != items.end()) {
            auto& existingItem = it->second;
            int newQuantity = existingItem->getQuantity() - quantity;
            if (newQuantity <= 0) {
                items.erase(it);
            } else {
                existingItem->setQuantity(newQuantity);
            }
        }
    }

    std::unordered_map<std::string, std::shared_ptr<Item>> viewItems() const {
        return items;
    }

    double total_price() const {
        double total = 0.0;
        for (const auto& entry : items) {
            const std::shared_ptr<Item>& item = entry.second;
            total += item->getPrice() * item->getQuantity();
        }
        return total;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Item>> items;
};