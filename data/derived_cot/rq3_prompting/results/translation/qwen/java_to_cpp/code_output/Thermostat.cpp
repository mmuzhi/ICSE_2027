#include <string>

class Thermostat {
public:
    double currentTemperature;
    double targetTemperature;
    std::string mode;

    Thermostat(double currentTemperature, double targetTemperature, std::string mode) 
        : currentTemperature(currentTemperature), targetTemperature(targetTemperature), mode(std::move(mode)) {}

    double getTargetTemperature() const {
        return targetTemperature;
    }

    void setTargetTemperature(double temperature) {
        targetTemperature = temperature;
    }

    std::string getMode() const {
        return mode;
    }

    bool setMode(std::string mode) {
        if (mode == "heat" || mode == "cool") {
            this->mode = std::move(mode);
            return true;
        }
        return false;
    }

    void autoSetMode() {
        if (currentTemperature < targetTemperature) {
            mode = "heat";
        } else {
            mode = "cool";
        }
    }

    bool autoCheckConflict() {
        if (currentTemperature > targetTemperature) {
            if (mode == "cool") {
                return true;
            } else {
                autoSetMode();
                return false;
            }
        } else {
            if (mode == "heat") {
                return true;
            } else {
                autoSetMode();
                return false;
            }
        }
    }

    int simulateOperation() {
        autoSetMode();
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
};