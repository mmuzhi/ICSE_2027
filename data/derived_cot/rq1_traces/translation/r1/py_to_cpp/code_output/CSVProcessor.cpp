#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cctype>
#include <stdexcept>

using namespace std;

class CSVProcessor {
public:
    CSVProcessor() {}

    pair<vector<string>, vector<vector<string>>> read_csv(const string& file_name) {
        ifstream file(file_name);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + file_name);
        }

        vector<vector<string>> data;
        vector<string> title;
        string line;

        if (getline(file, line)) {
            title = parse_csv_line(line);
        }

        while (getline(file, line)) {
            vector<string> row = parse_csv_line(line);
            if (!row.empty()) {
                data.push_back(row);
            }
        }

        return make_pair(title, data);
    }

    int write_csv(const vector<vector<string>>& data, const string& file_name) {
        ofstream file(file_name, ios::out | ios::binary);
        if (!file.is_open()) {
            return 0;
        }

        for (const vector<string>& row : data) {
            string line = format_csv_row(row);
            file << line << '\n';
            if (file.fail()) {
                return 0;
            }
        }

        return 1;
    }

    int process_csv_data(int N, const string& save_file_name) {
        auto p = read_csv(save_file_name);
        vector<string> title = p.first;
        vector<vector<string>> data = p.second;

        vector<string> column_data;
        for (const vector<string>& row : data) {
            if (static_cast<size_t>(N) >= row.size()) {
                throw out_of_range("Index N is out of range");
            }
            column_data.push_back(row[N]);
        }

        for (string& s : column_data) {
            transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return toupper(c); });
        }

        vector<vector<string>> new_data;
        new_data.push_back(title);
        new_data.push_back(column_data);

        size_t dot_index = save_file_name.find_last_of('.');
        string new_file_name = save_file_name.substr(0, dot_index) + "_process.csv";
        return write_csv(new_data, new_file_name);
    }

private:
    vector<string> parse_csv_line(const string& line) {
        vector<string> tokens;
        string token;
        bool in_quotes = false;
        size_t i = 0;
        while (i < line.length()) {
            if (line[i] == '"') {
                if (in_quotes) {
                    if (i + 1 < line.length() && line[i + 1] == '"') {
                        token += '"';
                        i++;
                    } else {
                        in_quotes = false;
                    }
                } else {
                    in_quotes = true;
                }
            } else if (line[i] == ',' && !in_quotes) {
                tokens.push_back(token);
                token.clear();
            } else {
                token += line[i];
            }
            i++;
        }
        tokens.push_back(token);
        return tokens;
    }

    string format_csv_row(const vector<string>& row) {
        string result;
        for (size_t i = 0; i < row.size(); i++) {
            string field = row[i];
            bool needs_quotes = field.find(',') != string::npos || 
                                field.find('"') != string::npos || 
                                field.find('\n') != string::npos;

            if (needs_quotes) {
                result += '"';
                for (char c : field) {
                    if (c == '"') {
                        result += "\"\"";
                    } else {
                        result += c;
                    }
                }
                result += '"';
            } else {
                result += field;
            }

            if (i < row.size() - 1) {
                result += ',';
            }
        }
        return result;
    }
};