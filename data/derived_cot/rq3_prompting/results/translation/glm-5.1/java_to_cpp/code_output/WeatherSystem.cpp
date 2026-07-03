#pragma once
#include <string>
#include <unordered_map>
#include <any>
#include <vector>
#include <optional>

class WeatherSystem {
private:
    std::optional<double> temperature;
    std::string weather;
    std::string city;
    std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList;

public:
    WeatherSystem(const std::string& city) : city(city) {}

    void setCity(const std::string& city) {
        this->city = city;
    }

    std::string getCity() const {
        return this->city;
    }

    void setTemperature(double temperature) {
        this->temperature = temperature;
    }

    double celsiusToFahrenheit() {
        return (this->temperature.value() * 9 / 5) + 32;
    }

    double fahrenheitToCelsius() {
        return (this->temperature.value() - 32) * 5 / 9;
    }

    std::vector<std::any> query(std::unordered_map<std::string, std::unordered_map<std::string, std::any>> weatherList, const std::string& tmpUnits) {
        this->weatherList = weatherList;
        if (this->weatherList.find(this->city) == this->weatherList.end()) {
            return {false};
        }

        auto& cityWeather = this->weatherList.at(this->city);
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

        return {this->temperature.value(), this->weather};
    }
};