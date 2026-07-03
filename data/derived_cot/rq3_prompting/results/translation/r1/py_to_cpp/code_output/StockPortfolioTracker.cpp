#include <vector>
#include <string>
#include <algorithm>
#include <utility>

struct Stock {
    std::string name;
    double price;
    int quantity;
};

struct StockSummary {
    std::string name;
    double value;
};

class StockPortfolioTracker {
private:
    std::vector<Stock> portfolio;
    double cash_balance;

public:
    StockPortfolioTracker(double cash_balance) : cash_balance(cash_balance) {}

    void add_stock(const Stock& stock) {
        auto it = std::find_if(portfolio.begin(), portfolio.end(),
                               [&](const Stock& s) { return s.name == stock.name; });
        if (it != portfolio.end()) {
            it->quantity += stock.quantity;
        } else {
            portfolio.push_back(stock);
        }
    }

    bool remove_stock(const Stock& stock) {
        auto it = std::find_if(portfolio.begin(), portfolio.end(),
                               [&](const Stock& s) { return s.name == stock.name; });
        if (it != portfolio.end() && it->quantity >= stock.quantity) {
            it->quantity -= stock.quantity;
            if (it->quantity == 0) {
                portfolio.erase(it);
            }
            return true;
        }
        return false;
    }

    bool buy_stock(const Stock& stock) {
        double cost = stock.price * stock.quantity;
        if (cost > cash_balance) {
            return false;
        }
        add_stock(stock);
        cash_balance -= cost;
        return true;
    }

    bool sell_stock(const Stock& stock) {
        if (!remove_stock(stock)) {
            return false;
        }
        cash_balance += stock.price * stock.quantity;
        return true;
    }

    double calculate_portfolio_value() const {
        double total = cash_balance;
        for (const auto& s : portfolio) {
            total += s.price * s.quantity;
        }
        return total;
    }

    std::pair<double, std::vector<StockSummary>> get_portfolio_summary() const {
        std::vector<StockSummary> summary;
        for (const auto& s : portfolio) {
            double value = get_stock_value(s);
            summary.push_back({s.name, value});
        }
        double total = calculate_portfolio_value();
        return {total, summary};
    }

    double get_stock_value(const Stock& stock) const {
        return stock.price * stock.quantity;
    }
};