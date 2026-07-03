#include <unordered_map>
#include <string>

class Warehouse {
private:
    struct Product {
        std::string name;
        int quantity;

        Product(std::string name, int quantity) : name(name), quantity(quantity) {}
        void addQuantity(int quantity) { this->quantity += quantity; }
        int getQuantity() const { return quantity; }
    };

    struct Order {
        int productId;
        int quantity;
        std::string status;

        Order(int productId, int quantity, std::string status) 
            : productId(productId), quantity(quantity), status(std::move(status)) {}
        void setStatus(std::string status) { this->status = std::move(status); }
        std::string getStatus() const { return status; }
    };

    std::unordered_map<int, Product> inventory;
    std::unordered_map<int, Order> orders;

public:
    Warehouse() = default;

    void add_product(int productId, std::string name, int quantity) {
        if (inventory.find(productId) != inventory.end()) {
            inventory[productId].addQuantity(quantity);
        } else {
            inventory[productId] = Product(name, quantity);
        }
    }

    void update_product_quantity(int productId, int quantity) {
        if (inventory.find(productId) != inventory.end()) {
            inventory[productId].addQuantity(quantity);
        }
    }

    int get_product_quantity(int productId) const {
        if (inventory.find(productId) != inventory.end()) {
            return inventory[productId].getQuantity();
        }
        return -1;
    }

    bool create_order(int orderId, int productId, int quantity) {
        if (inventory.find(productId) != inventory.end() && 
            inventory[productId].getQuantity() >= quantity) {
            inventory[productId].addQuantity(-quantity);
            orders[orderId] = Order(productId, quantity, "Shipped");
            return true;
        }
        return false;
    }

    bool change_order_status(int orderId, std::string status) {
        if (orders.find(orderId) != orders.end()) {
            orders[orderId].setStatus(status);
            return true;
        }
        return false;
    }

    std::string track_order(int orderId) const {
        if (orders.find(orderId) != orders.end()) {
            return orders[orderId].getStatus();
        }
        return "";
    }
};