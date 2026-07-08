#ifndef STOCK_PORTFOLIO_TRACKER_H
#define STOCK_PORTFOLIO_TRACKER_H

#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstring>
#include <cstdint>

class StockPortfolioTracker {
public:
    class Stock {
    private:
        std::string name;
        double price;
        int quantity;

        static int doubleCompare(double a, double b) {
            if (std::isnan(a) || std::isnan(b)) {
                if (std::isnan(a) && std::isnan(b)) return 0;
                return std::isnan(a) ? 1 : -1;
            }
            if (a == b) {
                std::int64_t aBits = 0, bBits = 0;
                std::memcpy(&aBits, &a, sizeof(aBits));
                std::memcpy(&bBits, &b, sizeof(bBits));
                if (aBits == bBits) return 0;
                return (static_cast<std::uint64_t>(aBits) < static_cast<std::uint64_t>(bBits)) ? -1 : 1;
            }
            return (a < b) ? -1 : 1;
        }

        static int stringHashCode(const std::string& s) {
            int h = 0;
            for (unsigned char c : s) {
                h = 31 * h + static_cast<int>(c);
            }
            return h;
        }

        static int doubleHashCode(double d) {
            std::int64_t bits = 0;
            std::memcpy(&bits, &d, sizeof(bits));
            return static_cast<int>(bits ^ (static_cast<std::uint64_t>(bits) >> 32));
        }

    public:
        Stock(const std::string& name, double price, int quantity)
            : name(name), price(price), quantity(quantity) {}

        const std::string& getName() const {
            return name;
        }

        double getPrice() const {
            return price;
        }

        int getQuantity() const {
            return quantity;
        }

        void setQuantity(int qty) {
            quantity = qty;
        }

        bool equals(const Stock& other) const {
            if (this == &other) return true;
            return doubleCompare(other.price, price) == 0 &&
                   quantity == other.quantity &&
                   name == other.name;
        }

        int hashCode() const {
            int result = 1;
            result = 31 * result + stringHashCode(name);
            result = 31 * result + doubleHashCode(price);
            result = 31 * result + quantity;
            return result;
        }

        std::string toString() const {
            return name + ": " + std::to_string(quantity) + " shares at $" + formatDouble(price) + " each";
        }

        static std::string formatDouble(double d) {
            if (std::isnan(d)) return "NaN";
            if (std::isinf(d)) return d > 0 ? "Infinity" : "-Infinity";
            std::ostringstream oss;
            oss << d;
            std::string result = oss.str();
            if (result.find('.') == std::string::npos &&
                result.find('e') == std::string::npos &&
                result.find('E') == std::string::npos) {
                result += ".0";
            }
            return result;
        }
    };

private:
    double initialCashBalance;
    double cashBalance;
    std::vector<Stock> portfolio;

public:
    StockPortfolioTracker(double initialCashBalance)
        : initialCashBalance(initialCashBalance),
          cashBalance(initialCashBalance),
          portfolio() {}

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
        summary << "Total Value: $" << Stock::formatDouble(calculatePortfolioValue()) << "\n";
        return summary.str();
    }
};

#endif // STOCK_PORTFOLIO_TRACKER_H