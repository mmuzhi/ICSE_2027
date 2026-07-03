#include <string>
#include <unordered_map>
#include <optional>
#include <utility>

struct CityWeather {
    std::string weather;
    double temperature;
    std::string temperatureUnits;
};

class WeatherSystem {
public:
    // Constructor
    WeatherSystem(const std::string& city) : city(city) {}

    // Query weather information for the city, with optional unit conversion.
    // Returns std::nullopt if city is not found; otherwise a pair (temperature, weather).
    std::optional<std::pair<double, std::string>> query(
        const std::unordered_map<std::string, CityWeather>& weather_list,
        const std::string& tmp_units = "celsius")
    {
        this->weather_list = weather_list;

        auto it = this->weather_list.find(city);
        if (it == this->weather_list.end()) {
            return std::nullopt;
        }

        const CityWeather& data = it->second;
        this->temperature = data.temperature;
        this->weather = data.weather;

        if (data.temperatureUnits != tmp_units) {
            if (tmp_units == "celsius") {
                return std::make_pair(fahrenheit_to_celsius(), this->weather);
            } else if (tmp_units == "fahrenheit") {
                return std::make_pair(celsius_to_fahrenheit(), this->weather);
            }
        }
        // No conversion needed
        return std::make_pair(this->temperature.value(), this->weather);
    }

    // Set the city name
    void set_city(const std::string& new_city) {
        city = new_city;
    }

    // Convert current temperature (in Celsius) to Fahrenheit
    double celsius_to_fahrenheit() const {
        return (temperature.value() * 9.0 / 5.0) + 32.0;
    }

    // Convert current temperature (in Fahrenheit) to Celsius
    double fahrenheit_to_celsius() const {
        return (temperature.value() - 32.0) * 5.0 / 9.0;
    }

private:
    std::optional<double> temperature;           // None initially
    std::string weather;                         // Set after query
    std::string city;
    std::unordered_map<std::string, CityWeather> weather_list;
};