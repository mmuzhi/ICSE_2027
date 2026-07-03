#include <zip.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstring>

namespace fs = std::filesystem;

enum class Level {
    SEVERE,
    WARNING,
    INFO
};

class Logger {
public:
    Logger(const std::string& name) : name_(name) {}

    void log(Level level, const std::string& msg) {
        const char* levelStr = "";
        switch (level) {
            case Level::SEVERE: levelStr = "SEVERE"; break;
            case Level::WARNING: levelStr = "WARNING"; break;
            case Level::INFO: levelStr = "INFO"; break;
        }
        std::cerr << "[" << name_ << "] " << levelStr << ": " << msg << std::endl;
    }

    void log(Level level, const std::string& msg, const std::exception& e) {
        log(level, msg + ": " + e.what());
    }

    void severe(const std::string& msg) { log(Level::SEVERE, msg); }
    void warning(const std::string& msg) { log(Level::WARNING, msg); }
    void info(const std::string& msg) { log(Level::INFO, msg); }

    static Logger getLogger(const std::string& name) {
        return Logger(name);
    }

private:
    std::string name_;
};

struct ZipEntry {
    std::string name;
    bool isDirectory;
};

class ZipFile {
public:
    explicit ZipFile(zip_t* handle) : handle_(handle) {}

    ~ZipFile() {
        if (handle_) {
            zip_close(handle_);
        }
    }

    ZipFile(const ZipFile&) = delete;
    ZipFile& operator=(const ZipFile&) = delete;

    ZipFile(ZipFile&& other) noexcept : handle_(other.handle_) {
        other.handle_ = nullptr;
    }

    ZipFile& operator=(ZipFile&& other) noexcept {
        if (this != &other) {
            if (handle_) {
                zip_close(handle_);
            }
            handle_ = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }

    bool isValid() const { return handle_ != nullptr; }

    std::vector<ZipEntry> entries() {
        std::vector<ZipEntry> result;
        zip_int64_t num_entries = zip_get_num_entries(handle_, 0);
        for (zip_int64_t i = 0; i < num_entries; i++) {
            struct zip_stat sb;
            if (zip_stat_index(handle_, i, 0, &sb) != 0) {
                continue;
            }
            std::string name = sb.name;
            bool isDirectory = (sb.valid & ZIP_STAT_NAME) && name.back() == '/';
            result.push_back({name, isDirectory});
        }
        return result;
    }

    std::optional<ZipEntry> getEntry(const std::string& name) {
        zip_int64_t index = zip_name_locate(handle_, name.c_str(), 0);
        if (index < 0) {
            return std::nullopt;
        }
        struct zip_stat sb;
        if (zip_stat_index(handle_, index, 0, &sb) != 0) {
            return std::nullopt;
        }
        std::string entryName = sb.name;
        bool isDirectory = (sb.valid & ZIP_STAT_NAME) && entryName.back() == '/';
        return ZipEntry{entryName, isDirectory};
    }

    bool extractEntry(const ZipEntry& entry, const fs::path& filePath) {
        zip_int64_t index = zip_name_locate(handle_, entry.name.c_str(), 0);
        if (index < 0) {
            return false;
        }

        zip_file_t* file = zip_fopen_index(handle_, index, 0);
        if (!file) {
            return false;
        }

        try {
            std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
            if (!out) {
                zip_fclose(file);
                return false;
            }

            char buffer[1024];
            zip_int64_t len;
            while ((len = zip_fread(file, buffer, sizeof(buffer))) {
                if (len < 0) {
                    zip_fclose(file);
                    return false;
                }
                out.write(buffer, len);
                if (!out) {
                    zip_fclose(file);
                    return false;
                }
            }
            zip_fclose(file);
            return true;
        } catch (...) {
            zip_fclose(file);
            return false;
        }
    }

private:
    zip_t* handle_;
};

class ZipFileProcessor {
private:
    fs::path zipFilePath;
    static Logger logger;

public:
    ZipFileProcessor(const std::string& zipFileName) : zipFilePath(zipFileName) {}

    std::unique_ptr<ZipFile> readZipFile() {
        if (!fs::exists(zipFilePath)) {
            logger.severe("Zip file does not exist: " + zipFilePath.string());
            return nullptr;
        }

        int err;
        zip_t* handle = zip_open(zipFilePath.c_str(), ZIP_RDONLY, &err);
        if (!handle) {
            char error_str[100];
            zip_error_to_str(error_str, sizeof(error_str), err, errno);
            logger.severe("Failed to read the zip file: " + zipFilePath.string() + " - " + error_str);
            return nullptr;
        }
        return std::make_unique<ZipFile>(handle);
    }

    bool extract_all(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        auto zipFile = readZipFile();
        if (!zipFile || !zipFile->isValid()) {
            return false;
        }

        if (!fs::exists(outputDirPath)) {
            try {
                fs::create_directories(outputDirPath);
                logger.info("Created output directory: " + outputDirPath.string());
            } catch (const std::exception& e) {
                logger.log(Level::SEVERE, "Failed to create output directory: " + outputDirPath.string(), e);
                return false;
            }
        }

        auto entries = zipFile->entries();
        for (const auto& entry : entries) {
            fs::path filePath = outputDirPath / entry.name;
            try {
                if (entry.isDirectory) {
                    if (!fs::exists(filePath)) {
                        fs::create_directories(filePath);
                        logger.info("Created directory: " + filePath.string());
                    }
                } else {
                    fs::path parentPath = filePath.parent_path();
                    if (!fs::exists(parentPath)) {
                        fs::create_directories(parentPath);
                    }
                    if (zipFile->extractEntry(entry, filePath)) {
                        logger.info("Extracted file: " + filePath.string());
                    } else {
                        logger.severe("Failed to extract file: " + filePath.string());
                    }
                }
            } catch (const std::exception& e) {
                logger.log(Level::SEVERE, "Failed to process entry: " + entry.name, e);
            }
        }
        return true;
    }

    bool extract_file(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        fs::path filePath = outputDirPath / fileName;
        auto zipFile = readZipFile();
        if (!zipFile || !zipFile->isValid()) {
            return false;
        }

        auto entry = zipFile->getEntry(fileName);
        if (!entry) {
            logger.warning("File not found in zip: " + fileName);
            return false;
        }

        fs::path parentPath = filePath.parent_path();
        if (!fs::exists(parentPath)) {
            try {
                fs::create_directories(parentPath);
                logger.info("Created parent directory: " + parentPath.string());
            } catch (const std::exception& e) {
                logger.log(Level::SEVERE, "Failed to create parent directory: " + parentPath.string(), e);
                return false;
            }
        }

        if (zipFile->extractEntry(*entry, filePath)) {
            logger.info("Extracted file: " + filePath.string());
            return true;
        } else {
            logger.severe("Failed to extract file: " + fileName);
            return false;
        }
    }
};

Logger ZipFileProcessor::logger = Logger::getLogger("ZipFileProcessor");