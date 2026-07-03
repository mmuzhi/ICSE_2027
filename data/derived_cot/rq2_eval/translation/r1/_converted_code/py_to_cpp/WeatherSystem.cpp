#include <string>
#include <optional>
#include <unordered_map>
#include <stdexcept>
#include <utility>

struct WeatherInfo {
    std::string weather;
    double temperature;
    std::string temperature_units;
};

class WeatherSystem {
private:
    std::optional<double> temperature;
    std::optional<std::string> weather;
    std::string city;
    std::unordered_map<std::string, WeatherInfo> weather_list;

public:
    WeatherSystem(const std::string& city) : city(city), temperature(std::nullopt), weather(std::nullopt) {}

    std::optional<std::pair<double, std::string>> query(const std::unordered_map<std::string, WeatherInfo>& weather_list, const std::string& tmp_units = "celsius") {
        this->weather_list = weather_list;

        auto it = weather_list.find(city);
        if (it == weather_list.end()) {
            return std::nullopt;
        }

        const WeatherInfo& info = it->second;
        temperature = info.temperature;
        weather = info.weather;

        if (info.temperature_units != tmp_units) {
            if (tmp_units == "celsius") {
                double converted_temp = fahrenheit_to_celsius();
                return std::make_pair(converted_temp, *weather);
            } else if (tmp_units == "fahrenheit") {
                double converted_temp = celsius_to_fahrenheit();
                return std::make_pair(converted_temp, *weather);
            } else {
                throw std::invalid_argument("Unsupported temperature unit: " + tmp_units);
            }
        } else {
            return std::make_pair(*temperature, *weather);
        }
    }

    void set_city(const std::string& city) {
        this->city = city;
    }

    double celsius_to_fahrenheit() {
        return (*temperature * 9.0 / 5.0) + 32.0;
    }

    double fahrenheit_to_celsius() {
        return (*temperature - 32.0) * 5.0 / 9.0;
    }
};