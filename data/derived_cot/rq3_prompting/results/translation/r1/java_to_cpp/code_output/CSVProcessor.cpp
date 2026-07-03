#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::ios_base::failure("Cannot open file: " + fileName);
        }

        std::string line;
        if (std::getline(file, line)) {
            // Split first line into title
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {
                title.push_back(token);
            }

            // Read remaining lines into data
            while (std::getline(file, line)) {
                std::vector<std::string> row;
                std::stringstream ss2(line);
                while (std::getline(ss2, token, ',')) {
                    row.push_back(token);
                }
                data.push_back(row);
            }
        }
        // If file is empty (no lines), title and data remain empty
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
            std::ofstream file;
            file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            file.open(fileName);

            // Write title line
            for (size_t i = 0; i < title.size(); ++i) {
                if (i > 0) file << ",";
                file << title[i];
            }
            file << "\n";

            // Write data rows
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    if (i > 0) file << ",";
                    file << row[i];
                }
                file << "\n";
            }
            return 1;
        } catch (const std::ios_base::failure&) {
            return 0;
        }
    }

    int writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
            std::ofstream file;
            file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            file.open(fileName);

            // Write data rows only
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    if (i > 0) file << ",";
                    file << row[i];
                }
                file << "\n";
            }
            return 1;
        } catch (const std::ios_base::failure&) {
            return 0;
        }
    }

    int processCSVData(int N, const std::string& saveFileName) {
        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;
        readCSV(saveFileName, title, data);  // may throw

        std::vector<std::string> columnData;
        for (const auto& row : data) {
            if (N < static_cast<int>(row.size())) {
                std::string upper;
                for (char c : row[N]) {
                    upper += std::toupper(static_cast<unsigned char>(c));
                }
                columnData.push_back(upper);
            }
        }

        std::vector<std::vector<std::string>> newData;
        newData.push_back(columnData);

        // Build output file name: first part before first '.'
        size_t dotPos = saveFileName.find_first_of('.');
        std::string base = (dotPos == std::string::npos) ? saveFileName : saveFileName.substr(0, dotPos);
        std::string outFileName = base + "_process.csv";

        return writeCSV(title, newData, outFileName);
    }
};