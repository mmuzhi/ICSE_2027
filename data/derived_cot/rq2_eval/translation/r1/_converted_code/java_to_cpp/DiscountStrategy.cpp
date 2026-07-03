#include <functional>
#include <vector>
#include <string>
#include <initializer_list>

class DiscountStrategy {
public:
    class Customer {
    private:
        std::string name;
        int fidelity;
    public:
        Customer(std::string name, int fidelity) : name(name), fidelity(fidelity) {}
        std::string getName() const { return name; }
        int fidelity_discount() const { return fidelity; }
    };

    class Product {
    private:
        std::string name;
        int quantity;
        double price;
    public:
        Product(std::string name, int quantity, double price) 
            : name(name), quantity(quantity), price(price) {}
        std::string getName() const { return name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
    };

    class Cart {
    private:
        std::vector<Product> products;
    public:
        Cart(std::initializer_list<Product> items) : products(items) {}
        void addProduct(const Product& product) {
            products.push_back(product);
        }
        const std::vector<Product>& getProducts() const { return products; }
        std::vector<Product>& getProducts() { return products; }
    };

    using Promotion = std::function<double(DiscountStrategy*)>;

    static inline Promotion FIDELITY_PROMO = [](DiscountStrategy* order) -> double {
        return (order->customer.fidelity_discount() >= 1000) ? (order->total * 0.05) : 0.0;
    };

    static inline Promotion BULK_ITEM_PROMO = [](DiscountStrategy* order) -> double {
        double discount = 0.0;
        for (const Product& item : order->cart.getProducts()) {
            if (item.getQuantity() >= 20) {
                discount += item.getQuantity() * item.getPrice() * 0.1;
            }
        }
        return discount;
    };

    static inline Promotion LARGE_ORDER_PROMO = [](DiscountStrategy* order) -> double {
        return (order->cart.getProducts().size() >= 10) ? (order->total * 0.07) : 0.0;
    };

private:
    Customer customer;
    Cart& cart;
    Promotion promotion;
    double total;

public:
    DiscountStrategy(Customer customer, Cart& cart, Promotion promotion)
        : customer(customer), cart(cart), promotion(promotion) {
        this->total = total();
    }

    double total() {
        double sum = 0.0;
        for (const Product& p : cart.getProducts()) {
            sum += p.getQuantity() * p.getPrice();
        }
        total = sum;
        return total;
    }

    double due() {
        double discount = promotion ? promotion(this) : 0.0;
        return total - discount;
    }

    double promotion(DiscountStrategy* order) {
        return promotion ? promotion(this) : 0.0;
    }
};