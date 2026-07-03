#include <vector>
#include <string>
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
    StockPortfolioTracker(double initial_cash) : cash_balance(initial_cash) {}

    void add_stock(const Stock& stock) {
        for (auto& s : portfolio) {
            if (s.name == stock.name) {
                s.quantity += stock.quantity;
                return;
            }
        }
        portfolio.push_back(stock);
    }

    bool remove_stock(const Stock& stock) {
        for (auto it = portfolio.begin(); it != portfolio.end(); ++it) {
            if (it->name == stock.name) {
                if (it->quantity >= stock.quantity) {
                    it->quantity -= stock.quantity;
                    if (it->quantity == 0) {
                        portfolio.erase(it);
                    }
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        return false;
    }

    bool buy_stock(const Stock& stock) {
        double total_cost = stock.price * stock.quantity;
        if (total_cost > cash_balance) {
            return false;
        }
        add_stock(stock);
        cash_balance -= total_cost;
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
        double total_value = cash_balance;
        for (const auto& stock : portfolio) {
            total_value += stock.price * stock.quantity;
        }
        return total_value;
    }

    std::pair<double, std::vector<StockSummary>> get_portfolio_summary() const {
        std::vector<StockSummary> summary;
        for (const auto& stock : portfolio) {
            double value = stock.price * stock.quantity;
            summary.push_back({stock.name, value});
        }
        double total_value = calculate_portfolio_value();
        return std::make_pair(total_value, summary);
    }

    double get_stock_value(const Stock& stock) const {
        return stock.price * stock.quantity;
    }
};