#ifndef STOCK_PORTFOLIO_TRACKER_HPP
#define STOCK_PORTFOLIO_TRACKER_HPP

#include <vector>
#include <string>
#include <sstream>
#include <cmath>

class StockPortfolioTracker {
public:
    class Stock {
    private:
        std::string name;
        double price;
        int quantity;

        static int doubleCompare(double a, double b) {
            bool aNaN = std::isnan(a);
            bool bNaN = std::isnan(b);
            if (aNaN && bNaN) return 0;
            if (aNaN) return 1;
            if (bNaN) return -1;
            if (a < b) return -1;
            if (a > b) return 1;
            if (std::signbit(a) != std::signbit(b)) {
                return std::signbit(a) ? -1 : 1;
            }
            return 0;
        }

    public:
        Stock(const std::string& name, double price, int quantity)
            : name(name), price(price), quantity(quantity) {}

        const std::string& getName() const { return name; }
        double getPrice() const { return price; }
        int getQuantity() const { return quantity; }
        void setQuantity(int qty) { quantity = qty; }

        bool operator==(const Stock& other) const {
            return doubleCompare(price, other.price) == 0 &&
                   quantity == other.quantity &&
                   name == other.name;
        }

        std::string toString() const {
            std::ostringstream oss;
            oss << name << ": " << quantity << " shares at $" << price << " each";
            return oss.str();
        }
    };

private:
    double initialCashBalance;
    double cashBalance;
    std::vector<Stock> portfolio;

public:
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

    double getCashBalance() const { return cashBalance; }

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
};

#endif