#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <zip.h>

namespace fs = std::filesystem;

// ============================================================================
// Simple Logger mimicking java.util.logging.Logger
// ============================================================================
class Logger {
public:
    enum Level { SEVERE, WARNING, INFO };

    static Logger* getLogger(const std::string& name) {
        static Logger instance(name);
        return &instance;
    }

    void log(Level level, const std::string& message) {
        const char* levelStr = "";
        switch (level) {
            case SEVERE:  levelStr = "SEVERE";  break;
            case WARNING: levelStr = "WARNING"; break;
            case INFO:    levelStr = "INFO";    break;
        }
        std::cerr << levelStr << ": " << message << std::endl;
    }

    // Mimics Java's log(Level, String, Throwable)
    void log(Level level, const std::string& message, const std::exception& e) {
        log(level, message + " - " + e.what());
    }

    void info(const std::string& message)    { log(INFO, message); }
    void warning(const std::string& message) { log(WARNING, message); }
    void severe(const std::string& message)  { log(SEVERE, message); }

private:
    explicit Logger(const std::string& name) : name_(name) {}
    std::string name_;
};

// ============================================================================
// Represents a single entry in a zip file
// ============================================================================
struct ZipEntry {
    std::string name;
    bool isDirectory;
    zip_uint64_t index;
};

// ============================================================================
// RAII wrapper around libzip's zip_t
// ============================================================================
class ZipFile {
public:
    explicit ZipFile(const fs::path& path) : path_(path), zip_(nullptr) {
        int error = 0;
        zip_ = zip_open(path.string().c_str(), ZIP_RDONLY, &error);
        if (!zip_) {
            throw std::runtime_error(
                "Failed to open zip file: " + path.string() +
                " (error code: " + std::to_string(error) + ")");
        }
    }

    ~ZipFile() {
        if (zip_) {
            zip_close(zip_);
        }
    }

    // Non-copyable
    ZipFile(const ZipFile&) = delete;
    ZipFile& operator=(const ZipFile&) = delete;

    // Movable
    ZipFile(ZipFile&& other) noexcept
        : zip_(other.zip_), path_(std::move(other.path_)) {
        other.zip_ = nullptr;
    }
    ZipFile& operator=(ZipFile&& other) noexcept {
        if (this != &other) {
            if (zip_) zip_close(zip_);
            zip_ = other.zip_;
            path_ = std::move(other.path_);
            other.zip_ = nullptr;
        }
        return *this;
    }

    // Returns a pointer to a ZipEntry (caller must delete), or nullptr if not found
    ZipEntry* getEntry(const std::string& name) const {
        zip_int64_t idx = zip_name_locate(zip_, name.c_str(), 0);
        if (idx < 0) return nullptr;

        zip_stat_t stat;
        if (zip_stat_index(zip_, static_cast<zip_uint64_t>(idx), 0, &stat) != 0)
            return nullptr;

        bool isDir = (stat.name[std::strlen(stat.name) - 1] == '/');
        return new ZipEntry{stat.name, isDir, static_cast<zip_uint64_t>(idx)};
    }

    // Returns all entries in the order they appear in the zip file
    std::vector<ZipEntry> entries() const {
        std::vector<ZipEntry> result;
        zip_int64_t count = zip_get_num_entries(zip_, 0);
        for (zip_int64_t i = 0; i < count; ++i) {
            zip_stat_t stat;
            if (zip_stat_index(zip_, static_cast<zip_uint64_t>(i), 0, &stat) == 0) {
                bool isDir = (stat.name[std::strlen(stat.name) - 1] == '/');
                result.push_back({stat.name, isDir, static_cast<zip_uint64_t>(i)});
            }
        }
        return result;
    }

    // Reads the entire content of a zip entry into a byte buffer
    std::vector<char> readEntry(const ZipEntry& entry) const {
        zip_file_t* zf = zip_fopen_index(zip_, entry.index, 0);
        if (!zf) {
            throw std::runtime_error("Failed to open entry in zip: " + entry.name);
        }

        std::vector<char> buffer(1024);
        std::vector<char> result;
        zip_int64_t len;
        while ((len = zip_fread(zf, buffer.data(), buffer.size())) > 0) {
            result.insert(result.end(), buffer.begin(), buffer.begin() + len);
        }
        zip_fclose(zf);
        return result;
    }

private:
    zip_t* zip_;
    fs::path path_;
};

// ============================================================================
// ZipFileProcessor - equivalent to the Java class
// ============================================================================
class ZipFileProcessor {
private:
    static Logger* logger;
    fs::path zipFilePath;

    // Package-private in Java; made private here since C++ has no package concept
    std::unique_ptr<ZipFile> readZipFile() {
        if (!fs::exists(zipFilePath)) {
            logger->log(Logger::SEVERE,
                "Zip file does not exist: " + fs::absolute(zipFilePath).string());
            return nullptr;
        }
        try {
            return std::make_unique<ZipFile>(zipFilePath);
        } catch (const std::exception& e) {
            logger->log(Logger::SEVERE,
                "Failed to read the zip file: " + fs::absolute(zipFilePath).string(), e);
            return nullptr;
        }
    }

public:
    explicit ZipFileProcessor(const std::string& zipFileName)
        : zipFilePath(zipFileName) {}

    bool extractAll(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        auto zipFile = readZipFile();
        if (!zipFile) return false;

        try {
            if (!fs::exists(outputDirPath)) {
                try {
                    fs::create_directories(outputDirPath);
                    logger->info("Created output directory: " +
                        fs::absolute(outputDirPath).string());
                } catch (const fs::filesystem_error& e) {
                    logger->log(Logger::SEVERE,
                        "Failed to create output directory: " +
                        fs::absolute(outputDirPath).string(), e);
                    return false;
                }
            }

            auto allEntries = zipFile->entries();
            for (const auto& entry : allEntries) {
                fs::path filePath = outputDirPath / entry.name;
                try {
                    if (entry.isDirectory) {
                        if (!fs::exists(filePath)) {
                            fs::create_directories(filePath);
                            logger->info("Created directory: " +
                                fs::absolute(filePath).string());
                        }
                    } else {
                        auto content = zipFile->readEntry(entry);
                        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
                        if (!out) {
                            throw std::runtime_error(
                                "Failed to open output file: " + filePath.string());
                        }
                        out.write(content.data(), content.size());
                        out.close();
                        logger->info("Extracted file: " +
                            fs::absolute(filePath).string());
                    }
                } catch (const std::exception& e) {
                    logger->log(Logger::SEVERE,
                        "Failed to process entry: " + entry.name, e);
                }
            }

            return true;
        } catch (const std::exception& e) {
            logger->log(Logger::SEVERE,
                "Failed to extract files from zip: " +
                fs::absolute(zipFilePath).string(), e);
            return false;
        }
    }

    bool extractFile(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        fs::path filePath = outputDirPath / fileName;

        auto zipFile = readZipFile();
        if (!zipFile) return false;

        try {
            std::unique_ptr<ZipEntry> entry(zipFile->getEntry(fileName));
            if (!entry) {
                logger->warning("File not found in zip: " + fileName);
                return false;
            }

            fs::path parentPath = filePath.parent_path();
            // Guard against empty parent (fileName has no directory component)
            if (!parentPath.empty() && !fs::exists(parentPath)) {
                try {
                    fs::create_directories(parentPath);
                    logger->info("Created parent directory: " +
                        fs::absolute(parentPath).string());
                } catch (const fs::filesystem_error& e) {
                    logger->log(Logger::SEVERE,
                        "Failed to create parent directory: " +
                        fs::absolute(parentPath).string(), e);
                    return false;
                }
            }

            auto content = zipFile->readEntry(*entry);
            std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
            if (!out) {
                throw std::runtime_error(
                    "Failed to open output file: " + filePath.string());
            }
            out.write(content.data(), content.size());
            out.close();
            logger->info("Extracted file: " + fs::absolute(filePath).string());

            return true;
        } catch (const std::exception& e) {
            logger->log(Logger::SEVERE, "Failed to extract file: " + fileName, e);
            return false;
        }
    }
};

// Initialize the static logger
Logger* ZipFileProcessor::logger = Logger::getLogger("ZipFileProcessor");