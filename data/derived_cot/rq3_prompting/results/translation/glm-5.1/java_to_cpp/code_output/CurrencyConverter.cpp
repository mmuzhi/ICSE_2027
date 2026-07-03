#include <unordered_map>
#include <unordered_set>
#include <string>

class CurrencyConverter {
private:
    std::unordered_map<std::string, double> rates;

public:
    CurrencyConverter() {
        rates["USD"] = 1.0;
        rates["EUR"] = 0.85;
        rates["GBP"] = 0.72;
        rates["JPY"] = 110.15;
        rates["CAD"] = 1.23;
        rates["AUD"] = 1.34;
        rates["CNY"] = 6.40;
    }

    double convert(double amount, const std::string& fromCurrency, const std::string& toCurrency) {
        if (fromCurrency == toCurrency) {
            return amount;
        }

        if (rates.find(fromCurrency) == rates.end() || rates.find(toCurrency) == rates.end()) {
            return -1;
        }

        double fromRate = rates[fromCurrency];
        double toRate = rates[toCurrency];

        double convertedAmount = (amount / fromRate) * toRate;
        return convertedAmount;
    }

    std::unordered_set<std::string> getSupportedCurrencies() {
        std::unordered_set<std::string> currencies;
        for (const auto& pair : rates) {
            currencies.insert(pair.first);
        }
        return currencies;
    }

    bool addCurrencyRate(const std::string& currency, double rate) {
        if (rates.find(currency) != rates.end()) {
            return false;
        }
        rates[currency] = rate;
        return true;
    }

    bool updateCurrencyRate(const std::string& currency, double newRate) {
        if (rates.find(currency) == rates.end()) {
            return false;
        }
        rates[currency] = newRate;
        return true;
    }

    std::unordered_map<std::string, double>& getRates() {
        return rates;
    }
};