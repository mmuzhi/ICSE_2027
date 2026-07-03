#include <vector>
#include <functional>
#include <string>

class DiscountStrategy;

using Promotion = std::function<double(DiscountStrategy*)>;

class Product {
    std::string name;
    int quantity;
    double price;
public:
    Product(std::string name, int quantity, double price)
        : name(std::move(name)), quantity(quantity), price(price) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
};

class Customer {
    std::string name;
    int fidelity;
public:
    Customer(std::string name, int fidelity)
        : name(std::move(name)), fidelity(fidelity) {}
    std::string getName() const { return name; }
    int getFidelity() const { return fidelity; }
};

class Cart {
    std::vector<Product> products;
public:
    Cart(std::initializer_list<Product> prods) {
        for (const auto& p : prods) products.push_back(p);
    }
    void addProduct(const Product& product) { products.push_back(product); }
    std::vector<Product>& getProducts() { return products; }
};

class DiscountStrategy {
public:
    static Promotion FIDELITY_PROMO;
    static Promotion BULK_ITEM_PROMO;
    static Promotion LARGE_ORDER_PROMO;

private:
    Customer customer;
    Cart cart;
    Promotion promotion;
    double total;

public:
    DiscountStrategy(Customer customer, Cart cart, Promotion promotion)
        : customer(std::move(customer)), cart(std::move(cart)), promotion(std::move(promotion)), total(0.0) {
        total = this->total();
    }

    double total() {
        total = 0.0;
        for (const auto& p : cart.getProducts()) {
            total += p.getQuantity() * p.getPrice();
        }
        return total;
    }

    double due() {
        double discount = promotion ? promotion(this) : 0.0;
        return total - discount;
    }

    double promotion(DiscountStrategy& /*order*/) {
        return promotion ? promotion(this) : 0.0;
    }

    Customer& getCustomer() { return customer; }
    Cart& getCart() { return cart; }
};

Promotion DiscountStrategy::FIDELITY_PROMO = [](DiscountStrategy* order) -> double {
    return order->getCustomer().getFidelity() >= 1000 ? order->total() * 0.05 : 0.0;
};

Promotion DiscountStrategy::BULK_ITEM_PROMO = [](DiscountStrategy* order) -> double {
    double discount = 0.0;
    for (const Product& item : order->getCart().getProducts()) {
        if (item.getQuantity() >= 20) {
            discount += item.getQuantity() * item.getPrice() * 0.1;
        }
    }
    return discount;
};

Promotion DiscountStrategy::LARGE_ORDER_PROMO = [](DiscountStrategy* order) -> double {
    return order->getCart().getProducts().size() >= 10 ? order->total() * 0.07 : 0.0;
};