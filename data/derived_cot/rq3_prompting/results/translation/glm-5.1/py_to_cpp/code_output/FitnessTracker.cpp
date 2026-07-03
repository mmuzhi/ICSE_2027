#include <string>
#include <vector>
#include <map>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    std::vector<std::map<std::string, std::vector<double>>> BMI_std;

public:
    FitnessTracker(double height, double weight, int age, std::string sex)
        : height(height), weight(weight), age(age), sex(sex) {
        BMI_std = {
            std::map<std::string, std::vector<double>>{{"male", {20.0, 25.0}}},
            std::map<std::string, std::vector<double>>{{"female", {19.0, 24.0}}}
        };
    }

    double get_BMI() {
        return weight / (height * height);
    }

    int condition_judge() {
        double BMI = get_BMI();
        std::vector<double> BMI_range;
        if (sex == "male") {
            BMI_range = BMI_std[0]["male"];
        } else {
            BMI_range = BMI_std[1]["female"];
        }
        if (BMI > BMI_range[1]) {
            return 1;
        } else if (BMI < BMI_range[0]) {
            return -1;
        } else {
            return 0;
        }
    }

    double calculate_calorie_intake() {
        double BMR;
        if (sex == "male") {
            BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        } else {
            BMR = 10 * weight + 6.25 * height - 5 * age - 161;
        }
        double calorie_intake;
        if (condition_judge() == 1) {
            calorie_intake = BMR * 1.2;
        } else if (condition_judge() == -1) {
            calorie_intake = BMR * 1.6;
        } else {
            calorie_intake = BMR * 1.4;
        }
        return calorie_intake;
    }
};