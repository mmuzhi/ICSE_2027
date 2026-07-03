#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <string>

using json = nlohmann::json;

class JSONProcessor {
public:
    int read_json(const std::string& file_path) {
        if (!std::filesystem::exists(file_path)) {
            return 0;
        }
        try {
            std::ifstream file(file_path);
            json data = json::parse(file);
            return data;
        } catch (...) {
            return -1;
        }
    }

    int write_json(const json& data, const std::string& file_path) {
        try {
            std::ofstream file(file_path);
            data.dump(file);
            return 1;
        } catch (...) {
            return -1;
        }
    }

    int process_json(const std::string& file_path, const std::string& remove_key) {
        auto data = read_json(file_path);
        if (data == 0 || data == -1) {
            return 0;
        }
        if (data.is_object() && data.find(remove_key) != data.end()) {
            data.erase(remove_key);
            write_json(data, file_path);
            return 1;
        }
        return 0;
    }
};