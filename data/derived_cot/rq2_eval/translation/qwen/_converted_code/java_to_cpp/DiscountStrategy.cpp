#include <vector>
#include <string>
#include <functional>

class Customer {
public:
    Customer(const std::string& name, int fidelity) : name(name), fidelity(fidelity) {}
    std::string getName() const { return name; }
    int getFidelity() const { return fidelity; }

private:
    std::string name;
    int fidelity;
};

class Cart {
public:
    Cart() = default;
    void addProduct(const Product& product) { products.push_back(product); }
    const std::vector<Product>& getProducts() const { return products; }

private:
    std::vector<Product> products;
};

class Product {
public:
    Product(const std::string& name, int quantity, double price) : name(name), quantity(quantity), price(price) {}
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

private:
    std::string name;
    int quantity;
    double price;
};

class DiscountStrategy {
public:
    using Promotion = std::function<double(const DiscountStrategy&)>;

    static const Promotion FIDELITY_PROMO;
    static const Promotion BULK_ITEM_PROMO;
    static const Promotion LARGE_ORDER_PROMO;

    DiscountStrategy(const Customer& customer, const Cart& cart, const Promotion& promotion)
        : customer(customer), cart(cart), promotion(promotion), total(0.0) {}

    double total() const;
    double due() const;
    double promotion(const DiscountStrategy& order) const;

private:
    Customer customer;
    Cart cart;
    Promotion promotion;
    mutable double total;
};

// Define static members
const DiscountStrategy::Promotion DiscountStrategy::FIDELITY_PROMO = [](const DiscountStrategy& order) {
    return order.customer.getFidelity() >= 1000 ? order.total() * 0.05 : 0;
};

const DiscountStrategy::Promotion DiscountStrategy::BULK_ITEM_PROMO = [](const DiscountStrategy& order) {
    double discount = 0.0;
    for (const auto& item : order.cart.getProducts()) {
        if (item.getQuantity() >= 20) {
            discount += item.getQuantity() * item.getPrice() * 0.1;
        }
    }
    return discount;
};

const DiscountStrategy::Promotion DiscountStrategy::LARGE_ORDER_PROMO = [](const DiscountStrategy& order) {
    return order.cart.getProducts().size() >= 10 ? order.total() * 0.07 : 0;
};

double DiscountStrategy::total() const {
    total = 0.0;
    for (const auto& product : cart.getProducts()) {
        total += product.getQuantity() * product.getPrice();
    }
    return total;
}

double DiscountStrategy::due() const {
    double discount = (promotion == nullptr) ? 0 : promotion(*this);
    return total - discount;
}

double DiscountStrategy::promotion(const DiscountStrategy& order) const {
    return (promotion == nullptr) ? 0 : promotion(order);
}