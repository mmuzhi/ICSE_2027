#include <vector>
#include <set>
#include <string>

struct Customer {
    std::string name;
    int fidelity;
};

struct CartItem {
    std::string product;
    int quantity;
    double price;
};

double fidelityPromo(const DiscountStrategy& order) {
    return order.total() * 0.05;
}

double bulkItemPromo(const DiscountStrategy& order) {
    double discount = 0.0;
    for (const auto& item : order.cart) {
        if (item.quantity >= 20) {
            discount += item.quantity * item.price * 0.1;
        }
    }
    return discount;
}

double largeOrderPromo(const DiscountStrategy& order) {
    std::set<std::string> distinctProducts;
    for (const auto& item : order.cart) {
        distinctProducts.insert(item.product);
    }
    return distinctProducts.size() >= 10 ? order.total() * 0.07 : 0.0;
}

class DiscountStrategy {
private:
    const Customer& customer;
    const std::vector<CartItem>& cart;
    double (*promotion)(const DiscountStrategy&) = nullptr;
    double totalAmount;

    double computeTotal() const {
        double total = 0.0;
        for (const auto& item : cart) {
            total += item.quantity * item.price;
        }
        return total;
    }

public:
    DiscountStrategy(const Customer& customer, const std::vector<CartItem>& cart, 
                     double (*promotion)(const DiscountStrategy&) = nullptr)
        : customer(customer), cart(cart), promotion(promotion) {
        totalAmount = computeTotal();
    }

    double total() const {
        return totalAmount;
    }

    double due() const {
        double discount = 0.0;
        if (promotion) {
            discount = promotion(*this);
        }
        return totalAmount - discount;
    }
};