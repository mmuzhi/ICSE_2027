#include <string>
#include <vector>

class FitnessTracker {
private:
    double height;
    double weight;
    int age;
    std::string sex;
    std::vector<std::vector<double>> BMI_std = {{20, 25}, {19, 24}};

public:
    explicit FitnessTracker(double height, double weight, int age, std::string sex)
        : height(height), weight(weight), age(age), sex(std::move(sex)) {}

    double getBMI() const {
        return weight / (height * height);
    }

    int conditionJudge() const {
        const int index = (sex == "male") ? 0 : 1;
        const double BMI = getBMI();
        if (BMI > BMI_std[index][1]) {
            return 1;
        }
        else if (BMI < BMI_std[index][0]) {
            return -1;
        }
        return 0;
    }

    double calculateCalorieIntake() const {
        const double BMR = (sex == "male") 
            ? (10 * weight + 6.25 * height - 5 * age + 5)
            : (10 * weight + 6.25 * height - 5 * age - 161);
        const int condition = conditionJudge();
        switch (condition) {
            case 1: return BMR * 1.2;
            case -1: return BMR * 1.6;
            default: return BMR * 1.4;
        }
    }
};