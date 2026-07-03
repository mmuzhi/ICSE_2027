#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <variant>

using namespace std;

using Variant = variant<string, int, float, bool>;

class ArgumentParser {
private:
    map<string, Variant> arguments;
    set<string> required;
    map<string, string> types;

    static map<string, function<Variant(string)>> getTypeConverters() {
        static map<string, function<Variant(string)>> type_converters;
        if (type_converters.empty()) {
            type_converters["str"] = [](string s) { return s; };
            type_converters["int"] = [](string s) {
                try {
                    return stoi(s);
                } catch (...) {
                    throw runtime_error("Conversion to int failed");
                }
            };
            type_converters["float"] = [](string s) {
                try {
                    return stof(s);
                } catch (...) {
                    throw runtime_error("Conversion to float failed");
                }
            };
            type_converters["bool"] = [](string s) {
                return !s.empty();
            };
        }
        return type_converters;
    }

public:
    ArgumentParser() {}

    void add_argument(const string& arg, bool required, const string& type_str) {
        if (required) {
            required.insert(arg);
        }
        types[arg] = type_str;
    }

    pair<bool, set<string>> parse_arguments(const string& command_string) {
        if (command_string.empty()) {
            set<string> missing_args = required;
            return make_pair(false, missing_args);
        }

        vector<string> tokens;
        istringstream iss(command_string);
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Skip the first token (usually the script name)
        if (!tokens.empty()) {
            tokens.erase(tokens.begin());
        }

        int i = 0;
        for (int index = 0; index < tokens.size(); ++index) {
            string token = tokens[index];
            if (token.empty()) {
                continue;
            }

            if (token[0] == '-') {
                string key;
                if (token.size() == 1) {
                    // This is an invalid option, skip
                    continue;
                }
                key = token.substr(1);

                if (index + 1 < tokens.size() && !tokens[index + 1].empty() && tokens[index + 1][0] != '-') {
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    string value = tokens[index + 1];
                    auto& converters = getTypeConverters();
                    if (converters.find(types[key]) == converters.end()) {
                        throw runtime_error("Unsupported type: " + types[key]);
                    }
                    try {
                        Variant value_variant = converters[types[key]](value);
                        arguments[key] = value_variant;
                    } catch (exception& e) {
                        arguments[key] = value;
                    }
                    ++index; // Skip the next token as it's used as value
                } else {
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    arguments[key] = true;
                }
            } else if (token[0] == '-') {
                // Handle long options starting with '-'
                // Note: Some systems use '-' for long options and '--' for short options, but the Python code uses '--' for long.
                // Since the Python code uses '--' for long options, we treat any option starting with '-' as short, and options starting with '--' as long.
                // But the Python code uses '--' for long options. Let's clarify: the Python code checks for '--' explicitly.
                // In the provided Python code, it checks for '--' for long options and '-' for short options.
                // We'll follow the same: tokens starting with '--' are long options.
                // So this section is not needed for long options, but for completeness, let's handle options starting with '-' as short and '--' as long.
                // But note: the Python code does not handle '--' for short options. We'll assume that the input might have long options starting with '--' and short options starting with '-'.
                // Since the Python code only checks for '--' for long options, we'll only handle '--' for long and '-' for short.
                // This section is for short options starting with '-'
                string key = token.substr(1);

                if (index + 1 < tokens.size() && !tokens[index + 1].empty() && tokens[index + 1][0] != '-') {
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    string value = tokens[index + 1];
                    auto& converters = getTypeConverters();
                    if (converters.find(types[key]) == converters.end()) {
                        throw runtime_error("Unsupported type: " + types[key]);
                    }
                    try {
                        Variant value_variant = converters[types[key]](value);
                        arguments[key] = value_variant;
                    } catch (exception& e) {
                        arguments[key] = value;
                    }
                    ++index; // Skip the next token as it's used as value
                } else {
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    arguments[key] = true;
                }
            } else if (token[0] == '-') {
                // Handle long options (starting with '--')
                // Extract the option name and value if present
                string rest = token.substr(1);
                size_t pos = rest.find('=');
                string key, value_str;
                if (pos != string::npos) {
                    key = rest.substr(0, pos);
                    value_str = rest.substr(pos + 1);
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    auto& converters = getTypeConverters();
                    if (converters.find(types[key]) == converters.end()) {
                        throw runtime_error("Unsupported type: " + types[key]);
                    }
                    try {
                        Variant value_variant = converters[types[key]](value_str);
                        arguments[key] = value_variant;
                    } catch (exception& e) {
                        arguments[key] = value_str;
                    }
                } else {
                    key = rest;
                    if (types.find(key) == types.end()) {
                        throw runtime_error("Unknown argument: " + key);
                    }
                    arguments[key] = true;
                }
            }
        }

        set<string> missing_args;
        for (const string& req : required) {
            if (arguments.find(req) == arguments.end()) {
                missing_args.insert(req);
            }
        }

        if (!missing_args.empty()) {
            return make_pair(false, missing_args);
        }

        return make_pair(true, set<string>());
    }

    Variant get_argument(const string& key) {
        if (arguments.find(key) != arguments.end()) {
            return arguments[key];
        }
        return Variant();
    }
};