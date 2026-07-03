#include <unordered_map>
#include <string>
#include <variant>

struct WeatherInfo {
    std::string weather;
    double temperature;
    std::string temperature_units;
};

class WeatherSystem {
private:
    std::string city;
    double temperature;
    std::string weather;
    std::unordered_map<std::string, WeatherInfo> weather_list;

    bool set_weather(const std::string& city, const std::unordered_map<std::string, WeatherInfo>& weather_list) {
        auto it = weather_list.find(city);
        if (it == weather_list.end()) {
            return false;
        }
        this->weather_list = weather_list;
        this->temperature = it->second.temperature;
        this->weather = it->second.weather;
        return true;
    }

    double celsius_to_fahrenheit() {
        return (this->temperature * 9/5) + 32;
    }

    double fahrenheit_to_celsius() {
        return (this->temperature - 32) * 5/9;
    }

public:
    WeatherSystem(const std::string& city) : city(city), temperature(0.0), weather("") {}

    std::variant<bool, std::tuple<double, std::string>> query(const std::unordered_map<std::string, WeatherInfo>& weather_list, const std::string& tmp_units = "celsius") {
        if (!set_weather(city, weather_list)) {
            return false;
        }

        if (this->weather_list[city].temperature_units != tmp_units) {
            if (tmp_units == "celsius") {
                double converted = this->fahrenheit_to_celsius();
                return std::make_tuple(converted, this->weather);
            } else if (tmp_units == "fahrenheit") {
                double converted = this->celsius_to_fahrenheit();
                return std::make_tuple(converted, this->weather);
            }
        } else {
            return std::make_tuple(this->temperature, this->weather);
        }
    }

    void set_city(const std::string& city) {
        this->city = city;
    }

    double celsius_to_fahrenheit() {
        return (this->temperature * 9/5) + 32;
    }

    double fahrenheit_to_celsius() {
        return (this->temperature - 32) * 5/9;
    }
};