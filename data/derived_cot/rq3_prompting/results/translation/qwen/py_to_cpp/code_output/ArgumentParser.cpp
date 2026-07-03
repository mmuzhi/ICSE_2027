#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <stdexcept>
#include <functional>

class ArgumentParser {
private:
    std::unordered_map<std::string, std::any> arguments;
    std::unordered_set<std::string> required;
    std::unordered_map<std::string, std::function<std::any(const std::string&)>> types;

    std::any _convert_type(const std::string& arg, const std::string& value) {
        try {
            return types[arg](value);
        } catch (const std::exception& e) {
            return value;
        }
    }

public:
    ArgumentParser() = default;

    std::pair<bool, std::unordered_set<std::string>> parse_arguments(const std::string& command_string) {
        if (command_string.empty()) {
            return {true, {}};
        }

        std::istringstream iss(command_string);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Skip the first token if it's the script name or interpreter
        std::vector<std::string> args;
        bool skip_next = false;
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "python" || tokens[i] == "./script.py") {
                skip_next = true;
                continue;
            }
            if (skip_next) {
                skip_next = false;
                continue;
            }
            args.push_back(tokens[i]);
        }

        for (size_t i = 0; i < args.size(); ++i) {
            const std::string& arg = args[i];
            if (arg.starts_with("--")) {
                size_t pos = arg.find('=');
                if (pos != std::string::npos) {
                    std::string key = arg.substr(2, pos - 2);
                    std::string value = arg.substr(pos + 1);
                    arguments[key] = _convert_type(key, value);
                } else {
                    std::string key = arg.substr(2);
                    arguments[key] = true;
                }
            } else if (arg.starts_with('-')) {
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && !args[i + 1].starts_with('-')) {
                    arguments[key] = _convert_type(key, args[i + 1]);
                } else {
                    arguments[key] = true;
                }
            }
        }

        std::unordered_set<std::string> missing_args;
        for (const std::string& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missing_args.insert(req);
            }
        }

        if (!missing_args.empty()) {
            return {false, missing_args};
        }

        return {true, {}};
    }

    std::any get_argument(const std::string& key) {
        auto it = arguments.find(key);
        if (it != arguments.end()) {
            return it->second;
        }
        return nullptr;
    }

    void add_argument(const std::string& arg, bool required = false, const std::string& arg_type = "str") {
        if (required) {
            required.insert(arg);
        }
        // Define a conversion function for the given type
        if (arg_type == "int") {
            types[arg] = [](const std::string& value) {
                return std::stoi(value);
            };
        } else if (arg_type == "str") {
            types[arg] = [](const std::string& value) {
                return value;
            };
        } else if (arg_type == "bool") {
            types[arg] = [](const std::string& value) {
                return !value.empty();
            };
        } else if (arg_type == "float") {
            types[arg] = [](const std::string& value) {
                return std::stod(value);
            };
        } else {
            // Default to string conversion
            types[arg] = [](const std::string& value) {
                return value;
            };
        }
    }
};