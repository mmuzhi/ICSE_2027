#include <any>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

class ArgumentParser {
private:
    std::map<std::string, std::any> arguments;
    std::set<std::string> required;
    std::map<std::string, std::function<std::any(const std::string&)>> types;

    std::any _convert_type(const std::string& arg, const std::string& value) {
        auto it = types.find(arg);
        if (it != types.end()) {
            try {
                return it->second(value);
            } catch (...) {
                return value;
            }
        } else {
            return value;
        }
    }

public:
    ArgumentParser() = default;

    void add_argument(const std::string& arg, bool required_arg = false, std::function<std::any(const std::string&)> converter = [](const std::string& s) { return s; }) {
        if (required_arg) {
            required.insert(arg);
        }
        types[arg] = converter;
    }

    std::any get_argument(const std::string& key) const {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return std::any();
    }

    std::pair<bool, std::set<std::string>> parse_arguments(const std::string& command_string) {
        std::vector<std::string> tokens;
        std::istringstream iss(command_string);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (!tokens.empty()) {
            tokens.erase(tokens.begin());
        }

        for (size_t i = 0; i < tokens.size(); ) {
            const std::string& token_str = tokens[i];
            if (token_str.substr(0, 2) == "--") {
                std::string arg_part = token_str.substr(2);
                size_t eq_pos = arg_part.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = arg_part.substr(0, eq_pos);
                    std::string value = arg_part.substr(eq_pos + 1);
                    arguments[key] = _convert_type(key, value);
                } else {
                    arguments[arg_part] = true;
                }
                ++i;
            } else if (token_str[0] == '-') {
                std::string key = token_str.substr(1);
                if (i + 1 < tokens.size() && tokens[i + 1][0] != '-') {
                    std::string value = tokens[i + 1];
                    arguments[key] = _convert_type(key, value);
                    i += 2;
                } else {
                    arguments[key] = true;
                    ++i;
                }
            } else {
                ++i;
            }
        }

        std::set<std::string> missing;
        for (const auto& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missing.insert(req);
            }
        }

        if (!missing.empty()) {
            return { false, missing };
        }
        return { true, missing };
    }
};