#include <zip.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cerrno>

class ZipFileProcessor {
private:
    std::string file_name;

    // Create directories recursively for a given path.
    static bool create_directories(const std::string& path) {
        size_t pos = 0;
        std::string current;
        while ((pos = path.find_first_of("/\\", pos)) != std::string::npos) {
            current = path.substr(0, pos);
            if (!current.empty()) {
                mkdir(current.c_str(), 0755);
            }
            pos++;
        }
        // Create the final directory if path ends with separator
        if (!path.empty() && (path.back() == '/' || path.back() == '\\')) {
            mkdir(path.c_str(), 0755);
        }
        return true; // mkdir may fail if exists, that's fine
    }

public:
    ZipFileProcessor(const std::string& file_name) : file_name(file_name) {}

    // Returns a zip_t* pointer on success, nullptr on failure.
    zip_t* read_zip_file() {
        int err = 0;
        zip_t* z = zip_open(file_name.c_str(), ZIP_RDONLY, &err);
        if (z == nullptr) {
            return nullptr;
        }
        return z;
    }

    bool extract_all(const std::string& output_path) {
        zip_t* z = zip_open(file_name.c_str(), ZIP_RDONLY, nullptr);
        if (z == nullptr) return false;

        bool success = true;
        zip_int64_t num_entries = zip_get_num_entries(z, 0);
        for (zip_int64_t i = 0; i < num_entries; ++i) {
            const char* name = zip_get_name(z, i, 0);
            if (name == nullptr) {
                success = false;
                break;
            }

            std::string full_path = output_path + "/" + name;

            // If the entry is a directory (name ends with '/'), create it.
            size_t len = strlen(name);
            if (len > 0 && name[len - 1] == '/') {
                create_directories(full_path);
                continue;
            }

            // Ensure parent directories exist.
            size_t last_slash = full_path.find_last_of("/\\");
            if (last_slash != std::string::npos) {
                create_directories(full_path.substr(0, last_slash));
            }

            // Read file contents and write to disk.
            zip_file_t* zf = zip_fopen_index(z, i, 0);
            if (zf == nullptr) {
                success = false;
                break;
            }

            std::ofstream out(full_path, std::ios::binary);
            if (!out.is_open()) {
                zip_fclose(zf);
                success = false;
                break;
            }

            char buf[4096];
            zip_int64_t n;
            while ((n = zip_fread(zf, buf, sizeof(buf))) > 0) {
                out.write(buf, n);
            }
            out.close();
            zip_fclose(zf);

            if (n < 0) {
                success = false;
                break;
            }
        }

        zip_close(z);
        return success;
    }

    bool extract_file(const std::string& file_name, const std::string& output_path) {
        zip_t* z = zip_open(this->file_name.c_str(), ZIP_RDONLY, nullptr);
        if (z == nullptr) return false;

        // Look for the file inside the archive.
        zip_stat_t stat;
        if (zip_stat(z, file_name.c_str(), 0, &stat) != 0) {
            zip_close(z);
            return false;
        }

        // Ensure output directory exists.
        size_t last_slash = output_path.find_last_of("/\\");
        if (last_slash != std::string::npos) {
            create_directories(output_path.substr(0, last_slash));
        } else {
            create_directories(output_path);
        }

        // Open the entry.
        zip_file_t* zf = zip_fopen(z, file_name.c_str(), 0);
        if (zf == nullptr) {
            zip_close(z);
            return false;
        }

        std::string out_path = output_path;
        // If output_path ends with a directory separator, append the file name.
        if (!out_path.empty() && (out_path.back() == '/' || out_path.back() == '\\')) {
            out_path += file_name;
        }

        std::ofstream out(out_path, std::ios::binary);
        if (!out.is_open()) {
            zip_fclose(zf);
            zip_close(z);
            return false;
        }

        char buf[4096];
        zip_int64_t n;
        while ((n = zip_fread(zf, buf, sizeof(buf))) > 0) {
            out.write(buf, n);
        }
        out.close();
        zip_fclose(zf);
        zip_close(z);

        return (n >= 0);
    }

    bool create_zip_file(const std::vector<std::string>& files, const std::string& output_file_name) {
        // Remove existing file if present.
        std::remove(output_file_name.c_str());

        zip_t* z = zip_open(output_file_name.c_str(), ZIP_CREATE | ZIP_TRUNCATE, nullptr);
        if (z == nullptr) return false;

        bool success = true;
        for (const auto& file : files) {
            // Use the local file name as the archive entry name.
            zip_source_t* source = zip_source_file(z, file.c_str(), 0, 0);
            if (source == nullptr) {
                success = false;
                break;
            }

            // Extract the base name for the entry.
            size_t last_sep = file.find_last_of("/\\");
            std::string entry_name = (last_sep == std::string::npos) ? file : file.substr(last_sep + 1);

            zip_int64_t index = zip_file_add(z, entry_name.c_str(), source, ZIP_FL_OVERWRITE);
            if (index < 0) {
                zip_source_free(source);
                success = false;
                break;
            }
        }

        zip_close(z);
        return success;
    }
};