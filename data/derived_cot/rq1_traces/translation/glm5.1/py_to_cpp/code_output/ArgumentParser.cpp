#include <any>
#include <functional>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class ArgumentParser {
private:
    std::unordered_map<std::string, std::any> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, std::function<std::any(const std::string&)>> types;

    std::any _convert_type(const std::string& arg, const std::string& value) {
        auto it = types.find(arg);
        if (it == types.end()) {
            return value;
        }
        try {
            return it->second(value);
        } catch (...) {
            return value;
        }
    }

public:
    ArgumentParser() = default;

    std::pair<bool, std::optional<std::unordered_set<std::string>>>
    parse_arguments(const std::string& command_string) {
        std::vector<std::string> all_args;
        std::istringstream iss(command_string);
        std::string token;
        while (iss >> token) {
            all_args.push_back(token);
        }

        std::vector<std::string> args;
        if (all_args.size() > 1) {
            args.assign(all_args.begin() + 1, all_args.end());
        }

        for (size_t i = 0; i < args.size(); i++) {
            const std::string& arg = args[i];
            if (arg.size() >= 2 && arg[0] == '-' && arg[1] == '-') {
                std::string rest = arg.substr(2);
                size_t eq_pos = rest.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = rest.substr(0, eq_pos);
                    std::string value = rest.substr(eq_pos + 1);
                    arguments[key] = _convert_type(key, value);
                } else {
                    arguments[rest] = true;
                }
            } else if (!arg.empty() && arg[0] == '-') {
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && args[i + 1][0] != '-') {
                    arguments[key] = _convert_type(key, args[i + 1]);
                } else {
                    arguments[key] = true;
                }
            }
        }

        std::unordered_set<std::string> missing_args;
        for (const auto& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missing_args.insert(req);
            }
        }

        if (!missing_args.empty()) {
            return {false, missing_args};
        }

        return {true, std::nullopt};
    }

    std::optional<std::any> get_argument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void add_argument(const std::string& arg, bool required = false,
                      std::function<std::any(const std::string&)> arg_type = nullptr) {
        if (required) {
            this->required.insert(arg);
        }
        if (arg_type) {
            types[arg] = std::move(arg_type);
        } else {
            // Default arg_type=str equivalent: return the string as-is
            types[arg] = [](const std::string& v) -> std::any { return v; };
        }
    }
};