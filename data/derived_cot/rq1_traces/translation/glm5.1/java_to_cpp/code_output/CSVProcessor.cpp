#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::ios_base::failure("Could not open file: " + fileName);
        }

        std::string line;
        if (std::getline(file, line)) {
            std::vector<std::string> parts = split(line, ',');
            title.insert(title.end(), parts.begin(), parts.end());

            std::string lineData;
            while (std::getline(file, lineData)) {
                data.push_back(split(lineData, ','));
            }
        }
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
            std::ofstream file(fileName);
            if (!file.is_open()) {
                return 0;
            }

            file << join(title, ",") << "\n";

            for (const auto& row : data) {
                file << join(row, ",") << "\n";
            }

            if (file.fail()) {
                return 0;
            }
            return 1;
        } catch (const std::exception&) {
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
                file << join(row, ",") << "\n";
            }

            if (file.fail()) {
                return 0;
            }
            return 1;
        } catch (const std::exception&) {
            return 0;
        }
    }

    int processCSVData(int N, const std::string& saveFileName) {
        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;
        readCSV(saveFileName, title, data);

        std::vector<std::string> columnData;
        for (const auto& row : data) {
            if (N < static_cast<int>(row.size())) {
                columnData.push_back(toUpperCase(row[N]));
            }
        }

        std::vector<std::vector<std::string>> newData;
        newData.push_back(columnData);

        std::string baseName = split(saveFileName, '.')[0];
        return writeCSV(title, newData, baseName + "_process.csv");
    }

private:
    // Mimics Java's String.split() with a single-char delimiter:
    // trailing empty strings are removed; if no delimiter is found,
    // the original string is returned as the sole element.
    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        // Remove trailing empty strings (Java split behavior)
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        // If no delimiter was found, return original string as single element
        if (tokens.empty() && s.find(delimiter) == std::string::npos) {
            tokens.push_back(s);
        }
        return tokens;
    }

    static std::string join(const std::vector<std::string>& v, const std::string& delimiter) {
        if (v.empty()) return "";
        std::string result = v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            result += delimiter + v[i];
        }
        return result;
    }

    static std::string toUpperCase(const std::string& s) {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        return result;
    }
};