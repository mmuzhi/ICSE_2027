#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <iostream>

class KeyError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Key not found";
    }
};

template<typename T>
class CamelCaseMap {
private:
    std::unordered_map<std::string, T> _data;

    static std::string to_camel_case(const std::string& key) {
        if (key.empty()) {
            return key;
        }
        std::istringstream iss(key);
        std::string part;
        std::vector<std::string> parts;
        while (std::getline(iss, part, '_')) {
            parts.push_back(part);
        }
        std::string result = parts[0];
        for (size_t i = 1; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                result += std::toupper(parts[i][0]);
                if (parts[i].size() > 1) {
                    result += parts[i].substr(1);
                }
            }
        }
        return result;
    }

public:
    CamelCaseMap() = default;

    T __getitem__(const std::string& key) {
        std::string camel_key = to_camel_case(key);
        auto it = _data.find(camel_key);
        if (it == _data.end()) {
            throw KeyError();
        }
        return it->second;
    }

    void __setitem__(const std::string& key, const T& value) {
        std::string camel_key = to_camel_case(key);
        _data[camel_key] = value;
    }

    void __delitem__(const std::string& key) {
        std::string camel_key = to_camel_case(key);
        auto it = _data.find(camel_key);
        if (it == _data.end()) {
            throw KeyError();
        }
        _data.erase(it);
    }

    auto __iter__() {
        return _data.begin();
    }

    size_t __len__() const {
        return _data.size();
    }
};

int main() {
    CamelCaseMap<std::string> camelize_map;
    camelize_map.__setitem__("first_name", "John");
    std::cout << camelize_map.__getitem__("first_name") << std::endl;

    try {
        std::cout << camelize_map.__getitem__("unknown_key") << std::endl;
    } catch (const KeyError& e) {
        std::cout << "KeyError: " << e.what() << std::endl;
    }

    return 0;
}