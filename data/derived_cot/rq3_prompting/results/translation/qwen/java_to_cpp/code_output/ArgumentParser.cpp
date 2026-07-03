#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <optional>
#include <set>
#include <string>
#include <typeinfo>

struct Tuple {
    bool x;
    std::optional<std::set<std::string>> y;
};

class ArgumentParser {
private:
    std::unordered_map<std::string, std::variant<int, bool, std::string>> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, std::string> types;

    std::variant<int, bool, std::string> convertType(const std::string& arg, const std::string& value) {
        auto it = types.find(arg);
        if (it == types.end()) {
            return value;
        }
        std::string type_str = it->second;
        if (type_str == "int") {
            try {
                return std::stoi(value);
            } catch (...) {
                return value;
            }
        } else if (type_str == "boolean") {
            try {
                if (value == "true" || value == "True" || value == "TRUE") {
                    return true;
                } else if (value == "false" || value == "False" || value == "FALSE") {
                    return false;
                }
                return false;
            } catch (...) {
                return value;
            }
        } else if (type_str == "string") {
            return value;
        }
        return value;
    }

public:
    ArgumentParser() = default;

    Tuple parseArguments(const std::string& commandString) {
        std::istringstream iss(commandString);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        for (int i = 1; i < static_cast<int>(tokens.size()); ++i) {
            std::string arg = tokens[i];
            if (arg.starts_with("--")) {
                std::string rest = arg.substr(2);
                auto pos = rest.find('=');
                if (pos != std::string::npos) {
                    std::string key = rest.substr(0, pos);
                    std::string value = rest.substr(pos + 1);
                    arguments[key] = convertType(key, value);
                } else {
                    arguments[arg.substr(2)] = true;
                }
            } else if (arg.starts_with("-")) {
                std::string key = arg.substr(1);
                if (i + 1 < tokens.size() && !tokens[i + 1].starts_with("-")) {
                    arguments[key] = convertType(key, tokens[i + 1]);
                    ++i;
                } else {
                    arguments[key] = true;
                }
            }
        }

        std::set<std::string> missingArgs;
        for (const auto& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missingArgs.insert(req);
            }
        }

        if (!missingArgs.empty()) {
            return {false, missingArgs};
        }
        return {true, std::nullopt};
    }

    std::optional<std::variant<int, bool, std::string>> getArgument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void addArgument(const std::string& arg, bool required, const std::type_info& type) {
        if (required) {
            required.insert(arg);
        }
        std::string type_str;
        if (type == typeid(int)) {
            type_str = "int";
        } else if (type == typeid(bool)) {
            type_str = "boolean";
        } else if (type == typeid(std::string)) {
            type_str = "string";
        } else {
            type_str = "string";
        }
        types[arg] = type_str;
    }
};

int main() {
    ArgumentParser parser;
    parser.addArgument("arg1", true, typeid(int));
    parser.addArgument("arg2", false, typeid(std::string));
    parser.addArgument("option1", false, typeid(bool));
    parser.addArgument("option2", false, typeid(bool));

    Tuple result = parser.parseArguments("python script.py --arg1=123 -arg2 value2 --option1 -option2");
    std::cout << result.x << std::endl;
    if (result.y) {
        std::cout << "Missing arguments: ";
        for (const auto& arg : *result.y) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    return 0;
}