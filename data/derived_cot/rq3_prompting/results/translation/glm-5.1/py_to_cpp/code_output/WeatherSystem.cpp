#include <string>
#include <map>
#include <optional>
#include <utility>

struct CityWeather {
    std::string weather;
    double temperature;
    std::string temperature_units;
};

class WeatherSystem {
public:
    std::optional<double> temperature;
    std::optional<std::string> weather;
    std::string city;
    std::map<std::string, CityWeather> weather_list;

    WeatherSystem(const std::string& city)
        : temperature(std::nullopt), weather(std::nullopt), city(city), weather_list({}) {}

    std::optional<std::pair<double, std::string>> query(
        const std::map<std::string, CityWeather>& wl,
        const std::string& tmp_units = "celsius")
    {
        weather_list = wl;
        auto it = weather_list.find(city);
        if (it == weather_list.end()) {
            return std::nullopt;
        }
        temperature = it->second.temperature;
        weather = it->second.weather;
        if (it->second.temperature_units != tmp_units) {
            if (tmp_units == "celsius") {
                return std::make_pair(fahrenheit_to_celsius(), *weather);
            } else if (tmp_units == "fahrenheit") {
                return std::make_pair(celsius_to_fahrenheit(), *weather);
            }
            return std::nullopt;
        }
        return std::make_pair(*temperature, *weather);
    }

    void set_city(const std::string& c) {
        city = c;
    }

    double celsius_to_fahrenheit() {
        return (*temperature * 9.0 / 5.0) + 32.0;
    }

    double fahrenheit_to_celsius() {
        return (*temperature - 32.0) * 5.0 / 9.0;
    }
};