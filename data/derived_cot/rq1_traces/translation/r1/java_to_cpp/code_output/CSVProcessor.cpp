#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>

class CSVProcessor {
public:
    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream in(fileName);
        if (!in.is_open()) {
            throw std::runtime_error("Failed to open file: " + fileName);
        }

        std::string line;
        if (std::getline(in, line)) {
            title = split(line);
        }

        while (std::getline(in, line)) {
            data.push_back(split(line));
        }

        if (in.bad() || (in.fail() && !in.eof())) {
            throw std::runtime_error("I/O error while reading file: " + fileName);
        }
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
            std::ofstream out(fileName);
            out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            out << join(title) << '\n';
            for (const auto& row : data) {
                out << join(row) << '\n';
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        try {
            std::ofstream out(fileName);
            out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
            for (const auto& row : data) {
                out << join(row) << '\n';
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int processCSVData(int N, const std::string& saveFileName) {
        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;
        readCSV(saveFileName, title, data);

        std::vector<std::string> columnData;
        for (const auto& row : data) {
            if (static_cast<size_t>(N) < row.size()) {
                std::string upperStr = row[N];
                std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
                               [](unsigned char c) { return std::toupper(c); });
                columnData.push_back(upperStr);
            }
        }

        std::vector<std::vector<std::string>> newData;
        newData.push_back(columnData);

        size_t lastDot = saveFileName.find_last_of('.');
        std::string baseName = (lastDot == std::string::npos) ? saveFileName : saveFileName.substr(0, lastDot);
        std::string newFileName = baseName + "_process.csv";

        return writeCSV(title, newData, newFileName);
    }

private:
    std::vector<std::string> split(const std::string& s) {
        std::vector<std::string> tokens;
        std::istringstream iss(s);
        std::string token;
        while (std::getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        return tokens;
    }

    std::string join(const std::vector<std::string>& v) {
        if (v.empty()) {
            return "";
        }
        std::ostringstream oss;
        oss << v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            oss << ',' << v[i];
        }
        return oss.str();
    }
};