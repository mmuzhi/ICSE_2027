#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

class CurrencyConverter {
private:
    std::unordered_map<std::string, double> rates;
    std::vector<std::string> currencyOrder;  // preserves insertion order

    // Helper to add a rate and track order
    void addRate(const std::string& currency, double rate) {
        rates[currency] = rate;
        currencyOrder.push_back(currency);
    }

public:
    CurrencyConverter() {
        addRate("USD", 1.0);
        addRate("EUR", 0.85);
        addRate("GBP", 0.72);
        addRate("JPY", 110.15);
        addRate("CAD", 1.23);
        addRate("AUD", 1.34);
        addRate("CNY", 6.40);
    }

    std::optional<double> convert(double amount,
                                  const std::string& from_currency,
                                  const std::string& to_currency) {
        if (from_currency == to_currency) {
            return amount;
        }

        auto it_from = rates.find(from_currency);
        auto it_to   = rates.find(to_currency);
        if (it_from == rates.end() || it_to == rates.end()) {
            return std::nullopt;   // equivalent to Python's False
        }

        double from_rate = it_from->second;
        double to_rate   = it_to->second;
        return (amount / from_rate) * to_rate;
    }

    std::vector<std::string> get_supported_currencies() const {
        return currencyOrder;
    }

    bool add_currency_rate(const std::string& currency, double rate) {
        if (rates.find(currency) != rates.end()) {
            return false;   // failure
        }
        rates[currency] = rate;
        currencyOrder.push_back(currency);
        return true;        // success (Python returns None, but we use true)
    }

    bool update_currency_rate(const std::string& currency, double new_rate) {
        auto it = rates.find(currency);
        if (it == rates.end()) {
            return false;   // failure
        }
        it->second = new_rate;
        return true;        // success
    }
};