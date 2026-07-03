#include <map>
#include <string>

class ShoppingCart {
public:
    // Struct to represent the inner dictionary {'price': price, 'quantity': quantity}
    struct ItemInfo {
        double price;
        int quantity;
    };

    ShoppingCart() = default;

    // Add item information to the shopping list items. 
    // Note: The original Python code replaces the item whether it exists or not.
    void add_item(const std::string& item, double price, int quantity = 1) {
        items[item] = {price, quantity};
    }

    // Subtract the specified quantity of item from the shopping list items.
    void remove_item(const std::string& item, int quantity = 1) {
        auto it = items.find(item);
        if (it != items.end()) {
            it->second.quantity -= quantity;
        }
    }

    // Return the current shopping list items.
    // A non-const reference is returned to match Python's reference behavior 
    // where modifying the returned dict modifies the class's internal state.
    std::map<std::string, ItemInfo>& view_items() {
        return items;
    }

    // Calculate the total price of all items in the shopping list.
    double total_price() const {
        double total = 0.0;
        for (const auto& pair : items) {
            total += pair.second.quantity * pair.second.price;
        }
        return total;
    }

private:
    std::map<std::string, ItemInfo> items;
};