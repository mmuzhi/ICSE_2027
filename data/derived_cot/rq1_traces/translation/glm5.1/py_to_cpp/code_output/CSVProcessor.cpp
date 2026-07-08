#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>

class CSVProcessor {
public:
    CSVProcessor() {}

    std::pair<std::vector<std::string>, std::vector<std::vector<std::string>>>
    read_csv(const std::string& file_name) {
        std::vector<std::vector<std::string>> data;
        std::ifstream file(file_name);

        std::vector<std::string> title;
        bool first = true;

        while (file) {
            auto row = parse_row(file);
            if (row.empty()) break;
            if (first) {
                title = row;
                first = false;
            } else {
                data.push_back(row);
            }
        }

        return {title, data};
    }

    int write_csv(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        try {
            std::ofstream file(file_name);
            if (!file.is_open()) return 0;
            for (const auto& row : data) {
                for (size_t i = 0; i < row.size(); ++i) {
                    if (i > 0) file << ",";
                    file << quote_csv_field(row[i]);
                }
                file << "\n";
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
            column_data.push_back(row[N]);
        }
        for (auto& val : column_data) {
            std::transform(val.begin(), val.end(), val.begin(),
                           [](unsigned char c) { return std::toupper(c); });
        }

        std::vector<std::vector<std::string>> new_data = {title, column_data};

        size_t dot_pos = save_file_name.find('.');
        std::string base_name = (dot_pos == std::string::npos)
                                    ? save_file_name
                                    : save_file_name.substr(0, dot_pos);
        std::string new_file_name = base_name + "_process.csv";

        return write_csv(new_data, new_file_name);
    }

private:
    // Parse one CSV row, handling quoted fields (including newlines within quotes)
    std::vector<std::string> parse_row(std::ifstream& file) {
        std::vector<std::string> row;
        std::string field;
        bool in_quotes = false;
        bool any_char_read = false;

        while (true) {
            char c;
            if (!file.get(c)) break;
            any_char_read = true;

            if (in_quotes) {
                if (c == '"') {
                    char next;
                    if (file.get(next)) {
                        if (next == '"') {
                            // Escaped double-quote
                            field += '"';
                        } else {
                            // Closing quote
                            in_quotes = false;
                            if (next == ',') {
                                row.push_back(field);
                                field.clear();
                            } else if (next == '\n') {
                                row.push_back(field);
                                field.clear();
                                return row;
                            } else if (next == '\r') {
                                char after;
                                if (file.get(after)) {
                                    if (after != '\n') {
                                        file.putback(after);
                                    }
                                }
                                row.push_back(field);
                                field.clear();
                                return row;
                            }
                            // Other chars after closing quote: skip (malformed CSV)
                        }
                    } else {
                        // EOF right after closing quote
                        in_quotes = false;
                        row.push_back(field);
                        field.clear();
                        return row;
                    }
                } else {
                    field += c;
                }
            } else {
                if (c == '"') {
                    in_quotes = true;
                } else if (c == ',') {
                    row.push_back(field);
                    field.clear();
                } else if (c == '\n') {
                    row.push_back(field);
                    field.clear();
                    return row;
                } else if (c == '\r') {
                    char next;
                    if (file.get(next)) {
                        if (next != '\n') {
                            file.putback(next);
                        }
                    }
                    row.push_back(field);
                    field.clear();
                    return row;
                } else {
                    field += c;
                }
            }
        }

        // At EOF: push the last field only if we read something
        if (any_char_read) {
            row.push_back(field);
        }

        return row;
    }

    // Quote a CSV field if it contains special characters
    std::string quote_csv_field(const std::string& field) {
        bool needs_quoting = false;
        for (char c : field) {
            if (c == ',' || c == '"' || c == '\n' || c == '\r') {
                needs_quoting = true;
                break;
            }
        }
        if (!needs_quoting) return field;

        std::string result = "\"";
        for (char c : field) {
            if (c == '"') {
                result += "\"\"";
            } else {
                result += c;
            }
        }
        result += "\"";
        return result;
    }
};