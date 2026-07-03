#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cctype>

class CSVProcessor {
public:
    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> read_csv(const std::string& file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + file_name);
        }

        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;

        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string cell;
            while (std::getline(ss, cell, ',')) {
                row.push_back(cell);
            }
            if (title.empty()) {
                title = row;
            } else {
                data.push_back(row);
            }
        }

        return std::make_pair(title, data);
    }

    int write_csv(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        try {
            std::ofstream file(file_name);
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); i++) {
                    file << row[i];
                    if (i < row.size() - 1) {
                        file << ',';
                    }
                }
                file << '\n';
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int process_csv_data(int N, const std::string& save_file_name) {
        try {
            auto result = read_csv(save_file_name);
            std::vector<std::string> title = std::move(result.first);
            std::vector<std::vector<std::string>> data = std::move(result.second);

            std::vector<std::string> column_data;
            for (const auto& row : data) {
                if (N < static_cast<int>(row.size())) {
                    column_data.push_back(row[N]);
                } else {
                    column_data.push_back("");
                }
            }

            for (auto& s : column_data) {
                for (char& c : s) {
                    c = std::toupper(c);
                }
            }

            std::vector<std::vector<std::string>> new_data;
            new_data.push_back(title);
            new_data.push_back(column_data);

            size_t last_dot = save_file_name.find_last_of('.');
            std::string base_name = last_dot == std::string::npos ? save_file_name : save_file_name.substr(0, last_dot);
            std::string new_file_name = base_name + "_process.csv";

            return write_csv(new_data, new_file_name);
        } catch (...) {
            return 0;
        }
    }
};