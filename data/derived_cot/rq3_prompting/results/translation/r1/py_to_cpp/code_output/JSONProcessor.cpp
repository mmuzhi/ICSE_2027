#include <iostream>
#include <fstream>
#include <filesystem>
#include <variant>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JSONProcessor {
public:
    // Read a JSON file and return the data.
    // Returns 0 if file does not exist, -1 on parse error, or the JSON object on success.
    std::variant<int, json> read_json(const std::string& file_path) {
        if (!std::filesystem::exists(file_path)) {
            return 0;
        }
        try {
            std::ifstream file(file_path);
            if (!file.is_open()) {
                return -1;
            }
            json data;
            file >> data;
            return data;
        } catch (...) {
            return -1;
        }
    }

    // Write data to a JSON file and save it to the given path.
    // Returns 1 on success, -1 on error.
    int write_json(const json& data, const std::string& file_path) {
        try {
            std::ofstream file(file_path);
            if (!file.is_open()) {
                return -1;
            }
            file << data.dump(4); // Pretty-print with indent 4 (like json.dump default)
            return 1;
        } catch (...) {
            return -1;
        }
    }

    // Read a JSON file, remove the specified key, and rewrite the file.
    // Returns 1 if the key was removed and file written; 0 if file missing, parse error, or key not found.
    int process_json(const std::string& file_path, const std::string& remove_key) {
        auto result = read_json(file_path);
        // Check if result is an error code (0 or -1)
        if (std::holds_alternative<int>(result) &&
            (std::get<int>(result) == 0 || std::get<int>(result) == -1)) {
            return 0;
        }
        // result is a valid json object
        json data = std::get<json>(result);
        if (data.contains(remove_key)) {
            data.erase(remove_key);
            write_json(data, file_path);  // Ignore return value as original Python does
            return 1;
        } else {
            return 0;
        }
    }
};