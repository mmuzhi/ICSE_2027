#include <string>
#include <vector>
#include <functional>
#include <unordered_set>

struct Customer {
    std::string name;
    double fidelity;
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
        : customer(std::move(customer)), cart(std::move(cart)), promotion(std::move(promotion)), _total(0.0) {
        _total = total();
    }

    double total() {
        _total = 0.0;
        for (const auto& item : cart) {
            _total += item.quantity * item.price;
        }
        return _total;
    }

    double due() {
        double discount = 0.0;
        if (promotion) {
            discount = promotion(*this);
        }
        return _total - discount;
    }

    static double FidelityPromo(DiscountStrategy& order) {
        return order.customer.fidelity >= 1000 ? order.total() * 0.05 : 0.0;
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
        std::unordered_set<std::string> products;
        for (const auto& item : order.cart) {
            products.insert(item.product);
        }
        return products.size() >= 10 ? order.total() * 0.07 : 0.0;
    }

private:
    double _total;
};