#include <string>
#include <vector>
#include <map>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    std::map<std::string, std::vector<double>> BMI_std;

public:
    FitnessTracker(double height, double weight, int age, std::string sex) {
        this->height = height;
        this->weight = weight;
        this->age = age;
        this->sex = sex;
        BMI_std["male"] = {20.0, 25.0};
        BMI_std["female"] = {19.0, 24.0};
    }

    double get_BMI() const {
        return weight / (height * height);
    }

    int condition_judge() const {
        double BMI = get_BMI();
        const auto& BMI_range = (sex == "male") ? BMI_std.at("male") : BMI_std.at("female");
        if (BMI > BMI_range[1]) {
            return 1;
        } else if (BMI < BMI_range[0]) {
            return -1;
        } else {
            return 0;
        }
    }

    double calculate_calorie_intake() const {
        double BMR;
        if (sex == "male") {
            BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        } else {
            BMR = 10 * weight + 6.25 * height - 5 * age - 161;
        }
        int condition = condition_judge();
        if (condition == 1) {
            return BMR * 1.2;
        } else if (condition == -1) {
            return BMR * 1.6;
        } else {
            return BMR * 1.4;
        }
    }
};