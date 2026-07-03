#include <unordered_map>
#include <optional>
#include <string>

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
    Warehouse() = default;

    void add_product(int product_id, const std::string& name, int quantity) {
        if (inventory.find(product_id) == inventory.end()) {
            inventory[product_id] = {name, quantity};
        } else {
            inventory[product_id].quantity += quantity;
        }
    }

    void update_product_quantity(int product_id, int quantity) {
        if (inventory.find(product_id) != inventory.end()) {
            inventory[product_id].quantity += quantity;
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
        auto quantity_opt = get_product_quantity(product_id);
        if (!quantity_opt.has_value()) {
            return false;
        }
        if (*quantity_opt < quantity) {
            return false;
        }
        update_product_quantity(product_id, -quantity);
        orders[order_id] = {product_id, quantity, "Shipped"};
        return true;
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