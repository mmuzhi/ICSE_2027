#include <string>
#include <unordered_map>
#include <optional>

struct Product {
    std::string name;
    int quantity;
};

struct Order {
    int product_id;
    int quantity;
    std::string status;
};

class Warehouse {
private:
    std::unordered_map<int, Product> inventory;
    std::unordered_map<int, Order> orders;

public:
    void add_product(int product_id, const std::string& name, int quantity) {
        auto it = inventory.find(product_id);
        if (it == inventory.end()) {
            inventory[product_id] = Product{name, quantity};
        } else {
            it->second.quantity += quantity;
        }
    }

    void update_product_quantity(int product_id, int quantity) {
        auto it = inventory.find(product_id);
        if (it != inventory.end()) {
            it->second.quantity += quantity;
        }
    }

    std::optional<int> get_product_quantity(int product_id) {
        auto it = inventory.find(product_id);
        if (it != inventory.end()) {
            return it->second.quantity;
        }
        return std::nullopt;
    }

    bool create_order(int order_id, int product_id, int quantity) {
        // Replicate Python: get_product_quantity returns False (==0) if not found,
        // so False >= quantity behaves as 0 >= quantity.
        int available = 0;
        auto it = inventory.find(product_id);
        if (it != inventory.end()) {
            available = it->second.quantity;
        }
        if (available >= quantity) {
            update_product_quantity(product_id, -quantity);
            orders[order_id] = Order{product_id, quantity, "Shipped"};
            return true;
        }
        return false;
    }

    bool change_order_status(int order_id, const std::string& status) {
        auto it = orders.find(order_id);
        if (it != orders.end()) {
            it->second.status = status;
            return true;
        }
        return false;
    }

    std::optional<std::string> track_order(int order_id) {
        auto it = orders.find(order_id);
        if (it != orders.end()) {
            return it->second.status;
        }
        return std::nullopt;
    }
};