#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::ios_base::failure("Failed to open file");
        }

        std::string line;
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            while (std::getline(ss, item, ',')) {
                title.push_back(item);
            }
        }

        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string item;
            while (std::getline(ss, item, ',')) {
                row.push_back(item);
            }
            data.push_back(row);
        }
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
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
            file << '\n';

            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    file << row[i];
                    if (i < row.size() - 1) {
                        file << ",";
                    }
                }
                file << '\n';
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
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
                file << '\n';
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int processCSVData(int N, const std::string& saveFileName) {
        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;

        try {
            readCSV(saveFileName, title, data);
        } catch (const std::ios_base::failure&) {
            return 0;
        }

        if (title.empty() || data.empty()) {
            return 0;
        }

        std::vector<std::string> columnData;
        for (const auto& row : data) {
            if (static_cast<size_t>(N) < row.size()) {
                std::string s = row[N];
                for (char& c : s) {
                    c = std::toupper(c);
                }
                columnData.push_back(s);
            }
        }

        if (columnData.empty()) {
            return 0;
        }

        std::vector<std::vector<std::string>> newData = { columnData };

        size_t dotPos = saveFileName.find_last_of('.');
        std::string processedFileName = (dotPos != std::string::npos)
            ? saveFileName.substr(0, dotPos) + "_process.csv"
            : saveFileName + "_process.csv";

        return writeCSV(title, newData, processedFileName);
    }
};