#include <string>
#include <optional>
#include <regex>

struct PersonRequest {
    std::optional<std::string> name;
    std::optional<std::string> sex;
    std::optional<std::string> phoneNumber;

    PersonRequest(std::string name, std::string sex, std::string phoneNumber) {
        name = validateName(name);
        sex = validateSex(sex);
        phoneNumber = validatePhoneNumber(phoneNumber);
    }

    std::optional<std::string> getName() const { return name; }
    std::optional<std::string> getSex() const { return sex; }
    std::optional<std::string> getPhoneNumber() const { return phoneNumber; }

private:
    std::optional<std::string> validateName(std::string name) {
        if (name.empty() || name.length() > 33) {
            return std::nullopt;
        }
        return name;
    }

    std::optional<std::string> validateSex(std::string sex) {
        if (sex != "Man" && sex != "Woman" && sex != "UGM") {
            return std::nullopt;
        }
        return sex;
    }

    std::optional<std::string> validatePhoneNumber(std::string phoneNumber) {
        if (phoneNumber.empty() || phoneNumber.length() != 11 || 
            !std::regex_match(phoneNumber, std::regex("\\d{11}"))) {
            return std::nullopt;
        }
        return phoneNumber;
    }
};