#include <any>
#include <map>
#include <string>
#include <vector>
#include <optional>
#include <stdexcept>

class NullPointerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "NullPointerException";
    }
};

class ClassCastException : public std::exception {
public:
    const char* what() const noexcept override {
        return "ClassCastException";
    }
};

class WeatherSystem {
private:
    std::optional<double> temperature;
    std::optional<std::string> weather;
    std::string city;
    std::map<std::string, std::map<std::string, std::any>>* weatherList;

public:
    WeatherSystem(std::string city) : city(city), weatherList(nullptr) {}

    void set_city(std::string city) {
        this->city = city;
    }

    std::string get_city() const {
        return this->city;
    }

    void set_temperature(std::optional<double> temperature) {
        this->temperature = temperature;
    }

    double celsius_to_fahrenheit() {
        if (!temperature.has_value()) {
            throw NullPointerException();
        }
        return (temperature.value() * 9.0 / 5.0) + 32.0;
    }

    double fahrenheit_to_celsius() {
        if (!temperature.has_value()) {
            throw NullPointerException();
        }
        return (temperature.value() - 32.0) * 5.0 / 9.0;
    }

    std::vector<std::any> query(std::map<std::string, std::map<std::string, std::any>>& weatherList, std::string tmpUnits) {
        this->weatherList = &weatherList;

        auto cityIt = weatherList.find(city);
        if (cityIt == weatherList.end()) {
            return { false };
        }

        auto& cityWeather = cityIt->second;

        std::optional<double> extractedTemp;
        std::optional<std::string> extractedWeather;
        std::optional<std::string> currentUnits;

        auto tempIt = cityWeather.find("temperature");
        if (tempIt != cityWeather.end()) {
            try {
                extractedTemp = std::any_cast<double>(tempIt->second);
            } catch (const std::bad_any_cast& e) {
                throw ClassCastException();
            }
        }

        auto weatherIt = cityWeather.find("weather");
        if (weatherIt != cityWeather.end()) {
            try {
                extractedWeather = std::any_cast<std::string>(weatherIt->second);
            } catch (const std::bad_any_cast& e) {
                throw ClassCastException();
            }
        }

        auto unitsIt = cityWeather.find("temperature units");
        if (unitsIt != cityWeather.end()) {
            try {
                currentUnits = std::any_cast<std::string>(unitsIt->second);
            } catch (const std::bad_any_cast& e) {
                throw ClassCastException();
            }
        }

        temperature = extractedTemp;
        weather = extractedWeather;

        if (currentUnits.has_value()) {
            if (currentUnits.value() != tmpUnits) {
                if (tmpUnits == "celsius") {
                    temperature = fahrenheit_to_celsius();
                } else if (tmpUnits == "fahrenheit") {
                    temperature = celsius_to_fahrenheit();
                }
            }
        } else {
            throw NullPointerException();
        }

        std::vector<std::any> result;
        if (temperature.has_value()) {
            result.push_back(temperature.value());
        } else {
            result.push_back(nullptr);
        }
        if (weather.has_value()) {
            result.push_back(weather.value());
        } else {
            result.push_back(nullptr);
        }
        return result;
    }
};