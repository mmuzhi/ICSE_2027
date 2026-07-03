#include <vector>
#include <string>
#include <tuple>

struct Stock {
    std::string name;
    double price;
    int quantity;
};

struct PortfolioSummaryItem {
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
            Stock& s = *it;
            if (s.name == stock.name && s.quantity >= stock.quantity) {
                s.quantity -= stock.quantity;
                if (s.quantity == 0) {
                    portfolio.erase(it);
                }
                return true;
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

    double calculate_portfolio_value() {
        double total_value = cash_balance;
        for (const auto& stock : portfolio) {
            total_value += stock.price * stock.quantity;
        }
        return total_value;
    }

    std::tuple<double, std::vector<PortfolioSummaryItem>> get_portfolio_summary() {
        double portfolio_value = calculate_portfolio_value();
        std::vector<PortfolioSummaryItem> summary;
        for (const auto& stock : portfolio) {
            double value = stock.price * stock.quantity;
            summary.push_back({stock.name, value});
        }
        return std::make_tuple(portfolio_value, summary);
    }

    double get_stock_value(const Stock& stock) const {
        return stock.price * stock.quantity;
    }
};