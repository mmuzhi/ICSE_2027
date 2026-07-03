#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>

using json = nlohmann::json;

class JSONProcessor {
public:
    json readJson(const std::string& filePath) {
        if (!std::filesystem::exists(filePath)) {
            return json();
        }
        std::ifstream input(filePath);
        try {
            return json::parse(input);
        } catch (...) {
            return json();
        }
    }

    bool writeJson(const json& data, const std::string& filePath) {
        std::ofstream output(filePath);
        try {
            output << data.dump(4) << std::endl;
            return true;
        } catch (...) {
            return false;
        }
    }

    bool processJson(const std::string& filePath, const std::string& removeKey) {
        json data = readJson(filePath);
        if (data.empty()) {
            return false;
        }
        if (data.find(removeKey) != data.end()) {
            data.erase(removeKey);
            return writeJson(data, filePath);
        } else {
            return false;
        }
    }
};