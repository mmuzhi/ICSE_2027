#include <string>
#include <vector>
#include <functional>
#include <initializer_list>

class DiscountStrategy {
public:
    // Promotion type alias (functional interface)
    using Promotion = std::function<double(DiscountStrategy&)>;

    // Static promotion definitions
    inline static const Promotion FIDELITY_PROMO = [](DiscountStrategy& order) -> double {
        return order.customer.getFidelity() >= 1000 ? order.total() * 0.05 : 0;
    };

    inline static const Promotion BULK_ITEM_PROMO = [](DiscountStrategy& order) -> double {
        double discount = 0;
        for (const auto& item : order.cart.getProducts()) {
            if (item.getQuantity() >= 20) {
                discount += item.getQuantity() * item.getPrice() * 0.1;
            }
        }
        return discount;
    };

    inline static const Promotion LARGE_ORDER_PROMO = [](DiscountStrategy& order) -> double {
        return order.cart.getProducts().size() >= 10 ? order.total() * 0.07 : 0;
    };

    // Nested class Customer
    class Customer {
    private:
        std::string name;
        int fidelity;
    public:
        Customer(const std::string& name, int fidelity) : name(name), fidelity(fidelity) {}
        const std::string& getName() const { return name; }
        int getFidelity() const { return fidelity; }
    };

    // Nested class Product
    class Product {
    private:
        std::string name;
        int quantity;
        double price;
    public:
        Product(const std::string& name, int quantity, double price) 
            : name(name), quantity(quantity), price(price) {}
        const std::string& getName() const { return name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
    };

    // Nested class Cart
    class Cart {
    private:
        std::vector<Product> products;
    public:
        Cart(std::initializer_list<Product> list) : products(list) {}
        void addProduct(const Product& product) { products.push_back(product); }
        const std::vector<Product>& getProducts() const { return products; }
    };

    // Constructor
    DiscountStrategy(const Customer& customer, const Cart& cart, Promotion promotion)
        : customer(customer), cart(cart), promotion(std::move(promotion)), total(0.0) {
        total = total();   // compute and store total
    }

    // Recalculate total from cart
    double total() {
        total = 0.0;
        for (const auto& p : cart.getProducts()) {
            total += p.getQuantity() * p.getPrice();
        }
        return total;
    }

    // Amount due after discount
    double due() {
        double discount = promotion ? promotion(*this) : 0.0;
        return total - discount;
    }

    // Discount amount (unused parameter preserved from Java)
    double promotion(DiscountStrategy& /*order*/) {
        return promotion ? promotion(*this) : 0.0;
    }

private:
    const Customer& customer;
    const Cart& cart;
    Promotion promotion;
    double total;
};