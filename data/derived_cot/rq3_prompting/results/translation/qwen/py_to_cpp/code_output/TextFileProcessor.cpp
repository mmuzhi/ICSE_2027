#include <fstream>
#include <string>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <cctype>

class TextFileProcessor {
public:
    TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    template<typename T>
    T read_file_as_json() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for JSON reading");
        }

        nlohmann::json json_data;
        file >> json_data;
        return json_data.get<T>();
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for reading");
        }

        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line;
        }
        return content;
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file for writing");
        }

        file << content;
    }

    std::string process_file() {
        std::string content = read_file();
        std::string processed;
        for (char c : content) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                processed += c;
            }
        }
        write_file(processed);
        return processed;
    }

private:
    std::string file_path;
};