#include <zip>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <memory>

namespace fs = std::filesystem;

class ZipFileProcessor {
private:
    std::string file_name;

public:
    explicit ZipFileProcessor(const std::string& file_name) : file_name(file_name) {}

    std::unique_ptr<std::zip_file> read_zip_file() {
        try {
            return std::make_unique<std::zip_file>(file_name, std::ios::in);
        } catch (...) {
            return nullptr;
        }
    }

    bool extract_all(const std::string& output_path) {
        try {
            std::zip_file zip(file_name, std::ios::in);
            for (const auto& entry : zip) {
                if (entry.is_directory()) continue;
                std::ofstream out(output_path + "/" + entry.name(), std::ios::binary);
                out << entry;
            }
            return true;
        } catch (...) {
            return false;
        }
    }

    bool extract_file(const std::string& file_name, const std::string& output_path) {
        try {
            std::zip_file zip(file_name, std::ios::in); // Note: 'file_name' here refers to the zip file
            for (const auto& entry : zip) {
                if (entry.name() == file_name && !entry.is_directory()) {
                    std::ofstream out(output_path + "/" + file_name, std::ios::binary);
                    out << entry;
                    return true;
                }
            }
            return false;
        } catch (...) {
            return false;
        }
    }

    bool create_zip_file(const std::vector<std::string>& files, const std::string& output_file_name) {
        try {
            std::zip_file zip(output_file_name, std::ios::out);
            for (const auto& file : files) {
                std::ifstream in(file, std::ios::binary);
                zip << in.rdbuf();
            }
            return true;
        } catch (...) {
            return false;
        }
    }
};