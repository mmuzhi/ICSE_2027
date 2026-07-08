#include <string>

class Thermostat {
public:
    // Package-private in Java translates to public in C++ as there is no package equivalent
    double currentTemperature;

private:
    double targetTemperature;
    std::string mode;

public:
    Thermostat(double currentTemperature, double targetTemperature, const std::string& mode)
        : currentTemperature(currentTemperature), targetTemperature(targetTemperature), mode(mode) {}

    double getTargetTemperature() const {
        return targetTemperature;
    }

    void setTargetTemperature(double temperature) {
        this->targetTemperature = temperature;
    }

    std::string getMode() const {
        return mode;
    }

    bool setMode(const std::string& mode) {
        // Objects.equals in Java handles nulls; std::string cannot be null, so == is equivalent
        if (mode == "heat" || mode == "cool") {
            this->mode = mode;
            return true;
        } else {
            return false;
        }
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
                useTime += 1;
            }
        } else {
            while (currentTemperature > targetTemperature) {
                currentTemperature -= 1;
                useTime += 1;
            }
        }
        return useTime;
    }
};