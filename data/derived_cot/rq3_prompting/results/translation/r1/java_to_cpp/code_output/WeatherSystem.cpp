#include <unordered_map>
#include <string>
#include <vector>
#include <any>
#include <optional>
#include <stdexcept>

class WeatherSystem {
private:
    std::optional<double> temperature;
    std::string weather;
    std::string city;
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList;

public:
    WeatherSystem(const std::string& city)
        : city(city), weatherList() {}

    void setCity(const std::string& city) {
        this->city = city;
    }

    std::string getCity() const {
        return this->city;
    }

    void setTemperature(std::optional<double> temperature) {
        this->temperature = temperature;
    }

    double celsiusToFahrenheit() {
        return (temperature.value() * 9.0 / 5.0) + 32.0;
    }

    double fahrenheitToCelsius() {
        return (temperature.value() - 32.0) * 5.0 / 9.0;
    }

    std::vector<std::any> query(
        const std::unordered_map<std::string, std::unordered_map<std::string, std::any>>& weatherList,
        const std::string& tmpUnits) {
        this->weatherList = weatherList;
        if (this->weatherList.find(city) == this->weatherList.end()) {
            return {std::any(false)};
        }

        const auto& cityWeather = this->weatherList.at(city);
        this->temperature = std::any_cast<double>(cityWeather.at("temperature"));
        this->weather = std::any_cast<std::string>(cityWeather.at("weather"));
        std::string currentUnits = std::any_cast<std::string>(cityWeather.at("temperature units"));

        if (currentUnits != tmpUnits) {
            if (tmpUnits == "celsius") {
                this->temperature = fahrenheitToCelsius();
            } else if (tmpUnits == "fahrenheit") {
                this->temperature = celsiusToFahrenheit();
            }
        }

        return {std::any(temperature.value()), std::any(weather)};
    }
};