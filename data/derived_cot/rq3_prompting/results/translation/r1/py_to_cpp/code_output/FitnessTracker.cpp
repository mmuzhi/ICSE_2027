#include <string>
#include <map>
#include <utility>

class FitnessTracker {
public:
    FitnessTracker(double height, double weight, int age, const std::string& sex)
        : height(height), weight(weight), age(age), sex(sex) {
        // Initialize BMI standard ranges to match Python list of dicts
        BMI_std[0]["male"] = std::make_pair(20.0, 25.0);
        BMI_std[1]["female"] = std::make_pair(19.0, 24.0);
    }

    double get_BMI() const {
        return weight / (height * height);
    }

    int condition_judge() const {
        double bmi = get_BMI();
        double low, high;
        if (sex == "male") {
            low = BMI_std.at(0).at("male").first;
            high = BMI_std.at(0).at("male").second;
        } else {
            low = BMI_std.at(1).at("female").first;
            high = BMI_std.at(1).at("female").second;
        }
        if (bmi > high) {
            return 1;   // too fat
        } else if (bmi < low) {
            return -1;  // too thin
        } else {
            return 0;   // normal
        }
    }

    double calculate_calorie_intake() const {
        double BMR;
        if (sex == "male") {
            BMR = 10.0 * weight + 6.25 * height - 5.0 * age + 5.0;
        } else {
            BMR = 10.0 * weight + 6.25 * height - 5.0 * age - 161.0;
        }
        int condition = condition_judge();
        double calorie_intake;
        if (condition == 1) {
            calorie_intake = BMR * 1.2;   // sedentary
        } else if (condition == -1) {
            calorie_intake = BMR * 1.6;   // active
        } else {
            calorie_intake = BMR * 1.4;   // moderate
        }
        return calorie_intake;
    }

private:
    double height;
    double weight;
    int age;
    std::string sex;
    // Structure mirroring Python's list of dicts: index -> sex -> (low, high)
    std::map<int, std::map<std::string, std::pair<double, double>>> BMI_std;
};