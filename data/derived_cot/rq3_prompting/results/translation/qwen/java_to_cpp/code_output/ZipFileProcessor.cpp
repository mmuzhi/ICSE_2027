#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>

namespace fs = std::filesystem;
namespace zip = std::zip; // Assuming C++27 zip library is available

class ZipFileProcessor {
private:
    fs::path zipFilePath;
    static spdlog::logger& logger() {
        static spdlog::logger log("zip-processor", spdlog::sinks::stdout_color_sink_mt());
        log.set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        return log;
    }

    std::unique_ptr<zip::ZipFile> readZipFile() {
        if (!fs::exists(zipFilePath)) {
            logger().error("Zip file does not exist: {}", zipFilePath.string());
            return nullptr;
        }
        try {
            return std::make_unique<zip::ZipFile>(zipFilePath.string());
        } catch (const std::exception& e) {
            logger().error("Failed to read the zip file: {}", zipFilePath.string());
            return nullptr;
        }
    }

public:
    explicit ZipFileProcessor(const std::string& zipFileName) : zipFilePath(zipFileName) {}

    bool extractAll(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        auto zipFile = readZipFile();
        if (!zipFile) return false;

        if (!fs::exists(outputDirPath)) {
            try {
                fs::create_directories(outputDirPath);
                logger().info("Created output directory: {}", outputDirPath.string());
            } catch (const std::exception& e) {
                logger().error("Failed to create output directory: {}", outputDirPath.string());
                return false;
            }
        }

        for (const auto& entry : *zipFile) {
            fs::path filePath = outputDirPath / entry.name();
            try {
                if (entry.isDirectory()) {
                    if (!fs::exists(filePath)) {
                        fs::create_directories(filePath);
                        logger().info("Created directory: {}", filePath.string());
                    }
                } else {
                    if (!fs::exists(filePath.parent_path())) {
                        fs::create_directories(filePath.parent_path());
                        logger().info("Created parent directory: {}", filePath.parent_path().string());
                    }
                    std::ifstream in(zipFile->open_entry(entry.name()), std::ios::binary);
                    std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
                    std::vector<char> buffer(1024);
                    while (in.read(buffer.data(), buffer.size())) {
                        out.write(buffer.data(), in.gcount());
                    }
                    logger().info("Extracted file: {}", filePath.string());
                }
            } catch (const std::exception& e) {
                logger().error("Failed to process entry: {}", entry.name());
            }
        }
        return true;
    }

    bool extractFile(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        fs::path filePath = outputDirPath / fileName;
        auto zipFile = readZipFile();
        if (!zipFile) return false;

        auto entry = zipFile->get_entry(fileName);
        if (!entry) {
            logger().warn("File not found in zip: {}", fileName);
            return false;
        }

        if (!fs::exists(filePath.parent_path())) {
            try {
                fs::create_directories(filePath.parent_path());
                logger().info("Created parent directory: {}", filePath.parent_path().string());
            } catch (const std::exception& e) {
                logger().error("Failed to create parent directory: {}", filePath.parent_path().string());
                return false;
            }
        }

        std::ifstream in(zipFile->open_entry(fileName), std::ios::binary);
        std::ofstream out(filePath, std::ios::binary | std::ios::trunc);
        std::vector<char> buffer(1024);
        while (in.read(buffer.data(), buffer.size())) {
            out.write(buffer.data(), in.gcount());
        }
        logger().info("Extracted file: {}", filePath.string());
        return true;
    }
};