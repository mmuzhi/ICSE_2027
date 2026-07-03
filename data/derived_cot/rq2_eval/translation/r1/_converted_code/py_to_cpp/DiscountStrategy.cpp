#include <vector>
#include <set>
#include <string>

class DiscountStrategy {
public:
    struct Customer {
        std::string name;
        int fidelity;
    };

    struct Item {
        std::string product;
        int quantity;
        double price;
    };

    using Promotion = double (*)(DiscountStrategy*);

    DiscountStrategy(const Customer& customer, const std::vector<Item>& cart, Promotion promotion = nullptr)
        : customer_(customer), cart_(cart), promotion_(promotion) {
        total_ = total();
    }

    double total() {
        total_ = 0.0;
        for (const auto& item : cart_) {
            total_ += item.quantity * item.price;
        }
        return total_;
    }

    double due() {
        double discount = 0.0;
        if (promotion_) {
            discount = promotion_(this);
        }
        return total_ - discount;
    }

    static double fidelity_discount(DiscountStrategy* order) {
        if (order->customer_.fidelity >= 1000) {
            return order->total() * 0.05;
        }
        return 0.0;
    }

    static double bulk_item_discount(DiscountStrategy* order) {
        double discount = 0.0;
        for (const auto& item : order->cart_) {
            if (item.quantity >= 20) {
                discount += item.quantity * item.price * 0.1;
            }
        }
        return discount;
    }

    static double large_order_discount(DiscountStrategy* order) {
        std::set<std::string> distinct;
        for (const auto& item : order->cart_) {
            distinct.insert(item.product);
        }
        if (distinct.size() >= 10) {
            return order->total() * 0.07;
        }
        return 0.0;
    }

private:
    Customer customer_;
    std::vector<Item> cart_;
    Promotion promotion_;
    double total_;
};