#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <utility>
#include <algorithm>
#include <sstream>

std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_quote = false;

    for (char c : line) {
        if (c == '"') {
            in_quote = !in_quote;
        } else if (c == ',' && !in_quote) {
            tokens.push_back(current_token);
            current_token = "";
        } else {
            current_token += c;
        }
    }

    tokens.push_back(current_token);
    return tokens;
}

class CSVProcessor {
public:
    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> read_csv(const std::string& file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            return std::make_pair(std::vector<std::string>(), std::vector<std::vector<std::string>>());
        }

        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;

        std::string line;
        if (!std::getline(file, line)) {
            return std::make_pair(title, data);
        }

        title = split_csv_line(line);

        while (std::getline(file, line)) {
            std::vector<std::string> row = split_csv_line(line);
            data.push_back(row);
        }

        return std::make_pair(title, data);
    }

    int write_csv(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        std::ofstream file(file_name);
        if (!file.is_open()) {
            return 0;
        }

        for (const auto& row : data) {
            for (size_t i = 0; i < row.size(); ++i) {
                file << row[i];
                if (i < row.size() - 1) {
                    file << ',';
                }
            }
            file << '\n';
        }

        return 1;
    }

    int process_csv_data(int N, const std::string& save_file_name) {
        auto result = read_csv(save_file_name);
        if (result.first.empty() && result.second.empty()) {
            return 0;
        }

        const auto& title = result.first;
        const auto& data = result.second;

        std::vector<std::string> column_data;
        for (const auto& row : data) {
            if (static_cast<size_t>(N) >= row.size()) {
                return 0;
            }
            std::string s = row[N];
            std::string upper_s;
            for (char c : s) {
                upper_s += std::toupper(c);
            }
            column_data.push_back(upper_s);
        }

        std::vector<std::vector<std::string>> new_data;
        new_data.push_back(title);
        new_data.push_back(column_data);

        std::string base_name;
        size_t dot_pos = save_file_name.find('.');
        if (dot_pos == std::string::npos) {
            base_name = save_file_name;
        } else {
            base_name = save_file_name.substr(0, dot_pos);
        }

        std::string new_file_name = base_name + "_process.csv";

        return write_csv(new_data, new_file_name);
    }
};