#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>

using json = nlohmann::json;

class JSONProcessor {
public:
    json read_json(const std::string& filePath) {
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

    bool write_json(const json& data, const std::string& filePath) {
        std::ofstream output(filePath);
        try {
            output << data.dump(4) << std::endl;
            return true;
        } catch (...) {
            return false;
        }
    }

    bool process_json(const std::string& filePath, const std::string& removeKey) {
        json data = read_json(filePath);
        if (data.empty()) {
            return false;
        }
        if (data.find(removeKey) != data.end()) {
            data.erase(removeKey);
            return write_json(data, filePath);
        } else {
            return false;
        }
    }
};