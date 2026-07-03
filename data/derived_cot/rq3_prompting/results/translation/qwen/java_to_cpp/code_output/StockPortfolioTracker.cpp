#include <vector>
#include <string>
#include <iostream>

class StockPortfolioTracker {
private:
    double initialCashBalance;
    double cashBalance;
    std::vector<Stock> portfolio;

    class Stock {
    private:
        const std::string name;
        const double price;
        int quantity;

    public:
        Stock(const std::string& name, double price, int quantity)
            : name(name), price(price), quantity(quantity) {}

        const std::string& getName() const { return name; }
        double getPrice() const { return price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int newQuantity) { quantity = newQuantity; }

        bool operator==(const Stock& other) const {
            return name == other.name && price == other.price;
        }
    };

public:
    explicit StockPortfolioTracker(double initialCashBalance)
        : initialCashBalance(initialCashBalance), cashBalance(initialCashBalance) {}

    void addStock(const Stock& stock) {
        for (auto& s : portfolio) {
            if (s == stock) {
                s.quantity += stock.quantity;
                return;
            }
        }
        portfolio.push_back(stock);
    }

    bool removeStock(const Stock& stock) {
        for (auto it = portfolio.begin(); it != portfolio.end(); ++it) {
            if (*it == stock) {
                if (it->quantity >= stock.quantity) {
                    it->quantity -= stock.quantity;
                    if (it->quantity == 0) {
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

    double getCashBalance() const { return cashBalance; }

    double calculatePortfolioValue() const {
        double totalValue = 0.0;
        for (const auto& stock : portfolio) {
            totalValue += stock.getPrice() * stock.getQuantity();
        }
        return totalValue;
    }

    std::string getPortfolioSummary() const {
        std::string summary;
        for (const auto& stock : portfolio) {
            summary += stock.toString() + '\n';
        }
        summary += "Total Value: $" + std::to_string(calculatePortfolioValue()) + '\n';
        return summary;
    }
};