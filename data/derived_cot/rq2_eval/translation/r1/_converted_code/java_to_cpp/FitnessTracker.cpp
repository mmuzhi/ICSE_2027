#include <string>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    double BMI_std[2][2] = {{20.0, 25.0}, {19.0, 24.0}};

public:
    FitnessTracker(double height, double weight, int age, std::string sex)
        : height(height), weight(weight), age(age), sex(sex) {}

    double get_BMI() {
        return weight / (height * height);
    }

    int condition_judge() {
        double BMI = get_BMI();
        int index = (sex == "male") ? 0 : 1;
        if (BMI > BMI_std[index][1]) {
            return 1;
        }
        else if (BMI < BMI_std[index][0]) {
            return -1;
        }
        else {
            return 0;
        }
    }

    double calculate_calorie_intake() {
        double BMR;
        if (sex == "male") {
            BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        }
        else {
            BMR = 10 * weight + 6.25 * height - 5 * age - 161;
        }

        int condition = condition_judge();
        if (condition == 1) {
            return BMR * 1.2;
        }
        else if (condition == -1) {
            return BMR * 1.6;
        }
        else {
            return BMR * 1.4;
        }
    }
};