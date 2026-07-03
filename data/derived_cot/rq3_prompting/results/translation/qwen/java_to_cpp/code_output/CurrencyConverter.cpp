#include <iostream>
#include <unordered_map>
#include <set>
#include <string>

class CurrencyConverter {
private:
    std::unordered_map<std::string, double> rates;
    std::set<std::string> supportedCurrencies;

    void updateSupportedCurrencies() {
        supportedCurrencies.clear();
        for (const auto& pair : rates) {
            supportedCurrencies.insert(pair.first);
        }
    }

public:
    CurrencyConverter() {
        rates["USD"] = 1.0;
        rates["EUR"] = 0.85;
        rates["GBP"] = 0.72;
        rates["JPY"] = 110.15;
        rates["CAD"] = 1.23;
        rates["AUD"] = 1.34;
        rates["CNY"] = 6.40;
        updateSupportedCurrencies();
    }

    double convert(double amount, std::string fromCurrency, std::string toCurrency) {
        if (fromCurrency == toCurrency) {
            return amount;
        }

        if (!rates.count(fromCurrency) || !rates.count(toCurrency)) {
            return -1.0;
        }

        double fromRate = rates.at(fromCurrency);
        double toRate = rates.at(toCurrency);
        return (amount / fromRate) * toRate;
    }

    std::set<std::string> getSupportedCurrencies() const {
        return supportedCurrencies;
    }

    bool addCurrencyRate(const std::string& currency, double rate) {
        if (rates.find(currency) != rates.end()) {
            return false;
        }
        rates[currency] = rate;
        updateSupportedCurrencies();
        return true;
    }

    bool updateCurrencyRate(const std::string& currency, double newRate) {
        if (rates.find(currency) == rates.end()) {
            return false;
        }
        rates[currency] = newRate;
        updateSupportedCurrencies();
        return true;
    }

    std::unordered_map<std::string, double> getRates() const {
        return rates;
    }
};