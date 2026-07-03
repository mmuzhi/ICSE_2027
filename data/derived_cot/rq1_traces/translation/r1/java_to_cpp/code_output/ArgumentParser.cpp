#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <optional>
#include <any>
#include <sstream>
#include <stdexcept>

enum class ArgType { INTEGER, BOOLEAN, STRING };

class ArgumentParser {
public:
    template <typename X, typename Y>
    struct Tuple {
        X x;
        std::optional<Y> y;
        Tuple(X x, std::optional<Y> y) : x(x), y(y) {}
    };

private:
    std::map<std::string, std::any> arguments;
    std::set<std::string> required;
    std::map<std::string, ArgType> types;

public:
    ArgumentParser() = default;

    Tuple<bool, std::set<std::string>> parseArguments(const std::string& commandString) {
        std::vector<std::string> args;
        std::istringstream iss(commandString);
        std::string token;
        while (iss >> token) {
            args.push_back(token);
        }

        for (size_t i = 1; i < args.size(); i++) {
            std::string arg = args[i];
            if (arg.substr(0, 2) == "--") {
                size_t pos = arg.find('=', 2);
                if (pos != std::string::npos) {
                    std::string key = arg.substr(2, pos - 2);
                    std::string value = arg.substr(pos + 1);
                    arguments[key] = convertType(key, value);
                } else {
                    std::string key = arg.substr(2);
                    arguments[key] = true;
                }
            } else if (arg.substr(0, 1) == "-") {
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && args[i+1][0] != '-') {
                    std::string value = args[i+1];
                    arguments[key] = convertType(key, value);
                    i++;
                } else {
                    arguments[key] = true;
                }
            }
        }

        std::set<std::string> missingArgs;
        for (const auto& r : required) {
            if (arguments.find(r) == arguments.end()) {
                missingArgs.insert(r);
            }
        }

        if (missingArgs.empty()) {
            return Tuple<bool, std::set<std::string>>(true, std::nullopt);
        } else {
            return Tuple<bool, std::set<std::string>>(false, missingArgs);
        }
    }

    std::any getArgument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return std::any();
    }

    void addArgument(const std::string& arg, bool required, ArgType argType) {
        if (required) {
            this->required.insert(arg);
        }
        types[arg] = argType;
    }

private:
    std::any convertType(const std::string& arg, const std::string& value) {
        auto it = types.find(arg);
        if (it == types.end()) {
            return value;
        }
        ArgType t = it->second;
        try {
            switch(t) {
                case ArgType::INTEGER:
                    return std::stoi(value);
                case ArgType::BOOLEAN: {
                    std::string lowerValue = value;
                    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(),
                                   [](unsigned char c) { return std::tolower(c); });
                    return (lowerValue == "true");
                }
                case ArgType::STRING:
                    return value;
                default:
                    return value;
            }
        } catch (...) {
            return value;
        }
    }
};

int main() {
    ArgumentParser parser;
    parser.addArgument("arg1", true, ArgType::INTEGER);
    parser.addArgument("arg2", false, ArgType::STRING);
    parser.addArgument("option1", false, ArgType::BOOLEAN);
    parser.addArgument("option2", false, ArgType::BOOLEAN);

    std::string command = "python script.py --arg1=123 -arg2 value2 --option1 -option2";
    auto result = parser.parseArguments(command);

    std::cout << std::boolalpha << result.x << std::endl;
    if (result.y.has_value()) {
        std::set<std::string> missing = result.y.value();
        std::cout << "[";
        for (auto it = missing.begin(); it != missing.end(); ) {
            std::cout << *it;
            if (++it != missing.end()) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    std::cout << "{";
    for (auto it = parser.arguments.begin(); it != parser.arguments.end(); ) {
        std::cout << it->first << "=";
        if (it->second.type() == typeid(int)) {
            std::cout << std::any_cast<int>(it->second);
        } else if (it->second.type() == typeid(bool)) {
            std::cout << std::boolalpha << std::any_cast<bool>(it->second);
        } else if (it->second.type() == typeid(std::string)) {
            std::cout << std::any_cast<std::string>(it->second);
        } else {
            std::cout << "?";
        }
        if (++it != parser.arguments.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;

    return 0;
}