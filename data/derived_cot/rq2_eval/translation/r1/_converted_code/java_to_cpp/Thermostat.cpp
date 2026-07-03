#include <string>

class Thermostat {
public:
    double currentTemperature;
    
    Thermostat(double currentTemperature, double targetTemperature, std::string mode) 
        : currentTemperature(currentTemperature), 
          targetTemperature(targetTemperature), 
          mode(mode) {}

    double get_target_temperature() const {
        return targetTemperature;
    }

    void set_target_temperature(double temperature) {
        targetTemperature = temperature;
    }

    std::string get_mode() const {
        return mode;
    }

    bool set_mode(std::string m) {
        if (m == "heat" || m == "cool") {
            mode = m;
            return true;
        } else {
            return false;
        }
    }

    void auto_set_mode() {
        if (currentTemperature < targetTemperature) {
            mode = "heat";
        } else {
            mode = "cool";
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
        int useTime = 0;
        if (mode == "heat") {
            while (currentTemperature < targetTemperature) {
                currentTemperature += 1;
                useTime++;
            }
        } else {
            while (currentTemperature > targetTemperature) {
                currentTemperature -= 1;
                useTime++;
            }
        }
        return useTime;
    }

private:
    double targetTemperature;
    std::string mode;
};