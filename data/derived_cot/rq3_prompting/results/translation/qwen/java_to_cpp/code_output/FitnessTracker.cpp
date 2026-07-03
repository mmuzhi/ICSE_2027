#include <string>
#include <array>

struct FitnessTracker {
    double height;
    double weight;
    int age;
    std::string sex;
    static constexpr std::array<std::array<double, 2>, 2> BMI_std = {{
        {{20.0, 25.0}}, // male
        {{19.0, 24.0}}  // female
    }};

    FitnessTracker(double height, double weight, int age, std::string sex)
        : height(height), weight(weight), age(age), sex(std::move(sex)) {}

    double getBMI() const {
        return weight / (height * height);
    }

    int conditionJudge() const {
        double BMI = getBMI();
        int index = (sex == "male") ? 0 : 1;
        if (BMI > BMI_std[index][1]) return 1;
        if (BMI < BMI_std[index][0]) return -1;
        return 0;
    }

    double calculateCalorieIntake() const {
        double BMR;
        if (sex == "male") {
            BMR = 10 * weight + 6.25 * height - 5 * age + 5;
        } else {
            BMR = 10 * weight + 6.25 * height - 5 * age - 161;
        }
        int condition = conditionJudge();
        if (condition == 1) return BMR * 1.2;
        if (condition == -1) return BMR * 1.6;
        return BMR * 1.4;
    }
};