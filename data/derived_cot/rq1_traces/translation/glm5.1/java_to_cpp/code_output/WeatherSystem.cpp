#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <utility>

namespace org::example {

class WeatherSystem {
private:
    double temperature = 0.0;
    std::string weather;
    std::string city;
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList;

public:
    explicit WeatherSystem(std::string city) : city(std::move(city)) {}

    void setCity(std::string city) {
        this->city = std::move(city);
    }

    std::string getCity() const {
        return this->city;
    }

    void setTemperature(double temperature) {
        this->temperature = temperature;
    }

    double celsiusToFahrenheit() const {
        return (this->temperature * 9.0 / 5.0) + 32.0;
    }

    double fahrenheitToCelsius() const {
        return (this->temperature - 32.0) * 5.0 / 9.0;
    }

    std::vector<std::any> query(const std::unordered_map<std::string, std::unordered_map<std::string, std::any>>& weatherList, const std::string& tmpUnits) {
        this->weatherList = weatherList; // Copy the map into the member variable
        
        if (this->weatherList.find(this->city) == this->weatherList.end()) {
            return {false}; // Equivalent to new Object[]{false}
        }

        const auto& cityWeather = this->weatherList.at(this->city);
        
        // std::any_cast will throw std::bad_any_cast if the key doesn't exist or type mismatches,
        // which is behaviorally equivalent to Java's NullPointerException / ClassCastException here.
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

        return {this->temperature, this->weather}; // Equivalent to new Object[]{this.temperature, this.weather}
    }
};

} // namespace org::example