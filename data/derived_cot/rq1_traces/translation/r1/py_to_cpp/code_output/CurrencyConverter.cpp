#include <vector>
#include <string>
#include <unordered_map>
#include <variant>

class CurrencyConverter {
public:
    enum class Status {
        Success,
        Failure
    };

    using ConvertResult = std::variant<double, bool>;

    CurrencyConverter() {
        currency_order_ = {"USD", "EUR", "GBP", "JPY", "CAD", "AUD", "CNY"};
        rates_ = {
            {"USD", 1.0},
            {"EUR", 0.85},
            {"GBP", 0.72},
            {"JPY", 110.15},
            {"CAD", 1.23},
            {"AUD", 1.34},
            {"CNY", 6.40}
        };
    }

    ConvertResult convert(double amount, const std::string& from_currency, const std::string& to_currency) {
        if (from_currency == to_currency) {
            return amount;
        }

        if (rates_.find(from_currency) == rates_.end() || rates_.find(to_currency) == rates_.end()) {
            return false;
        }

        double from_rate = rates_[from_currency];
        double to_rate = rates_[to_currency];

        double converted_amount = (amount / from_rate) * to_rate;
        return converted_amount;
    }

    std::vector<std::string> get_supported_currencies() const {
        return currency_order_;
    }

    Status add_currency_rate(const std::string& currency, double rate) {
        if (rates_.find(currency) != rates_.end()) {
            return Status::Failure;
        }
        rates_[currency] = rate;
        currency_order_.push_back(currency);
        return Status::Success;
    }

    Status update_currency_rate(const std::string& currency, double new_rate) {
        if (rates_.find(currency) == rates_.end()) {
            return Status::Failure;
        }
        rates_[currency] = new_rate;
        return Status::Success;
    }

private:
    std::vector<std::string> currency_order_;
    std::unordered_map<std::string, double> rates_;
};