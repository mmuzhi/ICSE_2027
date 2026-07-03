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
            this->mode = mode;
            return true;
        }
        return false;
    }

    void autoSetMode() {
        if (currentTemperature < targetTemperature) {
            this->mode = "heat";
        } else {
            this->mode = "cool";
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
        } else if (currentTemperature < targetTemperature) {
            if (mode == "heat") {
                return true;
            } else {
                autoSetMode();
                return false;
            }
        }
        return false;
    }

    int simulateOperation() {
        autoSetMode();
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