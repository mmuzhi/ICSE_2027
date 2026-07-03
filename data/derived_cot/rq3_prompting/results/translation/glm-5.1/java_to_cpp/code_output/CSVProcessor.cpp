#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    static std::vector<std::string> split(const std::string& str, const std::string& delim) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end;
        while ((end = str.find(delim, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delim.length();
        }
        tokens.push_back(str.substr(start));
        // Java's split discards trailing empty strings
        while (!tokens.empty() && tokens.back().empty()) {
            tokens.pop_back();
        }
        return tokens;
    }

    static std::string join(const std::vector<std::string>& parts, const std::string& delim) {
        std::string result;
        for (size_t i = 0; i < parts.size(); i++) {
            if (i > 0) result += delim;
            result += parts[i];
        }
        return result;
    }

    static std::string toUpperCase(const std::string& s) {
        std::string result = s;
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        return result;
    }

    void readCSV(const std::string& fileName, std::vector<std::string>& title, std::vector<std::vector<std::string>>& data) {
        std::ifstream reader(fileName);
        if (!reader.is_open()) {
            throw std::ios_base::failure("Could not open file: " + fileName);
        }

        std::string line;
        if (std::getline(reader, line)) {
            auto tokens = split(line, ",");
            title.insert(title.end(), tokens.begin(), tokens.end());

            std::string lineData;
            while (std::getline(reader, lineData)) {
                data.push_back(split(lineData, ","));
            }
        }
    }

    int writeCSV(const std::vector<std::string>& title, const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        std::ofstream writer(fileName);
        if (!writer.is_open()) return 0;

        writer << join(title, ",") << "\n";

        for (const auto& row : data) {
            writer << join(row, ",") << "\n";
        }

        writer.close();
        if (writer.fail()) return 0;
        return 1;
    }

    int writeCSV(const std::vector<std::vector<std::string>>& data, const std::string& fileName) {
        std::ofstream writer(fileName);
        if (!writer.is_open()) return 0;

        for (const auto& row : data) {
            writer << join(row, ",") << "\n";
        }

        writer.close();
        if (writer.fail()) return 0;
        return 1;
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

        // Java: saveFileName.split("\\.")[0] — regex split on literal dot, take first part
        std::vector<std::string> parts = split(saveFileName, ".");
        std::string baseName = parts.empty() ? "" : parts[0];

        return writeCSV(title, newData, baseName + "_process.csv");
    }
};