#include <filesystem>
#include <string>
#include <memory>
#include <fstream>
#include <cstring>
#include <zip.h>
#include <iostream>

namespace fs = std::filesystem;

enum class LogLevel { SEVERE, WARNING, INFO };

static const char* level_str(LogLevel level) {
    switch (level) {
        case LogLevel::SEVERE: return "SEVERE";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::INFO: return "INFO";
    }
    return "UNKNOWN";
}

struct Logger {
    void log(LogLevel level, const std::string& msg) {
        std::cerr << level_str(level) << ": " << msg << std::endl;
    }
    void log(LogLevel level, const std::string& msg, const std::string& err) {
        std::cerr << level_str(level) << ": " << msg << " - " << err << std::endl;
    }
    void severe(const std::string& msg) { log(LogLevel::SEVERE, msg); }
    void warning(const std::string& msg) { log(LogLevel::WARNING, msg); }
    void info(const std::string& msg) { log(LogLevel::INFO, msg); }
};

static Logger logger;

class ZipFileProcessor {
    fs::path zipFilePath;

    struct ZipFileHandle {
        zip_t* archive;
        explicit ZipFileHandle(zip_t* a) : archive(a) {}
        ~ZipFileHandle() { if (archive) zip_close(archive); }
        ZipFileHandle(const ZipFileHandle&) = delete;
        ZipFileHandle& operator=(const ZipFileHandle&) = delete;
        operator bool() const { return archive != nullptr; }
        zip_t* get() const { return archive; }
    };

    std::unique_ptr<ZipFileHandle> readZipFile() {
        if (!fs::exists(zipFilePath)) {
            logger.severe("Zip file does not exist: " + fs::absolute(zipFilePath).string());
            return nullptr;
        }
        int err;
        zip_t* archive = zip_open(zipFilePath.string().c_str(), ZIP_RDONLY, &err);
        if (!archive) {
            logger.log(LogLevel::SEVERE, "Failed to read the zip file: " + fs::absolute(zipFilePath).string(), std::to_string(err));
            return nullptr;
        }
        return std::make_unique<ZipFileHandle>(archive);
    }

public:
    explicit ZipFileProcessor(const std::string& zipFileName)
        : zipFilePath(zipFileName) {}

    bool extractAll(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        auto zipFile = readZipFile();
        if (!zipFile) return false;

        if (!fs::exists(outputDirPath)) {
            std::error_code ec;
            fs::create_directories(outputDirPath, ec);
            if (ec) {
                logger.log(LogLevel::SEVERE, "Failed to create output directory: " + fs::absolute(outputDirPath).string(), ec.message());
                return false;
            }
            logger.info("Created output directory: " + fs::absolute(outputDirPath).string());
        }

        zip_int64_t numEntries = zip_get_num_entries(zipFile->get(), 0);
        for (zip_int64_t i = 0; i < numEntries; i++) {
            const char* entryName = zip_get_name(zipFile->get(), i, 0);
            if (!entryName) continue;

            fs::path filePath = outputDirPath / entryName;

            if (entryName[std::strlen(entryName) - 1] == '/') {
                if (!fs::exists(filePath)) {
                    std::error_code ec;
                    fs::create_directories(filePath, ec);
                    if (!ec) {
                        logger.info("Created directory: " + fs::absolute(filePath).string());
                    }
                }
            } else {
                zip_file_t* zf = zip_fopen_index(zipFile->get(), i, 0);
                if (!zf) {
                    logger.log(LogLevel::SEVERE, "Failed to process entry: " + std::string(entryName), "zip_fopen_index failed");
                    continue;
                }
                struct Closer { zip_file_t* f; ~Closer() { if (f) zip_fclose(f); } } closer{zf};

                std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
                if (!out) {
                    logger.log(LogLevel::SEVERE, "Failed to process entry: " + std::string(entryName), "cannot open output file");
                    continue;
                }

                char buffer[1024];
                zip_int64_t len;
                while ((len = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
                    out.write(buffer, static_cast<std::streamsize>(len));
                }
                logger.info("Extracted file: " + fs::absolute(filePath).string());
            }
        }

        return true;
    }

    bool extractFile(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        fs::path filePath = outputDirPath / fileName;
        auto zipFile = readZipFile();
        if (!zipFile) return false;

        zip_int64_t idx = zip_name_locate(zipFile->get(), fileName.c_str(), 0);
        if (idx < 0) {
            logger.warning("File not found in zip: " + fileName);
            return false;
        }

        if (filePath.has_parent_path() && !fs::exists(filePath.parent_path())) {
            std::error_code ec;
            fs::create_directories(filePath.parent_path(), ec);
            if (ec) {
                logger.log(LogLevel::SEVERE, "Failed to create parent directory: " + fs::absolute(filePath.parent_path()).string(), ec.message());
                return false;
            }
            logger.info("Created parent directory: " + fs::absolute(filePath.parent_path()).string());
        }

        zip_file_t* zf = zip_fopen_index(zipFile->get(), idx, 0);
        if (!zf) {
            logger.log(LogLevel::SEVERE, "Failed to extract file: " + fileName, "zip_fopen_index failed");
            return false;
        }
        struct Closer { zip_file_t* f; ~Closer() { if (f) zip_fclose(f); } } closer{zf};

        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
        if (!out) {
            logger.log(LogLevel::SEVERE, "Failed to extract file: " + fileName, "cannot open output file");
            return false;
        }

        char buffer[1024];
        zip_int64_t len;
        while ((len = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
            out.write(buffer, static_cast<std::streamsize>(len));
        }
        logger.info("Extracted file: " + fs::absolute(filePath).string());

        return true;
    }
};