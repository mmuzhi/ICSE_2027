#include <optional>
#include <string>

class PersonRequest {
public:
    PersonRequest(std::string name, std::string sex, std::string phoneNumber)
        : name(validate_name(std::move(name))),
          sex(validate_sex(std::move(sex))),
          phoneNumber(validate_phoneNumber(std::move(phoneNumber))) {}

    std::optional<std::string> name;
    std::optional<std::string> sex;
    std::optional<std::string> phoneNumber;

private:
    static std::optional<std::string> validate_name(std::string name) {
        if (name.empty() || name.length() > 33) {
            return std::nullopt;
        }
        return std::move(name);
    }

    static std::optional<std::string> validate_sex(std::string sex) {
        if (sex == "Man" || sex == "Woman" || sex == "UGM") {
            return std::move(sex);
        }
        return std::nullopt;
    }

    static std::optional<std::string> validate_phoneNumber(std::string phoneNumber) {
        if (phoneNumber.length() != 11) {
            return std::nullopt;
        }
        for (char c : phoneNumber) {
            if (c < '0' || c > '9') {
                return std::nullopt;
            }
        }
        return std::move(phoneNumber);
    }
};