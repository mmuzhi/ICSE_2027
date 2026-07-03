#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <any>

class WeatherSystem {
private:
    std::string city;
    double temperature;
    std::string weather;
    std::unordered_map<std::string, std::map<std::string, std::any>> weatherList;

public:
    WeatherSystem(std::string city) : city(city) {}

    void set_city(std::string city) {
        this->city = city;
    }

    std::string get_city() {
        return this->city;
    }

    void set_temperature(double temperature) {
        this->temperature = temperature;
    }

    double celsius_to_fahrenheit() {
        return (this->temperature * 9 / 5) + 32;
    }

    double fahrenheit_to_celsius() {
        return (this->temperature - 32) * 5 / 9;
    }

    std::vector<std::any> query(std::unordered_map<std::string, std::map<std::string, std::any>> weatherList, std::string tmpUnits) {
        this->weatherList = weatherList;
        if (!this->weatherList.count(this->city)) {
            return { false };
        }

        auto cityWeather = this->weatherList[this->city];
        this->temperature = std::any_cast<double>(cityWeather["temperature"]);
        this->weather = std::any_cast<std::string>(cityWeather["weather"]);
        std::string currentUnits = std::any_cast<std::string>(cityWeather["temperature units"]);

        if (currentUnits != tmpUnits) {
            if (tmpUnits == "celsius") {
                this->temperature = fahrenheit_to_celsius();
            } else if (tmpUnits == "fahrenheit") {
                this->temperature = celsius_to_fahrenheit();
            }
        }

        return { this->temperature, this->weather };
    }
};