#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <nlohmann/json.hpp>

class TextFileProcessor {
public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    nlohmann::json read_file_as_json() {
        std::ifstream file(file_path);
        nlohmann::json data;
        file >> data;
        return data;
    }

    std::string read_file() {
        std::ifstream file(file_path);
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string filtered;
        filtered.reserve(content.size());
        for (char c : content) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                filtered += c;
            }
        }
        write_file(filtered);
        return filtered;
    }

private:
    std::string file_path;
};