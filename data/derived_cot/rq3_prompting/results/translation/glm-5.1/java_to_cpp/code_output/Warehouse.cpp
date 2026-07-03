#include <unordered_map>
#include <string>
#include <optional>

class Warehouse {
private:
    struct Product {
        std::string name;
        int quantity;

        Product(std::string name, int quantity) : name(std::move(name)), quantity(quantity) {}

        void addQuantity(int qty) {
            this->quantity += qty;
        }

        int getQuantity() const {
            return quantity;
        }
    };

    struct Order {
        int productId;
        int quantity;
        std::string status;

        Order(int productId, int quantity, std::string status) : productId(productId), quantity(quantity), status(std::move(status)) {}

        std::string getStatus() const {
            return status;
        }

        void setStatus(std::string stat) {
            this->status = std::move(stat);
        }
    };

    std::unordered_map<int, Product> inventory;
    std::unordered_map<int, Order> orders;

public:
    Warehouse() = default;

    void addProduct(int productId, const std::string& name, int quantity) {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            it->second.addQuantity(quantity);
        } else {
            inventory.emplace(productId, Product(name, quantity));
        }
    }

    void updateProductQuantity(int productId, int quantity) {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            it->second.addQuantity(quantity);
        }
    }

    int getProductQuantity(int productId) {
        auto it = inventory.find(productId);
        if (it != inventory.end()) {
            return it->second.getQuantity();
        } else {
            return -1;
        }
    }

    bool createOrder(int orderId, int productId, int quantity) {
        auto it = inventory.find(productId);
        if (it != inventory.end() && it->second.getQuantity() >= quantity) {
            it->second.addQuantity(-quantity);
            orders.emplace(orderId, Order(productId, quantity, "Shipped"));
            return true;
        } else {
            return false;
        }
    }

    bool changeOrderStatus(int orderId, const std::string& status) {
        auto it = orders.find(orderId);
        if (it != orders.end()) {
            it->second.setStatus(status);
            return true;
        } else {
            return false;
        }
    }

    std::optional<std::string> trackOrder(int orderId) {
        auto it = orders.find(orderId);
        if (it != orders.end()) {
            return it->second.getStatus();
        } else {
            return std::nullopt;
        }
    }
};