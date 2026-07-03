#include <iostream>
#include <unordered_map>
#include <variant>
#include <string>

// Define structs for Product and Order
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

    bool is_product_exists(int product_id) const {
        return inventory.find(product_id) != inventory.end();
    }

    int get_product_quantity(int product_id) const {
        return inventory.at(product_id).quantity;
    }

public:
    Warehouse() = default;

    void add_product(int product_id, const std::string& name, int quantity) {
        if (!is_product_exists(product_id)) {
            inventory[product_id] = {name, quantity};
        } else {
            inventory[product_id].quantity += quantity;
        }
    }

    void update_product_quantity(int product_id, int quantity) {
        if (is_product_exists(product_id)) {
            inventory[product_id].quantity += quantity;
        }
    }

    std::variant<int, bool> get_product_quantity(int product_id) {
        if (is_product_exists(product_id)) {
            return inventory[product_id].quantity;
        }
        return false;
    }

    bool create_order(int order_id, int product_id, int quantity) {
        if (get_product_quantity(product_id) >= quantity) {
            update_product_quantity(product_id, -quantity);
            orders[order_id] = {product_id, quantity, "Shipped"};
            return true;
        }
        return false;
    }

    bool change_order_status(int order_id, const std::string& status) {
        if (orders.find(order_id) != orders.end()) {
            orders[order_id].status = status;
            return true;
        }
        return false;
    }

    std::variant<std::string, bool> track_order(int order_id) {
        if (orders.find(order_id) != orders.end()) {
            return orders[order_id].status;
        }
        return false;
    }
};