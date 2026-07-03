#include <optional>
#include <string>
#include <cctype>

class PersonRequest {
private:
    std::optional<std::string> name_;
    std::optional<std::string> sex_;
    std::optional<std::string> phoneNumber_;

    static std::optional<std::string> validateName(const std::string& name) {
        if (name.empty() || name.length() > 33) {
            return std::nullopt;
        }
        return name;
    }

    static std::optional<std::string> validateSex(const std::string& sex) {
        if (sex != "Man" && sex != "Woman" && sex != "UGM") {
            return std::nullopt;
        }
        return sex;
    }

    static std::optional<std::string> validatePhoneNumber(const std::string& phoneNumber) {
        if (phoneNumber.length() != 11) {
            return std::nullopt;
        }
        for (char c : phoneNumber) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return std::nullopt;
            }
        }
        return phoneNumber;
    }

public:
    PersonRequest(std::optional<std::string> name, std::optional<std::string> sex, std::optional<std::string> phoneNumber)
        : name_(validateName(name.value_or("")))
        , sex_(validateSex(sex.value_or("")))
        , phoneNumber_(validatePhoneNumber(phoneNumber.value_or("")))
    {}

    std::optional<std::string> getName() const {
        return name_;
    }

    std::optional<std::string> getSex() const {
        return sex_;
    }

    std::optional<std::string> getPhoneNumber() const {
        return phoneNumber_;
    }
};