#include <string>
#include <vector>
#include <memory>
#include <miniz_cpp.hpp>

class ZipFileProcessor {
public:
    ZipFileProcessor(std::string file_name) : file_name_(std::move(file_name)) {}

    std::unique_ptr<miniz_cpp::zip_file> read_zip_file() {
        try {
            auto zip_file = std::make_unique<miniz_cpp::zip_file>();
            zip_file->load(file_name_);
            return zip_file;
        } catch (...) {
            return nullptr;
        }
    }

    bool extract_all(const std::string& output_path) {
        try {
            miniz_cpp::zip_file zip_file;
            zip_file.load(file_name_);
            zip_file.extractall(output_path);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool extract_file(const std::string& file_name, const std::string& output_path) {
        try {
            miniz_cpp::zip_file zip_file;
            zip_file.load(file_name_);
            zip_file.extract(file_name, output_path);
            return true;
        } catch (...) {
            return false;
        }
    }

    bool create_zip_file(const std::vector<std::string>& files, const std::string& output_file_name) {
        try {
            miniz_cpp::zip_file zip_file;
            for (const auto& file : files) {
                zip_file.write(file);
            }
            zip_file.save(output_file_name);
            return true;
        } catch (...) {
            return false;
        }
    }

private:
    std::string file_name_;
};