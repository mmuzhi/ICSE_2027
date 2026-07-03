#include <variant>
#include <filesystem>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace nlohmann;

class JSONProcessor {
public:
    std::variant<int, json> read_json(const std::string& file_path) {
        if (!std::filesystem::exists(file_path)) {
            return 0;
        }
        std::ifstream i(file_path);
        if (!i.is_open()) {
            return -1;
        }
        json j;
        i >> j;
        if (i.fail()) {
            return -1;
        }
        return j;
    }

    int write_json(const json& data, const std::string& file_path) {
        std::ofstream o(file_path);
        o << data;
        if (o.fail()) {
            return -1;
        }
        return 1;
    }

    int process_json(const std::string& file_path, const std::string& remove_key) {
        auto result = read_json(file_path);
        if (std::holds_alternative<int>(result)) {
            return 0;
        }
        json& data = std::get<json>(result);
        if (data.find(remove_key) != data.end()) {
            data.erase(remove_key);
            write_json(data, file_path);
            return 1;
        }
        return 0;
    }
};