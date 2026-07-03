#include <unordered_map>
#include <string>
#include <variant>

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

    int get_product_quantity(int product_id) {
        auto it = inventory.find(product_id);
        if (it == inventory.end()) {
            return -1;
        }
        return it->second.quantity;
    }

    bool create_order(int order_id, int product_id, int quantity) {
        auto it = inventory.find(product_id);
        int available = 0;
        if (it != inventory.end()) {
            available = it->second.quantity;
        }
        if (available >= quantity) {
            if (it != inventory.end()) {
                it->second.quantity -= quantity;
            }
            orders[order_id] = Order{product_id, quantity, "Shipped"};
            return true;
        }
        return false;
    }

    bool change_order_status(int order_id, const std::string& status) {
        auto it = orders.find(order_id);
        if (it == orders.end()) {
            return false;
        }
        it->second.status = status;
        return true;
    }

    std::variant<std::string, bool> track_order(int order_id) {
        auto it = orders.find(order_id);
        if (it == orders.end()) {
            return false;
        }
        return it->second.status;
    }
};