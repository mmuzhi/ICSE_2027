#include <vector>
#include <string>
#include <set>
#include <functional>

struct Customer {
    std::string name;
    int fidelity;
};

struct CartItem {
    std::string product;
    int quantity;
    double price;
};

class DiscountStrategy {
private:
    Customer customer;
    std::vector<CartItem> cart;
    std::function<double(const DiscountStrategy&)> promotion;
    double total_;

public:
    DiscountStrategy(const Customer& customer, const std::vector<CartItem>& cart, std::function<double(const DiscountStrategy&)> promotion = nullptr)
        : customer(customer), cart(cart), promotion(promotion) {
        total_ = total();
    }

    double total() const {
        double total = 0.0;
        for (const auto& item : cart) {
            total += item.quantity * item.price;
        }
        return total;
    }

    double due() const {
        double discount = 0.0;
        if (promotion) {
            discount = promotion(*this);
        }
        return total_ - discount;
    }

    static double fidelity_discount(const DiscountStrategy& order) {
        if (order.customer.fidelity >= 1000) {
            return order.total() * 0.05;
        }
        return 0.0;
    }

    static double bulk_item_discount(const DiscountStrategy& order) {
        double discount = 0.0;
        for (const auto& item : order.cart) {
            if (item.quantity >= 20) {
                discount += item.quantity * item.price * 0.1;
            }
        }
        return discount;
    }

    static double large_order_discount(const DiscountStrategy& order) {
        std::set<std::string> distinct_products;
        for (const auto& item : order.cart) {
            distinct_products.insert(item.product);
        }
        if (distinct_products.size() >= 10) {
            return order.total() * 0.07;
        }
        return 0.0;
    }
};