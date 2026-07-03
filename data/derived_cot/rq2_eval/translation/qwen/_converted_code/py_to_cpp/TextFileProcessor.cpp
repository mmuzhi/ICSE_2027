#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <cctype>

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    nlohmann::json read_file_as_json() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        nlohmann::json data;
        file >> data;
        return data;
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }
        std::string content((std::istreambuf_iterator<char>(file)), 
                          (std::istreambuf_iterator<char>()));
        return content;
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }
        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string filtered;
        for (char c : content) {
            if (std::isalpha(c)) {
                filtered += c;
            }
        }
        write_file(filtered);
        return filtered;
    }
};