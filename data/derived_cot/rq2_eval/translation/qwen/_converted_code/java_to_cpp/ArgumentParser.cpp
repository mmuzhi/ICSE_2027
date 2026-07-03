#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <any>
#include <stdexcept>

class ArgumentParser {
private:
    std::unordered_map<std::string, std::any> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, std::type_info> types;

    bool convertToBool(const std::string& value) {
        std::string s = value;
        auto start = s.find_first_not_of(" ");
        auto end = s.find_last_not_of(" ");
        if (start == std::string::npos) {
            return false;
        }
        s = s.substr(start, end - start + 1);
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char& c) { return std::toupper(c); });
        if (s == "TRUE") return true;
        if (s == "FALSE") return false;
        throw std::invalid_argument("Invalid boolean value: " + value);
    }

    int convertToInt(const std::string& value) {
        try {
            return std::stoi(value);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid integer value: " + value);
        }
    }

    std::string convertToString(const std::string& value) {
        return value;
    }

    std::any convert_type(const std::string& arg, const std::string& value) {
        auto it = types.find(arg);
        if (it == types.end()) {
            return value;
        }
        if (it->second == typeid(int)) {
            return convertToInt(value);
        } else if (it->second == typeid(bool)) {
            return convertToBool(value);
        } else if (it->second == typeid(std::string)) {
            return convertToString(value);
        } else {
            return value;
        }
    }

public:
    ArgumentParser() = default;

    std::pair<bool, std::unordered_set<std::string>> parseArguments(const std::string& commandString) {
        std::istringstream iss(commandString);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        for (int i = 1; i < tokens.size(); i++) {
            std::string arg = tokens[i];
            if (arg.starts_with("--")) {
                std::string optionPart = arg.substr(2);
                size_t pos = optionPart.find('=');
                if (pos != std::string::npos) {
                    std::string key = optionPart.substr(0, pos);
                    std::string value = optionPart.substr(pos + 1);
                    arguments[key] = convert_type(key, value);
                } else {
                    arguments[arg.substr(2)] = true;
                }
            } else if (arg.starts_with("-")) {
                std::string key = arg.substr(1);
                if (i + 1 < tokens.size() && !tokens[i + 1].starts_with("-")) {
                    arguments[key] = convert_type(key, tokens[i + 1]);
                    i++;
                } else {
                    arguments[key] = true;
                }
            }
        }

        std::unordered_set<std::string> missingArgs;
        for (const auto& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missingArgs.insert(req);
            }
        }

        if (!missingArgs.empty()) {
            return {false, missingArgs};
        }
        return {true, {}};
    }

    std::any get_argument(const std::string& key) {
        return arguments[key];
    }

    void add_argument(const std::string& arg, bool required, const std::type_info& argType) {
        if (required) {
            required.insert(arg);
        }
        types[arg] = argType;
    }
};

int main() {
    ArgumentParser parser;
    parser.add_argument("arg1", true, typeid(int));
    parser.add_argument("arg2", false, typeid(std::string));
    parser.add_argument("option1", false, typeid(bool));
    parser.add_argument("option2", false, typeid(bool));

    auto result = parser.parseArguments("python script.py --arg1=123 -arg2 value2 --option1 -option2");
    std::cout << result.first << std::endl;
    if (!result.second.empty()) {
        std::cout << "Missing arguments: ";
        for (const auto& arg : result.second) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}