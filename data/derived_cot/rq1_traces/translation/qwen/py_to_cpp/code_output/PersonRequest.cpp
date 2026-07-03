#include <string>

class PersonRequest {
private:
    static bool is_valid_sex(const std::string& sex) {
        return sex == "Man" || sex == "Woman" || sex == "UGM";
    }

    static bool is_valid_phone_number(const std::string& phone_number) {
        if (phone_number.empty()) return false;
        if (phone_number.length() != 11) return false;
        for (char c : phone_number) {
            if (!isdigit(static_cast<unsigned char>(c))) 
                return false;
        }
        return true;
    }

public:
    PersonRequest(const std::string& name, const std::string& sex, const std::string& phone_number) 
        : name(_validate_name(name)), 
          sex(_validate_sex(sex)), 
          phone_number(_validate_phone_number(phone_number)) {}

    const std::string& get_name() const { return name; }
    const std::string& get_sex() const { return sex; }
    const std::string& get_phone_number() const { return phone_number; }

private:
    std::string _validate_name(const std::string& name) {
        if (name.empty() || name.length() > 33) 
            return "";
        return name;
    }

    std::string _validate_sex(const std::string& sex) {
        if (!is_valid_sex(sex)) 
            return "";
        return sex;
    }

    std::string _validate_phone_number(const std::string& phone_number) {
        if (!is_valid_phone_number(phone_number)) 
            return "";
        return phone_number;
    }

    std::string name;
    std::string sex;
    std::string phone_number;
};