#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

class CurrencyConverter {
private:
    std::map<std::string, double> rates;

public:
    CurrencyConverter() {
        rates = {
            {"USD", 1.0},
            {"EUR", 0.85},
            {"GBP", 0.72},
            {"JPY", 110.15},
            {"CAD", 1.23},
            {"AUD", 1.34},
            {"CNY", 6.40}
        };
    }

    double convert(double amount, const std::string& from_currency, const std::string& to_currency) {
        if (from_currency == to_currency) {
            return amount;
        }

        if (rates.find(from_currency) == rates.end() || rates.find(to_currency) == rates.end()) {
            return std::numeric_limits<double>::quiet_NaN();
        }

        double from_rate = rates[from_currency];
        double to_rate = rates[to_currency];

        double converted_amount = (amount / from_rate) * to_rate;
        return converted_amount;
    }

    std::vector<std::string> get_supported_currencies() {
        std::vector<std::string> currencies;
        for (const auto& pair : rates) {
            currencies.push_back(pair.first);
        }
        return currencies;
    }

    bool add_currency_rate(const std::string& currency, double rate) {
        if (rates.find(currency) != rates.end()) {
            return false;
        }
        rates[currency] = rate;
        return true;
    }

    bool update_currency_rate(const std::string& currency, double new_rate) {
        if (rates.find(currency) == rates.end()) {
            return false;
        }
        rates[currency] = new_rate;
        return true;
    }
};