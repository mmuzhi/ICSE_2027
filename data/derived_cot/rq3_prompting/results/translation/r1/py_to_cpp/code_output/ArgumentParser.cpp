#include <iostream>
#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <sstream>
#include <any>
#include <functional>
#include <stdexcept>

class ArgumentParser {
private:
    std::unordered_map<std::string, std::any> arguments_;
    std::set<std::string> required_;
    std::unordered_map<std::string, std::function<std::any(const std::string&)>> types_;

    static std::any default_string_converter(const std::string& s) {
        return s;
    }

    std::any convert_type(const std::string& arg, const std::string& value) {
        auto it = types_.find(arg);
        if (it != types_.end()) {
            try {
                return it->second(value);
            } catch (...) {
                return std::any(value);
            }
        } else {
            return std::any(value);
        }
    }

public:
    ArgumentParser() {}

    void add_argument(const std::string& arg, bool required = false,
                      std::function<std::any(const std::string&)> converter = default_string_converter) {
        if (required) {
            required_.insert(arg);
        }
        types_[arg] = converter;
    }

    std::pair<bool, std::set<std::string>> parse_arguments(const std::string& command_string) {
        // Clear previous arguments (match Python behavior: new parse replaces old)
        arguments_.clear();

        std::vector<std::string> args;
        std::istringstream iss(command_string);
        std::string token;
        while (iss >> token) {
            args.push_back(token);
        }

        // Skip the script name (first token), if it exists
        if (args.empty()) {
            std::set<std::string> missing;
            for (const auto& r : required_) {
                if (arguments_.find(r) == arguments_.end())
                    missing.insert(r);
            }
            if (missing.empty())
                return {true, {}};
            else
                return {false, missing};
        }

        for (size_t i = 1; i < args.size(); ++i) {
            const std::string& arg = args[i];

            if (arg.size() >= 2 && arg[0] == '-' && arg[1] == '-') {
                // double dash: --key=value or --key (boolean)
                std::string keystr = arg.substr(2);
                size_t eqpos = keystr.find('=');
                if (eqpos != std::string::npos) {
                    std::string key = keystr.substr(0, eqpos);
                    std::string value = keystr.substr(eqpos + 1);
                    arguments_[key] = convert_type(key, value);
                } else {
                    arguments_[keystr] = std::any(true);
                }
            } else if (arg.size() >= 2 && arg[0] == '-' && arg[1] != '-') {
                // single dash: -key value or -key (boolean)
                std::string key = arg.substr(1);
                if (i + 1 < args.size() && !args[i+1].empty() && args[i+1][0] != '-') {
                    std::string value = args[i+1];
                    arguments_[key] = convert_type(key, value);
                    ++i; // skip the value token
                } else {
                    arguments_[key] = std::any(true);
                }
            }
            // Ignore tokens not starting with '-'
        }

        std::set<std::string> missing;
        for (const auto& r : required_) {
            if (arguments_.find(r) == arguments_.end())
                missing.insert(r);
        }
        if (missing.empty())
            return {true, {}};
        else
            return {false, missing};
    }

    std::any get_argument(const std::string& key) const {
        auto it = arguments_.find(key);
        if (it != arguments_.end())
            return it->second;
        return std::any(); // equivalent to None
    }
};