#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>

class CSVProcessor {
public:
    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open file: " + fileName);
        }

        std::string line;
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                title.push_back(cell);
            }

            while (std::getline(file, line)) {
                std::stringstream ss(line);
                std::vector<std::string> row;
                while (std::getline(ss, cell, ',')) {
                    row.push_back(cell);
                }
                data.push_back(row);
            }
        }
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            return 0;
        }

        for (size_t i = 0; i < title.size(); ++i) {
            file << title[i];
            if (i < title.size() - 1) {
                file << ",";
            }
        }
        file << "\n";

        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        return 1;
    }

    int writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            return 0;
        }

        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        return 1;
    }

    int processCSVData(int N, const std::string& saveFileName) {
        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;

        try {
            readCSV(saveFileName, title, data);
        } catch (const std::ios_base::failure& e) {
            throw;
        }

        std::vector<std::string> columnData;
        for (const auto& row : data) {
            if (row.size() > static_cast<size_t>(N)) {
                std::string cell = row[N];
                std::transform(cell.begin(), cell.end(), cell.begin(),
                    [](unsigned char c) { return std::toupper(c); });
                columnData.push_back(cell);
            }
        }

        std::vector<std::vector<std::string>> newData;
        newData.push_back(columnData);

        try {
            size_t last_dot = saveFileName.find_last_of(".");
            std::string base = (last_dot != std::string::npos) ? saveFileName.substr(0, last_dot) : saveFileName;
            std::string newFileName = base + "_process.csv";

            return writeCSV(title, newData, newFileName);
        } catch (...) {
            return 0;
        }
    }
};