#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    json read_file_as_json() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }
        json j;
        file >> j;
        return j;
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + file_path);
        }
        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string processed = std::regex_replace(content, std::regex("[^a-zA-Z]"), "");
        write_file(processed);
        return processed;
    }
};