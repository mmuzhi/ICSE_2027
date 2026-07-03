#include <map>
#include <set>
#include <string>

class CurrencyConverter {
private:
    std::map<std::string, double> rates;
    std::set<std::string> supportedCurrencies;

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
        for (const auto& entry : rates) {
            supportedCurrencies.insert(entry.first);
        }
    }

    double convert(double amount, const std::string& fromCurrency, const std::string& toCurrency) {
        if (fromCurrency == toCurrency) {
            return amount;
        }

        if (rates.find(fromCurrency) == rates.end() || rates.find(toCurrency) == rates.end()) {
            return -1.0;
        }

        double fromRate = rates.at(fromCurrency);
        double toRate = rates.at(toCurrency);

        double convertedAmount = (amount / fromRate) * toRate;
        return convertedAmount;
    }

    std::set<std::string> getSupportedCurrencies() {
        return supportedCurrencies;
    }

    bool addCurrencyRate(const std::string& currency, double rate) {
        if (rates.find(currency) != rates.end()) {
            return false;
        }
        rates[currency] = rate;
        supportedCurrencies.insert(currency);
        return true;
    }

    bool updateCurrencyRate(const std::string& currency, double newRate) {
        if (rates.find(currency) == rates.end()) {
            return false;
        }
        rates[currency] = newRate;
        return true;
    }

    std::map<std::string, double>& getRates() {
        return rates;
    }
};