#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

// Assume minizip (unzip.h) is available (part of zlib contrib)
#include <unzip.h>

namespace fs = std::filesystem;

// Simple logger mimicking Java's java.util.logging.Logger
class Logger {
public:
    static void severe(const std::string& msg) {
        std::cerr << "[SEVERE] " << msg << std::endl;
    }

    static void severe(const std::string& msg, const std::exception& e) {
        std::cerr << "[SEVERE] " << msg << " Exception: " << e.what() << std::endl;
    }

    static void warning(const std::string& msg) {
        std::cerr << "[WARNING] " << msg << std::endl;
    }

    static void info(const std::string& msg) {
        std::clog << "[INFO] " << msg << std::endl;
    }
};

// RAII guard for unzFile pointer
class ZipGuard {
    unzFile f_;
public:
    explicit ZipGuard(unzFile f) : f_(f) {}
    ~ZipGuard() { if (f_) unzClose(f_); }
    ZipGuard(const ZipGuard&) = delete;
    ZipGuard& operator=(const ZipGuard&) = delete;
    unzFile get() const { return f_; }
};

class ZipFileProcessor {
private:
    fs::path zipFilePath_;

    unzFile readZipFile() {
        if (!fs::exists(zipFilePath_)) {
            Logger::severe("Zip file does not exist: " + fs::absolute(zipFilePath_).string());
            return nullptr;
        }
        unzFile zip = unzOpen(zipFilePath_.string().c_str());
        if (!zip) {
            Logger::severe("Failed to read the zip file: " + fs::absolute(zipFilePath_).string());
            return nullptr;
        }
        return zip;
    }

    // Helper to copy bytes from unzFile to output stream
    static bool extractEntryToFile(unzFile zip, const fs::path& outPath) {
        if (unzOpenCurrentFile(zip) != UNZ_OK) {
            Logger::severe("Failed to open current entry in zip");
            return false;
        }

        std::ofstream outFile(outPath, std::ios::binary | std::ios::trunc);
        if (!outFile) {
            unzCloseCurrentFile(zip);
            Logger::severe("Failed to open output file: " + outPath.string());
            return false;
        }

        char buffer[1024];
        int bytesRead;
        bool success = true;
        while ((bytesRead = unzReadCurrentFile(zip, buffer, sizeof(buffer))) > 0) {
            outFile.write(buffer, bytesRead);
            if (!outFile) {
                Logger::severe("Write error for file: " + outPath.string());
                success = false;
                break;
            }
        }
        if (bytesRead < 0) {
            Logger::severe("Read error from zip for entry");
            success = false;
        }

        outFile.close();
        unzCloseCurrentFile(zip);
        return success;
    }

public:
    explicit ZipFileProcessor(const std::string& zipFileName)
        : zipFilePath_(zipFileName) {}

    bool extractAll(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        unzFile rawZip = readZipFile();
        if (!rawZip) return false;
        ZipGuard guard(rawZip);
        unzFile zip = guard.get();

        // Create output directory if not exists
        if (!fs::exists(outputDirPath)) {
            try {
                fs::create_directories(outputDirPath);
                Logger::info("Created output directory: " + fs::absolute(outputDirPath).string());
            } catch (const std::exception& e) {
                Logger::severe("Failed to create output directory: " + fs::absolute(outputDirPath).string(), e);
                return false;
            }
        }

        // Iterate over all entries in the zip file
        if (unzGoToFirstFile(zip) != UNZ_OK) {
            Logger::warning("Zip file is empty or corrupted");
            return true; // no entries, but empty zip is valid
        }

        bool anyFailure = false;
        do {
            char entryName[256];
            unz_file_info fileInfo;
            if (unzGetCurrentFileInfo(zip, &fileInfo, entryName, sizeof(entryName),
                                     nullptr, 0, nullptr, 0) != UNZ_OK) {
                Logger::severe("Failed to get entry info");
                anyFailure = true;
                continue;
            }

            // Determine if directory (zip entry names end with '/')
            bool isDirectory = (strlen(entryName) > 0 && entryName[strlen(entryName)-1] == '/');

            fs::path fullPath = outputDirPath / entryName;
            try {
                if (isDirectory) {
                    if (!fs::exists(fullPath)) {
                        fs::create_directories(fullPath);
                        Logger::info("Created directory: " + fs::absolute(fullPath).string());
                    }
                } else {
                    // Ensure parent directory exists
                    fs::path parent = fullPath.parent_path();
                    if (!fs::exists(parent)) {
                        fs::create_directories(parent);
                        Logger::info("Created parent directory: " + fs::absolute(parent).string());
                    }
                    if (!extractEntryToFile(zip, fullPath)) {
                        anyFailure = true;
                    } else {
                        Logger::info("Extracted file: " + fs::absolute(fullPath).string());
                    }
                }
            } catch (const std::exception& e) {
                Logger::severe("Failed to process entry: " + std::string(entryName), e);
                anyFailure = true;
            }
        } while (unzGoToNextFile(zip) == UNZ_OK);

        return !anyFailure;
    }

    bool extractFile(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        fs::path filePath = outputDirPath / fileName;

        unzFile rawZip = readZipFile();
        if (!rawZip) return false;
        ZipGuard guard(rawZip);
        unzFile zip = guard.get();

        // Locate the entry by name
        if (unzLocateFile(zip, fileName.c_str(), 0) != UNZ_OK) {
            Logger::warning("File not found in zip: " + fileName);
            return false;
        }

        // Create parent directory if needed
        fs::path parent = filePath.parent_path();
        if (!fs::exists(parent)) {
            try {
                fs::create_directories(parent);
                Logger::info("Created parent directory: " + fs::absolute(parent).string());
            } catch (const std::exception& e) {
                Logger::severe("Failed to create parent directory: " + fs::absolute(parent).string(), e);
                return false;
            }
        }

        try {
            if (!extractEntryToFile(zip, filePath)) {
                return false;
            }
            Logger::info("Extracted file: " + fs::absolute(filePath).string());
            return true;
        } catch (const std::exception& e) {
            Logger::severe("Failed to extract file: " + fileName, e);
            return false;
        }
    }
};