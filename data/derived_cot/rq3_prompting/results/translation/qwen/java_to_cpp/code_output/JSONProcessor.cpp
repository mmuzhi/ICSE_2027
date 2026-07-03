#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class JSONProcessor {
public:
    nlohmann::json readJson(const std::string& filePath) {
        if (!fs::exists(filePath)) {
            return nlohmann::json(nullptr);
        }
        try {
            std::ifstream i(filePath);
            return nlohmann::json::parse(i);
        } catch (...) {
            return nlohmann::json(nullptr);
        }
    }

    bool writeJson(const nlohmann::json& data, const std::string& filePath) {
        try {
            std::ofstream o(filePath);
            o << data.dump(0); // 0 for no indentation
            return true;
        } catch (...) {
            return false;
        }
    }

    bool processJson(const std::string& filePath, const std::string& removeKey) {
        nlohmann::json data = readJson(filePath);
        if (data.is_null()) {
            return false;
        }
        if (data.contains(removeKey)) {
            data.erase(removeKey);
            return writeJson(data, filePath);
        }
        return false;
    }
};