#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
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
            throw std::runtime_error("Could not open file: " + file_path);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return json::parse(buffer.str());
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + file_path);
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing: " + file_path);
        }
        file << content;
        file.close();
    }

    std::string process_file() {
        std::string content = read_file();
        std::string filtered;
        filtered.reserve(content.size());
        std::copy_if(content.begin(), content.end(), std::back_inserter(filtered),
                     [](unsigned char c) { return std::isalpha(c); });
        write_file(filtered);
        return filtered;
    }
};