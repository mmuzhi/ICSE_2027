#include <string>
#include <cctype>

class PersonRequest {
private:
    std::string name;
    std::string sex;
    std::string phoneNumber;

    std::string validate_name(const std::string& name) {
        if (name.empty() || name.length() > 33) {
            return "";
        }
        return name;
    }

    std::string validate_sex(const std::string& sex) {
        if (sex != "Man" && sex != "Woman" && sex != "UGM") {
            return "";
        }
        return sex;
    }

    std::string validate_phoneNumber(const std::string& phoneNumber) {
        if (phoneNumber.empty() || phoneNumber.length() != 11) {
            return "";
        }
        for (char c : phoneNumber) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return "";
            }
        }
        return phoneNumber;
    }

public:
    PersonRequest(const std::string& name, const std::string& sex, const std::string& phoneNumber) {
        this->name = validate_name(name);
        this->sex = validate_sex(sex);
        this->phoneNumber = validate_phoneNumber(phoneNumber);
    }
};