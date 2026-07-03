#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <any>
#include <optional>
#include <stdexcept>
#include <cctype>

// Simple tuple template to mimic Java Tuple<X,Y>
template<typename X, typename Y>
struct Tuple {
    X x;
    Y y;
    Tuple(X x_, Y y_) : x(std::move(x_)), y(std::move(y_)) {}
};

class ArgumentParser {
private:
    std::unordered_map<std::string, std::any> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, std::string> types; // "int", "bool", "string"

public:
    ArgumentParser() = default;

    // Parse command string (e.g., "program --arg=123 -b value")
    Tuple<bool, std::optional<std::unordered_set<std::string>>> parseArguments(const std::string& commandString) {
        std::istringstream iss(commandString);
        std::vector<std::string> args;
        std::string token;
        while (iss >> token) {
            args.push_back(token);
        }

        // Start from index 1 to skip the program name (as in Java)
        for (size_t i = 1; i < args.size(); ++i) {
            const std::string& arg = args[i];
            if (arg.size() >= 2 && arg[0] == '-' && arg[1] == '-') {
                // Long option --key=value or --key
                std::string keyValue = arg.substr(2);
                size_t eqPos = keyValue.find('=');
                if (eqPos != std::string::npos) {
                    std::string key = keyValue.substr(0, eqPos);
                    std::string value = keyValue.substr(eqPos + 1);
                    arguments[key] = convertType(key, value);
                } else {
                    arguments[keyValue] = true; // flag
                }
            } else if (arg.size() >= 1 && arg[0] == '-') {
                // Short option -key value or -key
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && !args[i + 1].empty() && args[i + 1][0] != '-') {
                    arguments[key] = convertType(key, args[i + 1]);
                    ++i; // consume next token
                } else {
                    arguments[key] = true; // flag
                }
            }
        }

        // Find missing required arguments
        std::unordered_set<std::string> missing;
        for (const auto& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missing.insert(req);
            }
        }
        if (!missing.empty()) {
            return Tuple<bool, std::optional<std::unordered_set<std::string>>>(false, std::move(missing));
        }
        return Tuple<bool, std::optional<std::unordered_set<std::string>>>(true, std::nullopt);
    }

    // Get value for a key (any type)
    std::any getArgument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return {};
    }

    // Add an argument specification
    void addArgument(const std::string& arg, bool required_, const std::string& argType) {
        if (required_) {
            required.insert(arg);
        }
        types[arg] = argType;
    }

private:
    // Convert string value according to registered type
    std::any convertType(const std::string& arg, const std::string& value) {
        try {
            auto it = types.find(arg);
            if (it != types.end()) {
                const std::string& typeStr = it->second;
                if (typeStr == "int") {
                    return std::stoi(value); // may throw
                } else if (typeStr == "bool") {
                    // Java Boolean.parseBoolean returns true only for "true" (case-sensitive)
                    return value == "true";
                } else if (typeStr == "string") {
                    return value;
                }
            }
        } catch (const std::exception&) {
            // fall through: return original string
        }
        return value; // fallback: string
    }
};

// Helper to print a std::any value (for debugging, matches Java's toString)
void printAny(std::ostream& os, const std::any& val) {
    if (val.type() == typeid(int)) {
        os << std::any_cast<int>(val);
    } else if (val.type() == typeid(bool)) {
        os << (std::any_cast<bool>(val) ? "true" : "false");
    } else if (val.type() == typeid(std::string)) {
        os << std::any_cast<std::string>(val);
    } else {
        os << "unknown";
    }
}

// Helper to print a set (like Java's Set.toString)
void printSet(std::ostream& os, const std::unordered_set<std::string>& s) {
    os << "[";
    bool first = true;
    for (const auto& elem : s) {
        if (!first) os << ", ";
        os << elem;
        first = false;
    }
    os << "]";
}

int main() {
    ArgumentParser parser;
    parser.addArgument("arg1", true, "int");
    parser.addArgument("arg2", false, "string");
    parser.addArgument("option1", false, "bool");
    parser.addArgument("option2", false, "bool");

    auto result = parser.parseArguments("python script.py --arg1=123 -arg2 value2 --option1 -option2");
    std::cout << std::boolalpha << result.x << std::endl;
    if (result.y.has_value()) {
        printSet(std::cout, result.y.value());
        std::cout << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }

    // Print arguments map (like Java's Map.toString)
    std::cout << "{";
    bool first = true;
    for (const auto& [key, val] : parser.arguments) {
        if (!first) std::cout << ", ";
        std::cout << key << "=";
        printAny(std::cout, val);
        first = false;
    }
    std::cout << "}" << std::endl;

    return 0;
}