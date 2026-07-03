#include <unordered_map>
#include <string>
#include <any>
#include <vector>

class WeatherSystem {
private:
    double temperature;
    std::string weather;
    std::string city;
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList;

public:
    WeatherSystem(std::string city) : city(city) {}

    void setCity(std::string city) {
        this->city = city;
    }

    std::string getCity() {
        return this->city;
    }

    void setTemperature(double temperature) {
        this->temperature = temperature;
    }

    double celsiusToFahrenheit() {
        return (this->temperature * 9 / 5) + 32;
    }

    double fahrenheitToCelsius() {
        return (this->temperature - 32) * 5 / 9;
    }

    std::vector<std::any> query(std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList, std::string tmpUnits) {
        this->weatherList = weatherList;
        if (this->weatherList.find(this->city) == this->weatherList.end()) {
            return {false};
        }

        auto cityWeather = this->weatherList[this->city];
        this->temperature = std::any_cast<double>(cityWeather["temperature"]);
        this->weather = std::any_cast<std::string>(cityWeather["weather"]);
        std::string currentUnits = std::any_cast<std::string>(cityWeather["temperature units"]);

        if (currentUnits != tmpUnits) {
            if (tmpUnits == "celsius") {
                this->temperature = fahrenheitToCelsius();
            } else if (tmpUnits == "fahrenheit") {
                this->temperature = celsiusToFahrenheit();
            }
        }

        return {this->temperature, this->weather};
    }
};