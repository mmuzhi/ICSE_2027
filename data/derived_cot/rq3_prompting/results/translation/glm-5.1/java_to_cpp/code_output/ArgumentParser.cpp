#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <variant>
#include <optional>
#include <regex>
#include <cctype>

enum class ArgType {
    Integer,
    Boolean,
    String
};

template<typename X, typename Y>
struct Tuple {
    X x;
    Y y;
    Tuple(X x_, Y y_) : x(std::move(x_)), y(std::move(y_)) {}
};

class ArgumentParser {
public:
    std::unordered_map<std::string, std::variant<int, bool, std::string>> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, ArgType> types;

    ArgumentParser() = default;

    Tuple<bool, std::optional<std::unordered_set<std::string>>> parseArguments(const std::string& commandString) {
        std::regex re("\\s+");
        std::sregex_token_iterator it(commandString.begin(), commandString.end(), re, -1);
        std::sregex_token_iterator end_it;
        std::vector<std::string> args(it, end_it);

        for (int i = 1; i < (int)args.size(); i++) {
            const std::string& arg = args[i];
            if (arg.size() >= 2 && arg[0] == '-' && arg[1] == '-') {
                std::string kv = arg.substr(2);
                size_t eqPos = kv.find('=');
                if (eqPos != std::string::npos) {
                    std::string key = kv.substr(0, eqPos);
                    std::string value = kv.substr(eqPos + 1);
                    arguments[key] = convertType(key, value);
                } else {
                    arguments[kv] = true;
                }
            }
            else if (!arg.empty() && arg[0] == '-') {
                std::string key = arg.substr(1);
                if (i + 1 < (int)args.size() && (args[i + 1].empty() || args[i + 1][0] != '-')) {
                    arguments[key] = convertType(key, args[i + 1]);
                    i++;
                }
                else {
                    arguments[key] = true;
                }
            }
        }

        std::unordered_set<std::string> missingArgs(required);
        for (const auto& [key, val] : arguments) {
            missingArgs.erase(key);
        }

        if (!missingArgs.empty()) {
            return Tuple<bool, std::optional<std::unordered_set<std::string>>>(false, missingArgs);
        }
        return Tuple<bool, std::optional<std::unordered_set<std::string>>>(true, std::nullopt);
    }

    std::variant<int, bool, std::string>* getArgument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) return &it->second;
        return nullptr;
    }

    void addArgument(const std::string& arg, bool isRequired, ArgType argType) {
        if (isRequired) {
            required.insert(arg);
        }
        types[arg] = argType;
    }

    std::variant<int, bool, std::string> convertType(const std::string& arg, const std::string& value) {
        try {
            auto it = types.find(arg);
            if (it != types.end()) {
                ArgType type = it->second;
                if (type == ArgType::Integer) {
                    return std::stoi(value);
                }
                else if (type == ArgType::Boolean) {
                    std::string lower = value;
                    for (auto& c : lower) c = (char)std::tolower((unsigned char)c);
                    return lower == "true";
                }
                else if (type == ArgType::String) {
                    return value;
                }
            }
        } catch (...) {
            return value;
        }
        return value;
    }
};

int main() {
    ArgumentParser parser;
    parser.addArgument("arg1", true, ArgType::Integer);
    parser.addArgument("arg2", false, ArgType::String);
    parser.addArgument("option1", false, ArgType::Boolean);
    parser.addArgument("option2", false, ArgType::Boolean);

    auto result = parser.parseArguments("python script.py --arg1=123 -arg2 value2 --option1 -option2");
    std::cout << std::boolalpha << result.x << "\n";
    if (result.y.has_value()) {
        std::cout << "[";
        bool first = true;
        for (const auto& s : result.y.value()) {
            if (!first) std::cout << ", ";
            std::cout << s;
            first = false;
        }
        std::cout << "]\n";
    } else {
        std::cout << "null\n";
    }

    std::cout << "{";
    bool first = true;
    for (const auto& [key, val] : parser.arguments) {
        if (!first) std::cout << ", ";
        std::cout << key << "=";
        std::visit([](auto&& v) {
            using T = std::decay_t<decltype(v)>;
            if constexpr (std::is_same_v<T, bool>) {
                std::cout << std::boolalpha << v;
            } else {
                std::cout << v;
            }
        }, val);
        first = false;
    }
    std::cout << "}\n";

    return 0;
}