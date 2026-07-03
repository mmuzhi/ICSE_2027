#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <regex>
#include <nlohmann/json.hpp>

class TextFileProcessor {
private:
    std::string file_path;

public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    nlohmann::json read_file_as_json() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }
        nlohmann::json result;
        file >> result;
        return result;
    }

    std::string read_file() {
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_path);
        }
        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string processedContent = std::regex_replace(content, std::regex("[^a-zA-Z]"), "");
        write_file(processedContent);
        return processedContent;
    }
};