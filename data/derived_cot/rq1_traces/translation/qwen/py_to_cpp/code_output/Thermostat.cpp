#include <string>

class Thermostat {
private:
    float current_temperature;
    float target_temperature;
    std::string mode;

public:
    Thermostat(float current, float target, const std::string& mode) 
        : current_temperature(current), target_temperature(target), mode(mode) {}

    float get_target_temperature() const {
        return target_temperature;
    }

    void set_target_temperature(float temperature) {
        target_temperature = temperature;
    }

    std::string get_mode() const {
        return mode;
    }

    bool set_mode(const std::string& new_mode) {
        if (new_mode == "heat" || new_mode == "cool") {
            mode = new_mode;
            return true;
        }
        return false;
    }

    void auto_set_mode() {
        if (current_temperature < target_temperature) {
            mode = "heat";
        } else {
            mode = "cool";
        }
    }

    bool auto_check_conflict() {
        if (current_temperature > target_temperature) {
            if (mode == "cool") {
                auto_set_mode();
                return true;
            }
            return false;
        } else if (current_temperature < target_temperature) {
            if (mode == "heat") {
                auto_set_mode();
                return true;
            }
            return false;
        }
        return false;
    }

    int simulate_operation() {
        auto_set_mode();
        int use_time = 0;
        if (mode == "heat") {
            while (current_temperature < target_temperature) {
                current_temperature += 1.0f;
                use_time++;
            }
        } else if (mode == "cool") {
            while (current_temperature > target_temperature) {
                current_temperature -= 1.0f;
                use_time++;
            }
        }
        return use_time;
    }
};