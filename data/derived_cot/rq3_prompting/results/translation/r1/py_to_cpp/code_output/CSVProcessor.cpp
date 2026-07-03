#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    CSVProcessor() = default;

    // Read CSV file, returns title (first row) and data (remaining rows)
    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>
    read_csv(const std::string& file_name) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_name);
        }

        std::vector<std::string> title;
        std::vector<std::vector<std::string>> data;

        std::string line;
        // Read title line
        if (std::getline(file, line)) {
            title = split_csv_line(line);
        } else {
            return {title, data}; // Empty file: no title, no data
        }

        // Read remaining lines
        while (std::getline(file, line)) {
            if (!line.empty()) { // skip empty lines (Python csv.reader skips them)
                data.push_back(split_csv_line(line));
            }
        }

        return {title, data};
    }

    // Write CSV data (list of rows) to file
    int write_csv(const std::vector<std::vector<std::string>>& data,
                  const std::string& file_name) {
        try {
            std::ofstream file(file_name);
            if (!file.is_open()) {
                return 0;
            }

            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    if (i > 0) file << ',';
                    file << quote_field(row[i]);
                }
                file << '\n';
            }

            if (file.good()) {
                return 1;
            }
            return 0;
        } catch (...) {
            return 0;
        }
    }

    // Process CSV: extract N-th column (0-indexed), uppercase, save to new file
    int process_csv_data(int N, const std::string& save_file_name) {
        auto [title, data] = read_csv(save_file_name);

        // Extract N-th column
        std::vector<std::string> column_data;
        for (const auto& row : data) {
            column_data.push_back(row.at(N)); // throws if N out of range
        }

        // Uppercase each element
        for (auto& s : column_data) {
            std::transform(s.begin(), s.end(), s.begin(),
                           [](unsigned char c) { return std::toupper(c); });
        }

        // Build new data: title row + column data row
        std::vector<std::vector<std::string>> new_data = {title, column_data};

        // Create new file name: remove extension, append '_process.csv'
        std::string base = save_file_name;
        size_t dot = save_file_name.rfind('.');
        if (dot != std::string::npos) {
            base = save_file_name.substr(0, dot);
        }
        std::string new_file = base + "_process.csv";

        return write_csv(new_data, new_file);
    }

private:
    // Simple CSV line parser (handles quoted fields with commas)
    static std::vector<std::string> split_csv_line(const std::string& line) {
        std::vector<std::string> fields;
        std::string field;
        bool in_quotes = false;
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (in_quotes) {
                if (c == '"') {
                    // Check for escaped quote ""
                    if (i + 1 < line.size() && line[i + 1] == '"') {
                        field += '"';
                        ++i; // skip next quote
                    } else {
                        in_quotes = false;
                    }
                } else {
                    field += c;
                }
            } else {
                if (c == '"') {
                    in_quotes = true;
                } else if (c == ',') {
                    fields.push_back(field);
                    field.clear();
                } else {
                    field += c;
                }
            }
        }
        fields.push_back(field); // last field
        return fields;
    }

    // Quote a field if it contains comma, double quote, or newline
    static std::string quote_field(const std::string& field) {
        if (field.find(',') != std::string::npos ||
            field.find('"') != std::string::npos ||
            field.find('\n') != std::string::npos) {
            std::string quoted = "\"";
            for (char c : field) {
                if (c == '"') {
                    quoted += "\"\""; // escape double quote
                } else {
                    quoted += c;
                }
            }
            quoted += '"';
            return quoted;
        }
        return field;
    }
};