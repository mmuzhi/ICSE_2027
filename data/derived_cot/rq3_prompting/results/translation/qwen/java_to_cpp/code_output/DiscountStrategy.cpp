#include <vector>
#include <string>
#include <functional>

struct DiscountStrategy {
    struct Customer {
        std::string name;
        int fidelity;

        Customer(const std::string& name, int fidelity)
            : name(name), fidelity(fidelity) {}
    };

    struct Cart {
        std::vector<Product> products;

        Cart() {}
        explicit Cart(std::initializer_list<Product> items) {
            for (auto& item : items) {
                products.push_back(item);
            }
        }

        void addProduct(const Product& product) {
            products.push_back(product);
        }

        const std::vector<Product>& getProducts() const {
            return products;
        }
    };

    struct Product {
        std::string name;
        int quantity;
        double price;

        Product(const std::string& name, int quantity, double price)
            : name(name), quantity(quantity), price(price) {}
    };

    using Promotion = std::function<double(DiscountStrategy&)>;

    static const Promotion FIDELITY_PROMO;
    static const Promotion BULK_ITEM_PROMO;
    static const Promotion LARGE_ORDER_PROMO;

    Customer customer;
    Cart cart;
    Promotion promotion;
    double total;

    void recalculateTotal() const {
        total = 0.0;
        for (const auto& product : cart.products) {
            total += product.quantity * product.price;
        }
    }

    DiscountStrategy(const Customer& customer, const Cart& cart, const Promotion& promotion)
        : customer(customer), cart(cart), promotion(promotion) {
        recalculateTotal();
    }

    double total() {
        recalculateTotal();
        return total;
    }

    double due() const {
        double discount = 0.0;
        if (promotion) {
            discount = promotion(*this);
        }
        return total - discount;
    }

    double promotion(DiscountStrategy& order) {
        return promotion ? promotion(order) : 0;
    };
};

const DiscountStrategy::Promotion DiscountStrategy::FIDELITY_PROMO = [](DiscountStrategy& order) {
    return order.customer.fidelity >= 1000 ? order.total() * 0.05 : 0;
};

const DiscountStrategy::Promotion DiscountStrategy::BULK_ITEM_PROMO = [](DiscountStrategy& order) {
    double discount = 0.0;
    for (const auto& product : order.cart.products) {
        if (product.quantity >= 20) {
            discount += product.quantity * product.price * 0.1;
        }
    }
    return discount;
};

const DiscountStrategy::Promotion DiscountStrategy::LARGE_ORDER_PROMO = [](DiscountStrategy& order) {
    return order.cart.products.size() >= 10 ? order.total() * 0.07 : 0;
};