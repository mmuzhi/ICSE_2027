#include <string>
#include <unordered_map>
#include <set>
#include <vector>
#include <optional>
#include <any>
#include <sstream>
#include <utility>

enum class ArgType { STRING, INT, FLOAT, BOOL };

class ArgumentParser {
public:
    ArgumentParser() = default;

    std::pair<bool, std::optional<std::set<std::string>>> parse_arguments(const std::string& command_string) {
        std::vector<std::string> tokens;
        std::istringstream iss(command_string);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        for (size_t i = 1; i < tokens.size(); ++i) {
            const std::string& arg = tokens[i];
            if (arg.rfind("--", 0) == 0) {
                std::string after_dashes = arg.substr(2);
                std::vector<std::string> parts;
                std::istringstream part_stream(after_dashes);
                std::string part;
                while (std::getline(part_stream, part, '=')) {
                    parts.push_back(part);
                }
                if (parts.size() == 2) {
                    arguments_[parts[0]] = convert_type(parts[0], parts[1]);
                } else {
                    arguments_[parts[0]] = true;
                }
            } else if (arg.rfind("-", 0) == 0) {
                std::string key = arg.substr(1);
                if (i + 1 < tokens.size() && tokens[i + 1].rfind("-", 0) != 0) {
                    arguments_[key] = convert_type(key, tokens[i + 1]);
                } else {
                    arguments_[key] = true;
                }
            }
        }

        std::set<std::string> missing_args;
        for (const auto& req : required_) {
            if (arguments_.find(req) == arguments_.end()) {
                missing_args.insert(req);
            }
        }

        if (!missing_args.empty()) {
            return {false, missing_args};
        }
        return {true, std::nullopt};
    }

    std::optional<std::any> get_argument(const std::string& key) const {
        auto it = arguments_.find(key);
        if (it != arguments_.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void add_argument(const std::string& arg, bool required = false, ArgType arg_type = ArgType::STRING) {
        if (required) {
            required_.insert(arg);
        }
        types_[arg] = arg_type;
    }

private:
    std::any convert_type(const std::string& arg, const std::string& value) {
        auto it = types_.find(arg);
        if (it == types_.end()) {
            return value;
        }
        try {
            switch (it->second) {
                case ArgType::INT:
                    return std::stoi(value);
                case ArgType::FLOAT:
                    return std::stod(value);
                case ArgType::BOOL:
                    return !value.empty();
                case ArgType::STRING:
                default:
                    return value;
            }
        } catch (...) {
            return value;
        }
    }

    std::unordered_map<std::string, std::any> arguments_;
    std::set<std::string> required_;
    std::unordered_map<std::string, ArgType> types_;
};