#ifndef DISCOUNT_STRATEGY_HPP
#define DISCOUNT_STRATEGY_HPP

#include <functional>
#include <initializer_list>
#include <string>
#include <vector>

class Product {
private:
    std::string name;
    int quantity;
    double price;

public:
    Product(const std::string& name, int quantity, double price)
        : name(name), quantity(quantity), price(price) {}

    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
};

class Customer {
private:
    std::string name;
    int fidelity;

public:
    Customer(const std::string& name, int fidelity)
        : name(name), fidelity(fidelity) {}

    std::string getName() const { return name; }
    int getFidelity() const { return fidelity; }
};

class Cart {
private:
    std::vector<Product> products;

public:
    Cart() = default;

    Cart(std::initializer_list<Product> products) : products(products) {}

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    std::vector<Product>& getProducts() { return products; }
    const std::vector<Product>& getProducts() const { return products; }
};

class DiscountStrategy;

using Promotion = std::function<double(DiscountStrategy&)>;

class DiscountStrategy {
public:
    static Promotion FIDELITY_PROMO;
    static Promotion BULK_ITEM_PROMO;
    static Promotion LARGE_ORDER_PROMO;

    Customer customer;
    Cart cart;

private:
    Promotion promotion_;
    double total_;

public:
    DiscountStrategy(const Customer& customer, const Cart& cart, const Promotion& promotion)
        : customer(customer), cart(cart), promotion_(promotion), total_(0.0) {
        total_ = total();
    }

    double total() {
        total_ = 0.0;
        for (const Product& p : cart.getProducts()) {
            total_ += p.getQuantity() * p.getPrice();
        }
        return total_;
    }

    double due() {
        double discount = promotion_ ? promotion_(*this) : 0.0;
        return total_ - discount;
    }

    double promotion(DiscountStrategy& order) {
        (void)order; // unused, matches Java signature
        return promotion_ ? promotion_(*this) : 0.0;
    }
};

// Static Promotion definitions (after DiscountStrategy is complete)
inline Promotion DiscountStrategy::FIDELITY_PROMO = [](DiscountStrategy& order) -> double {
    return order.customer.getFidelity() >= 1000 ? order.total() * 0.05 : 0.0;
};

inline Promotion DiscountStrategy::BULK_ITEM_PROMO = [](DiscountStrategy& order) -> double {
    double discount = 0.0;
    for (const Product& item : order.cart.getProducts()) {
        if (item.getQuantity() >= 20) {
            discount += item.getQuantity() * item.getPrice() * 0.1;
        }
    }
    return discount;
};

inline Promotion DiscountStrategy::LARGE_ORDER_PROMO = [](DiscountStrategy& order) -> double {
    return order.cart.getProducts().size() >= 10 ? order.total() * 0.07 : 0.0;
};

#endif // DISCOUNT_STRATEGY_HPP