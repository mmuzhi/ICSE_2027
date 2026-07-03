#include <map>
#include <vector>
#include <string>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    std::map<std::string, std::vector<double>> BMI_std_map;

public:
    FitnessTracker(double h, double w, int a, std::string s) 
        : height(h), weight(w), age(a), sex(s) {
        BMI_std_map["male"] = {20.0, 25.0};
        BMI_std_map["female"] = {19.0, 24.0};
    }

    double get_BMI() {
        return weight / (height * height);
    }

    int condition_judge() {
        double BMI = get_BMI();
        std::vector<double> BMI_range;
        if (sex == "male") {
            BMI_range = BMI_std_map["male"];
        } else {
            BMI_range = BMI_std_map["female"];
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
        int cond = condition_judge();
        if (cond == 1) {
            return BMR * 1.2;
        } else if (cond == -1) {
            return BMR * 1.6;
        } else {
            return BMR * 1.4;
        }
    }
};