#include <string>
#include <regex>

class PersonRequest {
private:
    std::string* name;
    std::string* sex;
    std::string* phoneNumber;

public:
    PersonRequest(const std::string* name, const std::string* sex, const std::string* phoneNumber) {
        this->name = validateName(name);
        this->sex = validateSex(sex);
        this->phoneNumber = validatePhoneNumber(phoneNumber);
    }

    ~PersonRequest() {
        delete name;
        delete sex;
        delete phoneNumber;
    }

    const std::string* getName() const {
        return name;
    }

    const std::string* getSex() const {
        return sex;
    }

    const std::string* getPhoneNumber() const {
        return phoneNumber;
    }

    static std::string* validateName(const std::string* name) {
        if (name == nullptr || name->empty() || name->size() > 33) {
            return nullptr;
        }
        return new std::string(*name);
    }

    static std::string* validateSex(const std::string* sex) {
        if (sex == nullptr || (*sex != "Man" && *sex != "Woman" && *sex != "UGM")) {
            return nullptr;
        }
        return new std::string(*sex);
    }

    static std::string* validatePhoneNumber(const std::string* phoneNumber) {
        if (phoneNumber == nullptr || phoneNumber->empty() || phoneNumber->size() != 11) {
            return nullptr;
        }
        std::regex pattern("\\d{11}");
        if (!std::regex_match(*phoneNumber, pattern)) {
            return nullptr;
        }
        return new std::string(*phoneNumber);
    }
};