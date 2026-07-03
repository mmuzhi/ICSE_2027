#include <string>
#include <unordered_map>
#include <optional>

class Warehouse {
public:
    struct Product {
        std::string name;
        int quantity;
    };

    struct Order {
        int product_id;
        int quantity;
        std::string status;
    };

    std::unordered_map<int, Product> inventory;
    std::unordered_map<int, Order> orders;

    void add_product(int product_id, const std::string& name, int quantity) {
        auto it = inventory.find(product_id);
        if (it == inventory.end()) {
            inventory[product_id] = {name, quantity};
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
        auto qty_opt = get_product_quantity(product_id);
        if (!qty_opt.has_value() || qty_opt.value() < quantity) {
            return false;
        }
        update_product_quantity(product_id, -quantity);
        orders[order_id] = {product_id, quantity, "Shipped"};
        return true;
    }

    bool change_order_status(int order_id, const std::string& status) {
        auto it = orders.find(order_id);
        if (it == orders.end()) {
            return false;
        }
        it->second.status = status;
        return true;
    }

    std::optional<std::string> track_order(int order_id) {
        auto it = orders.find(order_id);
        if (it != orders.end()) {
            return it->second.status;
        }
        return std::nullopt;
    }
};