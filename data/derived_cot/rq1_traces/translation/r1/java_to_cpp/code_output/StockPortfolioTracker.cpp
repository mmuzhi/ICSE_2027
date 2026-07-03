#include <vector>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdint>
#include <sstream>
#include <iostream>

class StockPortfolioTracker {
public:
    class Stock {
    public:
        Stock(const std::string& name, double price, int quantity)
            : name(name), price(price), quantity(quantity) {}

        const std::string& getName() const { return name; }
        double getPrice() const { return price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int newQuantity) { quantity = newQuantity; }

        bool operator==(const Stock& other) const {
            return (name == other.name) &&
                   (doubleToLongBits(price) == doubleToLongBits(other.price)) &&
                   (quantity == other.quantity);
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << name << ": " << quantity << " shares at $" << price << " each";
            return oss.str();
        }

    private:
        std::string name;
        double price;
        int quantity;

        static uint64_t doubleToLongBits(double x) {
            if (std::isnan(x)) {
                return 0x7FF8000000000000;
            }
            uint64_t bits;
            std::memcpy(&bits, &x, sizeof(double));
            return bits;
        }
    };

    StockPortfolioTracker(double initialCashBalance)
        : initialCashBalance(initialCashBalance), cashBalance(initialCashBalance) {}

    void addStock(const Stock& stock) {
        for (auto& s : portfolio) {
            if (s.getName() == stock.getName() && s.getPrice() == stock.getPrice()) {
                s.setQuantity(s.getQuantity() + stock.getQuantity());
                return;
            }
        }
        portfolio.push_back(stock);
    }

    bool removeStock(const Stock& stock) {
        for (auto it = portfolio.begin(); it != portfolio.end(); ++it) {
            if (it->getName() == stock.getName() && it->getPrice() == stock.getPrice()) {
                if (it->getQuantity() >= stock.getQuantity()) {
                    it->setQuantity(it->getQuantity() - stock.getQuantity());
                    if (it->getQuantity() == 0) {
                        portfolio.erase(it);
                    }
                    return true;
                }
            }
        }
        return false;
    }

    bool buyStock(const Stock& stock) {
        double cost = stock.getPrice() * stock.getQuantity();
        if (cashBalance >= cost) {
            addStock(stock);
            cashBalance -= cost;
            return true;
        }
        return false;
    }

    bool sellStock(const Stock& stock) {
        double revenue = stock.getPrice() * stock.getQuantity();
        if (removeStock(stock)) {
            cashBalance += revenue;
            return true;
        }
        return false;
    }

    std::vector<Stock> getPortfolio() const {
        return portfolio;
    }

    double getCashBalance() const {
        return cashBalance;
    }

    double calculatePortfolioValue() const {
        double totalValue = 0.0;
        for (const auto& stock : portfolio) {
            totalValue += stock.getPrice() * stock.getQuantity();
        }
        return totalValue;
    }

    std::string getPortfolioSummary() const {
        std::ostringstream summary;
        for (const auto& stock : portfolio) {
            summary << stock.toString() << "\n";
        }
        summary << "Total Value: $" << calculatePortfolioValue() << "\n";
        return summary.str();
    }

private:
    double initialCashBalance;
    double cashBalance;
    std::vector<Stock> portfolio;
};