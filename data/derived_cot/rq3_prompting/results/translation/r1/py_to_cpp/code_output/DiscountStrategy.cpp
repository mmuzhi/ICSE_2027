#include <string>
#include <vector>
#include <functional>
#include <set>
#include <numeric>

class DiscountStrategy {
public:
    struct Customer {
        std::string name;
        int fidelity;
    };

    struct CartItem {
        std::string product;
        int quantity;
        double price;
    };

    using PromoFunc = std::function<double(const DiscountStrategy&)>;

    DiscountStrategy(const Customer& customer, const std::vector<CartItem>& cart, PromoFunc promotion = nullptr)
        : customer_(customer), cart_(cart), promotion_(promotion) {
        total();
    }

    double total() const {
        double sum = 0.0;
        for (const auto& item : cart_) {
            sum += item.quantity * item.price;
        }
        total_ = sum;
        return total_;
    }

    double due() const {
        double discount = 0.0;
        if (promotion_) {
            discount = promotion_(*this);
        }
        return total_ - discount;
    }

    static double FidelityPromo(const DiscountStrategy& order) {
        if (order.customer_.fidelity >= 1000) {
            return order.total() * 0.05;
        }
        return 0.0;
    }

    static double BulkItemPromo(const DiscountStrategy& order) {
        double discount = 0.0;
        for (const auto& item : order.cart_) {
            if (item.quantity >= 20) {
                discount += item.quantity * item.price * 0.1;
            }
        }
        return discount;
    }

    static double LargeOrderPromo(const DiscountStrategy& order) {
        std::set<std::string> products;
        for (const auto& item : order.cart_) {
            products.insert(item.product);
        }
        if (products.size() >= 10) {
            return order.total() * 0.07;
        }
        return 0.0;
    }

private:
    Customer customer_;
    std::vector<CartItem> cart_;
    PromoFunc promotion_;
    mutable double total_ = 0.0;
};