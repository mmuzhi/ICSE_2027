#include <string>
#include <vector>
#include <functional>
#include <set>

struct Customer {
    std::string name;
    int fidelity;
};

struct Item {
    std::string product;
    int quantity;
    double price;
};

class DiscountStrategy {
public:
    Customer customer;
    std::vector<Item> cart;
    std::function<double(DiscountStrategy&)> promotion;

    DiscountStrategy(Customer customer, std::vector<Item> cart, std::function<double(DiscountStrategy&)> promotion = nullptr)
        : customer(std::move(customer)), cart(std::move(cart)), promotion(std::move(promotion)) {
        total();
    }

    double total() {
        total_ = 0.0;
        for (const auto& item : cart) {
            total_ += item.quantity * item.price;
        }
        return total_;
    }

    double due() {
        double discount = 0.0;
        if (promotion) {
            discount = promotion(*this);
        }
        return total_ - discount;
    }

    static double FidelityPromo(DiscountStrategy& order) {
        if (order.customer.fidelity >= 1000) {
            return order.total() * 0.05;
        }
        return 0.0;
    }

    static double BulkItemPromo(DiscountStrategy& order) {
        double discount = 0.0;
        for (const auto& item : order.cart) {
            if (item.quantity >= 20) {
                discount += item.quantity * item.price * 0.1;
            }
        }
        return discount;
    }

    static double LargeOrderPromo(DiscountStrategy& order) {
        std::set<std::string> products;
        for (const auto& item : order.cart) {
            products.insert(item.product);
        }
        if (products.size() >= 10) {
            return order.total() * 0.07;
        }
        return 0.0;
    }

private:
    double total_;
};