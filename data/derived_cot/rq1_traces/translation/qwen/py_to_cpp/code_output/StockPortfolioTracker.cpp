#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility> // for std::pair

struct Stock {
    std::string name;
    double price;
    int quantity;
};

class StockPortfolioTracker {
private:
    std::vector<Stock> portfolio;
    double cash_balance;

    auto find_stock(const std::string& name) {
        return std::find_if(portfolio.begin(), portfolio.end(), [name](const Stock& s) {
            return s.name == name;
        });
    }

public:
    StockPortfolioTracker(double cash_balance) : cash_balance(cash_balance) {}

    void add_stock(const Stock& stock) {
        auto it = find_stock(stock.name);
        if (it != portfolio.end()) {
            it->quantity += stock.quantity;
            return;
        }
        portfolio.push_back(stock);
    }

    bool remove_stock(const Stock& stock) {
        auto it = find_stock(stock.name);
        if (it == portfolio.end()) {
            return false;
        }

        if (it->quantity >= stock.quantity) {
            it->quantity -= stock.quantity;
            if (it->quantity == 0) {
                portfolio.erase(it);
            }
            return true;
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

    std::pair<double, std::vector<std::map<std::string, double>>> get_portfolio_summary() {
        std::vector<std::map<std::string, double>> summary;
        for (const auto& stock : portfolio) {
            double value = stock.price * stock.quantity;
            std::map<std::string, double> stock_summary;
            stock_summary["name"] = stock.name;
            stock_summary["value"] = value;
            summary.push_back(stock_summary);
        }
        double portfolio_value = calculate_portfolio_value();
        return std::make_pair(portfolio_value, summary);
    }

    double get_stock_value(const Stock& stock) {
        return stock.price * stock.quantity;
    }
};