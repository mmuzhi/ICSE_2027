#include <fstream>
#include <string>
#include <cctype>
#include <stdexcept>
#include "json.hpp"

using json = nlohmann::json;

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    json read_file_as_json() {
        std::string content = read_file();
        return json::parse(content);
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file) {
            throw std::runtime_error("Could not open file: " + file_path);
        }
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }

    template <typename T>
    void write_file(const T& content) {
        std::ofstream file(file_path);
        if (!file) {
            throw std::runtime_error("Could not open file for writing: " + file_path);
        }
        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string processed;
        for (char c : content) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                processed.push_back(c);
            }
        }
        write_file(processed);
        return processed;
    }
};