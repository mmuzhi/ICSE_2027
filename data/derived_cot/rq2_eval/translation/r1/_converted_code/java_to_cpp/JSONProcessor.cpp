#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;
using json = nlohmann::json;

class JSONProcessor {
public:
    json read_json(const std::string& filePath) {
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

    bool write_json(const json& data, const std::string& filePath) {
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

    bool process_json(const std::string& filePath, const std::string& removeKey) {
        json data = read_json(filePath);
        if (data.is_null()) {
            return false;
        }
        if (data.contains(removeKey)) {
            data.erase(removeKey);
            return write_json(data, filePath);
        } else {
            return false;
        }
    }
};