#include <fstream>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    nlohmann::json read_file_as_json() {
        try {
            std::ifstream file(file_path);
            return nlohmann::json::parse(file);
        } catch (const std::exception& e) {
            throw std::ios_base::failure("Error reading JSON file: " + std::string(e.what()));
        }
    }

    std::string read_file() {
        try {
            std::ifstream file(file_path, std::ios::binary);
            std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
            return content;
        } catch (const std::exception& e) {
            throw std::ios_base::failure("Error reading file: " + std::string(e.what()));
        }
    }

    void write_file(const std::string& content) {
        try {
            std::ofstream file(file_path, std::ios::binary);
            file.write(content.data(), content.size());
            file.close();
        } catch (const std::exception& e) {
            throw std::ios_base::failure("Error writing file: " + std::string(e.what()));
        }
    }

    std::string process_file() {
        try {
            std::string content = read_file();
            std::string processedContent;
            for (char c : content) {
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    processedContent += c;
                }
            }
            write_file(processedContent);
            return processedContent;
        } catch (const std::exception& e) {
            throw std::ios_base::failure("Error processing file: " + std::string(e.what()));
        }
    }
};