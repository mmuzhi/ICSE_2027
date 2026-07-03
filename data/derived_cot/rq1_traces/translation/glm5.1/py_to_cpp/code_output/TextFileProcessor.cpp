#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <algorithm>
#include <iterator>

// Requires the nlohmann/json library to handle JSON parsing identically to Python
// https://github.com/nlohmann/json
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
            throw std::runtime_error("File not found or cannot be opened: " + file_path);
        }
        
        try {
            // nlohmann::json::parse automatically infers the JSON type 
            // (dict, list, str, int, etc.) matching Python's json.load behavior
            return json::parse(file);
        } catch (const json::parse_error& e) {
            // Propagate JSON parse errors similar to Python's json.JSONDecodeError
            throw std::runtime_error(std::string("JSON parse error: ") + e.what());
        }
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("File not found or cannot be opened: " + file_path);
        }
        
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
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
        std::string filtered_content;
        filtered_content.reserve(content.size());

        // Filter out non-alphabetic characters.
        // static_cast<unsigned char> is required to safely handle non-ASCII chars 
        // and prevent undefined behavior with std::isalpha.
        std::copy_if(content.begin(), content.end(), std::back_inserter(filtered_content),
                     [](char c) { return std::isalpha(static_cast<unsigned char>(c)); });

        write_file(filtered_content);
        return filtered_content;
    }
};