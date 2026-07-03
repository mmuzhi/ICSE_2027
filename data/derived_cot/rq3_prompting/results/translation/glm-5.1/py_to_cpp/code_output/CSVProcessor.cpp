#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <stdexcept>

class CSVProcessor {
public:
    CSVProcessor() {}

    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>> read_csv(const std::string& file_name) {
        std::vector<std::vector<std::string>> all_rows;
        std::ifstream file(file_name);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + file_name);
        }

        while (file.peek() != EOF) {
            all_rows.push_back(parse_csv_row(file));
        }

        if (all_rows.empty()) {
            return {{}, {}};
        }

        std::vector<std::string> title = all_rows[0];
        std::vector<std::vector<std::string>> data(all_rows.begin() + 1, all_rows.end());
        return {title, data};
    }

    int write_csv(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        try {
            std::ofstream file(file_name);
            if (!file.is_open()) {
                return 0;
            }
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    if (i > 0) file << ',';
                    file << format_csv_field(row[i]);
                }
                file << "\r\n";
            }
            return 1;
        } catch (...) {
            return 0;
        }
    }

    int process_csv_data(int N, const std::string& save_file_name) {
        auto [title, data] = read_csv(save_file_name);
        std::vector<std::string> column_data;
        for (const auto& row : data) {
            std::string val = row[N];
            std::transform(val.begin(), val.end(), val.begin(),
                           [](unsigned char c) { return std::toupper(c); });
            column_data.push_back(val);
        }
        std::vector<std::vector<std::string>> new_data = {title, column_data};
        std::string base = save_file_name.substr(0, save_file_name.find('.'));
        return write_csv(new_data, base + "_process.csv");
    }

private:
    static std::string format_csv_field(const std::string& field) {
        bool needs_quoting = field.find(',') != std::string::npos ||
                             field.find('"') != std::string::npos ||
                             field.find('\n') != std::string::npos ||
                             field.find('\r') != std::string::npos;
        if (!needs_quoting) return field;
        std::string result = "\"";
        for (char c : field) {
            if (c == '"') result += "\"\"";
            else result += c;
        }
        result += '"';
        return result;
    }

    static std::vector<std::string> parse_csv_row(std::ifstream& file) {
        std::vector<std::string> fields;
        std::string field;
        bool in_quotes = false;
        char c;

        while (file.get(c)) {
            if (in_quotes) {
                if (c == '"') {
                    if (file.peek() == '"') {
                        file.get();
                        field += '"';
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
                } else if (c == '\r') {
                    if (file.peek() == '\n') file.get();
                    break;
                } else if (c == '\n') {
                    break;
                } else {
                    field += c;
                }
            }
        }
        fields.push_back(field);
        return fields;
    }
};