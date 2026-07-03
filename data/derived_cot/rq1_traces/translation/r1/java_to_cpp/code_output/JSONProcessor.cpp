#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using json = nlohmann::json;

class JSONProcessor {
public:
    json readJson(const std::string& filePath) {
        if (!fs::exists(filePath)) {
            return nullptr;
        }
        try {
            std::ifstream i(filePath);
            if (!i.is_open() || !i.good()) {
                return nullptr;
            }
            json j = json::parse(i);
            if (j.is_object()) {
                return j;
            } else {
                return nullptr;
            }
        } catch (...) {
            return nullptr;
        }
    }

    bool writeJson(const json& data, const std::string& filePath) {
        if (!data.is_object()) {
            return false;
        }
        try {
            std::ofstream o(filePath);
            if (!o.is_open() || !o.good()) {
                return false;
            }
            o << data;
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
        if (data.contains(removeKey)) {
            data.erase(removeKey);
            return writeJson(data, filePath);
        } else {
            return false;
        }
    }
};