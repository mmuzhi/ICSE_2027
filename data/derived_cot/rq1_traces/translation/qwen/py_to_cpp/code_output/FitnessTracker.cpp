#include <iostream>
#include <string>
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
        BMI_std["male"] = {20, 25};
        BMI_std["female"] = {19, 24};
    }

    double get_BMI() {
        return weight / (height * height);
    }

    int condition_judge() {
        double bmi = get_BMI();
        std::vector<double> bmi_range = BMI_std[sex];
        if (bmi > bmi_range[1]) {
            return 1;
        } else if (bmi < bmi_range[0]) {
            return -1;
        } else {
            return 0;
        }
    }

    double calculate_calorie_intake() {
        double bmr;
        if (sex == "male") {
            bmr = 10 * weight + 6.25 * height - 5 * age + 5;
        } else {
            bmr = 10 * weight + 6.25 * height - 5 * age - 161;
        }

        int condition = condition_judge();
        if (condition == 1) {
            return bmr * 1.2;
        } else if (condition == -1) {
            return bmr * 1.6;
        } else {
            return bmr * 1.4;
        }
    }
};