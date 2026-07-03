#include <string>
#include <map>
#include <variant>
#include <optional>
#include <utility>

class WeatherSystem {
public:
    std::optional<double> temperature;
    std::optional<std::string> weather;
    std::string city;
    std::map<std::string, std::map<std::string, std::variant<std::string, double>>> weather_list;

    WeatherSystem(const std::string& city)
        : temperature(std::nullopt), weather(std::nullopt), city(city), weather_list() {}

    std::optional<std::pair<double, std::string>> query(
        const std::map<std::string, std::map<std::string, std::variant<std::string, double>>>& wl,
        const std::string& tmp_units = "celsius")
    {
        weather_list = wl;
        if (weather_list.find(city) == weather_list.end()) {
            return std::nullopt;
        }
        temperature = std::get<double>(weather_list.at(city).at("temperature"));
        weather = std::get<std::string>(weather_list.at(city).at("weather"));

        if (std::get<std::string>(weather_list.at(city).at("temperature units")) != tmp_units) {
            if (tmp_units == "celsius") {
                return std::make_pair(fahrenheit_to_celsius(), weather.value());
            } else if (tmp_units == "fahrenheit") {
                return std::make_pair(celsius_to_fahrenheit(), weather.value());
            }
            return std::nullopt;
        }
        return std::make_pair(temperature.value(), weather.value());
    }

    void set_city(const std::string& c) {
        city = c;
    }

    double celsius_to_fahrenheit() {
        return (temperature.value() * 9.0 / 5.0) + 32.0;
    }

    double fahrenheit_to_celsius() {
        return (temperature.value() - 32.0) * 5.0 / 9.0;
    }
};