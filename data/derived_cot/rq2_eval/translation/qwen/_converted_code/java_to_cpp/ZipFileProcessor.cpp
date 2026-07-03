#include <iostream>
#include <filesystem>
#include <minizip/zip.h>
#include <minizip/unzip.h>

namespace fs = std::filesystem;

class ZipFileProcessor {
public:
    explicit ZipFileProcessor(const std::string& zipFileName) : zipFileName(zipFileName) {}

    bool extract_all(const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        minizip::Zip zip(zipFileName.c_str(), nullptr, 0, 0, 0, nullptr, nullptr, 0);
        if (!zip.Open(minizip::Zip::kRead)) {
            std::cerr << "Zip file does not exist or cannot be opened: " << zipFileName << std::endl;
            return false;
        }

        if (!fs::exists(outputDirPath)) {
            try {
                fs::create_directories(outputDirPath);
                std::cout << "Created output directory: " << outputDirPath << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Failed to create output directory: " << outputDirPath << ". Error: " << e.what() << std::endl;
                return false;
            }
        }

        int numEntries = zip.GetNumberOfFile();
        for (int i = 0; i < numEntries; ++i) {
            minizip::ZipLocalHeader header;
            if (!zip.GetLocalHeader(i, header)) continue;

            fs::path filePath = outputDirPath / header.m_filename;
            if (header.m_isDir) {
                if (!fs::exists(filePath)) {
                    try {
                        fs::create_directories(filePath);
                        std::cout << "Created directory: " << filePath << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to create directory: " << filePath << ". Error: " << e.what() << std::endl;
                        return false;
                    }
                }
            } else {
                if (!fs::exists(filePath.parent_path())) {
                    try {
                        fs::create_directories(filePath.parent_path());
                        std::cout << "Created parent directory: " << filePath.parent_path() << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to create parent directory: " << filePath.parent_path() << ". Error: " << e.what() << std::endl;
                        return false;
                    }
                }

                try (std::ifstream in(zip.OpenForReading(i));
                     std::ofstream out(filePath, std::ios::binary | std::ios::trunc)) {
                    if (!in) {
                        std::cerr << "Failed to open zip entry: " << header.m_filename << std::endl;
                        return false;
                    }
                    const int bufferSize = 1024;
                    char buffer[bufferSize];
                    while (in.read(buffer, bufferSize)) {
                        out.write(buffer, in.gcount());
                    }
                    std::cout << "Extracted file: " << filePath << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Failed to process entry: " << header.m_filename << ". Error: " << e.what() << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

    bool extract_file(const std::string& fileName, const std::string& outputDir) {
        fs::path outputDirPath(outputDir);
        minizip::Zip zip(zipFileName.c_str(), nullptr, 0, 0, 0, nullptr, nullptr, 0);
        if (!zip.Open(minizip::Zip::kRead)) {
            std::cerr << "Zip file does not exist or cannot be opened: " << zipFileName << std::endl;
            return false;
        }

        minizip::ZipLocalHeader header;
        if (!zip.GetLocalHeader(fileName.c_str(), header)) {
            std::cerr << "File not found in zip: " << fileName << std::endl;
            return false;
        }

        fs::path filePath = outputDirPath / fileName;
        if (!fs::exists(filePath.parent_path())) {
            try {
                fs::create_directories(filePath.parent_path());
                std::cout << "Created parent directory: " << filePath.parent_path() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Failed to create parent directory: " << filePath.parent_path() << ". Error: " << e.what() << std::endl;
                return false;
            }
        }

        try (std::ifstream in(zip.OpenForReading(fileName.c_str()));
             std::ofstream out(filePath, std::ios::binary | std::ios::trunc)) {
            if (!in) {
                std::cerr << "Failed to open zip entry: " << fileName << std::endl;
                return false;
            }
            const int bufferSize = 1024;
            char buffer[bufferSize];
            while (in.read(buffer, bufferSize)) {
                out.write(buffer, in.gcount());
            }
            std::cout << "Extracted file: " << filePath << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "Failed to extract file: " << fileName << ". Error: " << e.what() << std::endl;
            return false;
        }
    }

private:
    std::string zipFileName;
};