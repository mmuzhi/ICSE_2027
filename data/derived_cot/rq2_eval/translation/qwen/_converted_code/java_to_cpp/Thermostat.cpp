#include <string>

class Thermostat {
public:
    double currentTemperature;
    double targetTemperature;
    std::string mode;

    Thermostat(double currentTemperature, double targetTemperature, std::string mode) {
        this->currentTemperature = currentTemperature;
        this->targetTemperature = targetTemperature;
        this->mode = mode;
    }

    double get_target_temperature() const {
        return targetTemperature;
    }

    void set_target_temperature(double temperature) {
        targetTemperature = temperature;
    }

    std::string get_mode() const {
        return mode;
    }

    bool set_mode(std::string mode) {
        if (mode == "heat" || mode == "cool") {
            this->mode = mode;
            return true;
        }
        return false;
    }

    void auto_set_mode() {
        if (currentTemperature < targetTemperature) {
            this->mode = "heat";
        } else {
            this->mode = "cool";
        }
    }

    bool auto_check_conflict() {
        if (currentTemperature > targetTemperature) {
            if (mode == "cool") {
                return true;
            } else {
                auto_set_mode();
                return false;
            }
        } else if (currentTemperature < targetTemperature) {
            if (mode == "heat") {
                return true;
            } else {
                auto_set_mode();
                return false;
            }
        }
        return false;
    }

    int simulate_operation() {
        auto_set_mode();
        int useTime = 0;
        if (mode == "heat") {
            while (currentTemperature < targetTemperature) {
                currentTemperature += 1.0;
                useTime += 1;
            }
        } else {
            while (currentTemperature > targetTemperature) {
                currentTemperature -= 1.0;
                useTime += 1;
            }
        }
        return useTime;
    }
};