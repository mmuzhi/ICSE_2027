#include <string>

class Thermostat {
private:
    double current_temperature;
    double target_temperature;
    std::string mode;

public:
    Thermostat(double current_temp, double target_temp, std::string mode) 
        : current_temperature(current_temp), target_temperature(target_temp), mode(mode) {}

    double get_target_temperature() {
        return target_temperature;
    }

    void set_target_temperature(double temperature) {
        target_temperature = temperature;
    }

    std::string get_mode() {
        return mode;
    }

    bool set_mode(std::string new_mode) {
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
                return true;
            } else {
                auto_set_mode();
                return false;
            }
        } else {
            if (mode == "heat") {
                return true;
            } else {
                auto_set_mode();
                return false;
            }
        }
    }

    int simulate_operation() {
        auto_set_mode();
        int use_time = 0;
        if (mode == "heat") {
            while (current_temperature < target_temperature) {
                current_temperature += 1.0;
                use_time++;
            }
        } else if (mode == "cool") {
            while (current_temperature > target_temperature) {
                current_temperature -= 1.0;
                use_time++;
            }
        }
        return use_time;
    }
};