#include <fstream>
#include <stdexcept>
#include <string>
#include <regex>
#include <nlohmann/json.hpp>

using nlohmann::json;

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    json read_file_as_json() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        json j;
        file >> j;
        return j;
    }

    std::string read_file() {
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        file.write(content.c_str(), content.size());
    }

    std::string process_file() {
        std::string content = read_file();
        std::regex pattern("[^a-zA-Z]");
        std::string processedContent = std::regex_replace(content, pattern, "");
        write_file(processedContent);
        return processedContent;
    }
};