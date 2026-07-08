#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <any>
#include <sstream>
#include <regex>
#include <algorithm>

class ArgumentParser {
public:
    enum class ArgType {
        INT,
        BOOL,
        STRING
    };

    struct ParseResult {
        bool success;
        std::optional<std::set<std::string>> missing;

        ParseResult(bool s, std::optional<std::set<std::string>> m)
            : success(s), missing(std::move(m)) {}
    };

private:
    std::map<std::string, std::any> arguments;
    std::set<std::string> required;
    std::map<std::string, ArgType> types;

    static std::vector<std::string> splitWhitespace(const std::string& s) {
        std::vector<std::string> result;
        std::regex re("\\s+");
        std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        return result;
    }

    static std::vector<std::string> splitOnChar(const std::string& s, char delim) {
        std::vector<std::string> result;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, delim)) {
            result.push_back(token);
        }
        // Match Java's split behavior: remove trailing empty strings
        while (!result.empty() && result.back().empty()) {
            result.pop_back();
        }
        return result;
    }

    static bool startsWith(const std::string& s, const std::string& prefix) {
        return s.size() >= prefix.size() && s.compare(0, prefix.size(), prefix) == 0;
    }

    std::any convertType(const std::string& arg, const std::string& value) {
        try {
            auto it = types.find(arg);
            if (it != types.end()) {
                ArgType type = it->second;
                if (type == ArgType::INT) {
                    return std::stoi(value);
                } else if (type == ArgType::BOOL) {
                    // Java's Boolean.parseBoolean: true only for "true" (case-insensitive)
                    std::string lower = value;
                    std::transform(lower.begin(), lower.end(), lower.begin(),
                                   [](unsigned char c) { return std::tolower(c); });
                    return lower == "true";
                } else if (type == ArgType::STRING) {
                    return value;
                }
            }
        } catch (...) {
            return value;
        }
        return value;
    }

public:
    ArgumentParser() = default;

    ParseResult parseArguments(const std::string& commandString) {
        std::vector<std::string> args = splitWhitespace(commandString);
        for (size_t i = 1; i < args.size(); i++) {
            const std::string& arg = args[i];
            if (startsWith(arg, "--")) {
                std::string afterPrefix = arg.substr(2);
                std::vector<std::string> keyValue = splitOnChar(afterPrefix, '=');
                if (keyValue.size() == 2) {
                    arguments[keyValue[0]] = convertType(keyValue[0], keyValue[1]);
                } else {
                    arguments[keyValue[0]] = true;
                }
            } else if (startsWith(arg, "-")) {
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && !startsWith(args[i + 1], "-")) {
                    arguments[key] = convertType(key, args[i + 1]);
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
        if (!missingArgs.empty()) {
            return ParseResult(false, missingArgs);
        }
        return ParseResult(true, std::nullopt);
    }

    std::any getArgument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return {};
    }

    void addArgument(const std::string& arg, bool req, ArgType argType) {
        if (req) {
            required.insert(arg);
        }
        types[arg] = argType;
    }

    void printArguments(std::ostream& os = std::cout) const {
        os << "{";
        bool first = true;
        for (const auto& [key, value] : arguments) {
            if (!first) os << ", ";
            first = false;
            os << key << "=";
            if (value.type() == typeid(int)) {
                os << std::any_cast<int>(value);
            } else if (value.type() == typeid(bool)) {
                os << (std::any_cast<bool>(value) ? "true" : "false");
            } else if (value.type() == typeid(std::string)) {
                os << std::any_cast<std::string>(value);
            }
        }
        os << "}" << std::endl;
    }
};

int main() {
    ArgumentParser parser;
    parser.addArgument("arg1", true, ArgumentParser::ArgType::INT);
    parser.addArgument("arg2", false, ArgumentParser::ArgType::STRING);
    parser.addArgument("option1", false, ArgumentParser::ArgType::BOOL);
    parser.addArgument("option2", false, ArgumentParser::ArgType::BOOL);

    auto result = parser.parseArguments(
        "python script.py --arg1=123 -arg2 value2 --option1 -option2");

    std::cout << std::boolalpha << result.success << std::endl;

    if (result.missing.has_value()) {
        std::cout << "[";
        bool first = true;
        for (const auto& s : result.missing.value()) {
            if (!first) std::cout << ", ";
            first = false;
            std::cout << s;
        }
        std::cout << "]" << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    parser.printArguments();
    return 0;
}