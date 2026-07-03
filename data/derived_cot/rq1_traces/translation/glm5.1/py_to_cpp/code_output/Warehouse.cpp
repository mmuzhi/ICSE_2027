#include <variant>
#include <string>
#include <unordered_map>

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

    std::variant<int, bool> get_product_quantity(int product_id) {
        if (inventory.find(product_id) != inventory.end()) {
            return inventory[product_id].quantity;
        } else {
            return false;
        }
    }

    std::variant<std::monostate, bool> create_order(int order_id, int product_id, int quantity) {
        auto qty_var = get_product_quantity(product_id);
        // In Python, `False >= quantity` evaluates as `0 >= quantity`.
        // We replicate this exact behavior by extracting 0 if the variant holds `false`.
        int qty = std::holds_alternative<int>(qty_var) ? std::get<int>(qty_var) : 0;
        
        if (qty >= quantity) {
            update_product_quantity(product_id, -quantity);
            orders[order_id] = {product_id, quantity, "Shipped"};
            return std::monostate{}; // Represents Python's `None`
        } else {
            return false;
        }
    }

    std::variant<std::monostate, bool> change_order_status(int order_id, const std::string& status) {
        if (orders.find(order_id) != orders.end()) {
            orders[order_id].status = status;
            return std::monostate{}; // Represents Python's `None`
        } else {
            return false;
        }
    }

    std::variant<std::string, bool> track_order(int order_id) {
        if (orders.find(order_id) != orders.end()) {
            return orders[order_id].status;
        } else {
            return false;
        }
    }
};