#include <string>
#include <unordered_map>
#include <utility>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    std::unordered_map<std::string, std::pair<double, double>> BMI_std;

public:
    FitnessTracker(double height, double weight, int age, const std::string& sex)
        : height(height), weight(weight), age(age), sex(sex) {
        BMI_std["male"] = {20, 25};
        BMI_std["female"] = {19, 24};
    }

    double get_BMI() {
        return weight / (height * height);
    }

    int condition_judge() {
        double BMI = get_BMI();
        std::pair<double, double> BMI_range = BMI_std[sex];
        if (BMI > BMI_range.second) {
            return 1;
        } else if (BMI < BMI_range.first) {
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
        int condition = condition_judge();
        double calorie_intake;
        if (condition == 1) {
            calorie_intake = BMR * 1.2;
        } else if (condition == -1) {
            calorie_intake = BMR * 1.6;
        } else {
            calorie_intake = BMR * 1.4;
        }
        return calorie_intake;
    }
};