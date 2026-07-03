#include <string>

class Thermostat {
private:
    float current_temperature;
    float target_temperature;
    std::string mode;

public:
    Thermostat(float current_temperature, float target_temperature, const std::string& mode)
        : current_temperature(current_temperature), target_temperature(target_temperature), mode(mode) {}

    float get_target_temperature() const {
        return target_temperature;
    }

    void set_target_temperature(float temperature) {
        target_temperature = temperature;
    }

    std::string get_mode() const {
        return mode;
    }

    bool set_mode(const std::string& mode) {
        if (mode == "heat" || mode == "cool") {
            this->mode = mode;
            return true;
        } else {
            return false;
        }
    }

    void auto_set_mode() {
        if (current_temperature < target_temperature) {
            mode = "heat";
        } else {
            mode = "cool";
        }
    }

    bool auto_check_conflict() {
        bool result;
        if (current_temperature > target_temperature) {
            if (mode == "cool") {
                result = true;
            } else {
                auto_set_mode();
                result = false;
            }
        } else {
            if (mode == "heat") {
                result = true;
            } else {
                auto_set_mode();
                result = false;
            }
        }
        return result;
    }

    int simulate_operation() {
        auto_set_mode();
        int use_time = 0;
        if (mode == "heat") {
            while (current_temperature < target_temperature) {
                current_temperature += 1.0f;
                use_time++;
            }
        } else {
            while (current_temperature > target_temperature) {
                current_temperature -= 1.0f;
                use_time++;
            }
        }
        return use_time;
    }
};