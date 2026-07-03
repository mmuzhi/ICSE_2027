#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>

struct WeatherInfo {
    float temperature;
    std::string weather;
    std::string temperature_units;
};

class WeatherSystem {
private:
    std::string city;
    float temperature;
    std::string weather;
    std::unordered_map<std::string, WeatherInfo> weather_list;

    float celsius_to_fahrenheit() const {
        return (temperature * 9.0f / 5.0f) + 32.0f;
    }

    float fahrenheit_to_celsius() const {
        return (temperature - 32.0f) * 5.0f / 9.0f;
    }

public:
    WeatherSystem(const std::string& city) : city(city), temperature(0.0f), weather(""), weather_list() {}

    bool query(const std::unordered_map<std::string, WeatherInfo>& weather_list, const std::string& tmp_units = "celsius") {
        this->weather_list = weather_list;
        auto it = weather_list.find(city);
        if (it == weather_list.end()) {
            return false;
        }
        const WeatherInfo& info = it->second;
        temperature = info.temperature;
        weather = info.weather;

        if (info.temperature_units != tmp_units) {
            if (tmp_units == "celsius") {
                return std::make_pair(fahrenheit_to_celsius(), weather);
            } else if (tmp_units == "fahrenheit") {
                return std::make_pair(celsius_to_fahrenheit(), weather);
            }
        }
        return std::make_pair(temperature, weather);
    }

    void set_city(const std::string& city) {
        this->city = city;
    }

    float celsius_to_fahrenheit() const {
        return (temperature * 9.0f / 5.0f) + 32.0f;
    }

    float fahrenheit_to_celsius() const {
        return (temperature - 32.0f) * 5.0f / 9.0f;
    }
};