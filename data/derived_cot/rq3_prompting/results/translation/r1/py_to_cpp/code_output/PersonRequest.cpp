#include <string>
#include <optional>
#include <cctype>

class PersonRequest {
public:
    std::optional<std::string> name;
    std::optional<std::string> sex;
    std::optional<std::string> phoneNumber;

    PersonRequest(const std::string& name, const std::string& sex, const std::string& phoneNumber)
        : name(_validateName(name))
        , sex(_validateSex(sex))
        , phoneNumber(_validatePhoneNumber(phoneNumber))
    {}

private:
    static std::optional<std::string> _validateName(const std::string& name) {
        if (name.empty() || name.length() > 33) {
            return std::nullopt;
        }
        return name;
    }

    static std::optional<std::string> _validateSex(const std::string& sex) {
        if (sex != "Man" && sex != "Woman" && sex != "UGM") {
            return std::nullopt;
        }
        return sex;
    }

    static std::optional<std::string> _validatePhoneNumber(const std::string& phoneNumber) {
        if (phoneNumber.empty() || phoneNumber.length() != 11) {
            return std::nullopt;
        }
        for (char c : phoneNumber) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                return std::nullopt;
            }
        }
        return phoneNumber;
    }
};