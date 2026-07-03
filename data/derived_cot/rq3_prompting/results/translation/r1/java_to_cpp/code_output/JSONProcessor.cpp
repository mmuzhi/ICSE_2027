#include <string>
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JSONProcessor {
public:
    json readJson(const std::string& filePath) {
        if (!std::filesystem::exists(filePath)) {
            return json(); // null
        }
        try {
            std::ifstream ifs(filePath);
            if (!ifs.is_open()) {
                return json();
            }
            json data = json::parse(ifs);
            // Mimic Java's Map.class deserialization: only objects are accepted
            if (!data.is_object()) {
                return json();
            }
            return data;
        } catch (...) {
            return json();
        }
    }

    bool writeJson(const json& data, const std::string& filePath) {
        try {
            std::ofstream ofs(filePath);
            if (!ofs.is_open()) {
                return false;
            }
            ofs << data;
            return true;
        } catch (...) {
            return false;
        }
    }

    bool processJson(const std::string& filePath, const std::string& removeKey) {
        json data = readJson(filePath);
        if (data.is_null()) {
            return false;
        }
        // data is guaranteed to be an object after readJson, but check for safety
        if (data.is_object() && data.contains(removeKey)) {
            data.erase(removeKey);
            return writeJson(data, filePath);
        } else {
            return false;
        }
    }
};