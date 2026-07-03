#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

class TextFileProcessor {
private:
    std::string file_path;

public:
    explicit TextFileProcessor(const std::string& file_path) : file_path(file_path) {}

    std::string read_file_as_json() {
        std::ifstream file(file_path, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        file.seekg(0, std::ios::end);
        std::size_t size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        file.read(buffer.data(), size);
        std::string content(buffer.begin(), buffer.end());
        file.close();

        return content;
    }

    std::string read_file() {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string content;
        std::string line;
        while (std::getline(file, line)) {
            content += line;
        }
        file.close();

        return content;
    }

    void write_file(const std::string& content) {
        std::ofstream file(file_path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to write file");
        }

        file << content;
        file.close();
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
};