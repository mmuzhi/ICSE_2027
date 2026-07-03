#include <unordered_map>
#include <string>

class Warehouse {
private:
    class Product {
    private:
        std::string name;
        int quantity;

    public:
        Product(const std::string& name, int quantity) : name(name), quantity(quantity) {}

        void addQuantity(int quantity) {
            this->quantity += quantity;
        }

        int getQuantity() const {
            return quantity;
        }
    };

    class Order {
    private:
        int productId;
        int quantity;
        std::string status;

    public:
        Order(int productId, int quantity, const std::string& status) : productId(productId), quantity(quantity), status(status) {}

        void setStatus(const std::string& status) {
            this->status = status;
        }

        std::string getStatus() const {
            return status;
        }
    };

    std::unordered_map<int, Product> inventory;
    std::unordered_map<int, Order> orders;

public:
    Warehouse() {}

    void addProduct(int productId, const std::string& name, int quantity) {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            it->second.addQuantity(quantity);
        } else {
            inventory[productId] = Product(name, quantity);
        }
    }

    void updateProductQuantity(int productId, int quantity) {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            it->second.addQuantity(quantity);
        }
    }

    int getProductQuantity(int productId) const {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            return it->second.getQuantity();
        }
        return -1;
    }

    bool createOrder(int orderId, int productId, int quantity) {
        auto productIt = inventory.find(productId);
        if (productIt == inventory.end()) {
            return false;
        }

        if (productIt->second.getQuantity() < quantity) {
            return false;
        }

        productIt->second.addQuantity(-quantity);
        orders[orderId] = Order(productId, quantity, "Shipped");
        return true;
    }

    bool changeOrderStatus(int orderId, const std::string& status) {
        auto orderIt = orders.find(orderId);
        if (orderIt == orders.end()) {
            return false;
        }

        orderIt->second.setStatus(status);
        return true;
    }

    std::string trackOrder(int orderId) const {
        auto orderIt = orders.find(orderId);
        if (orderIt == orders.end()) {
            return nullptr;
        }
        return orderIt->second.getStatus();
    }
};