#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <xlsx/Document.h>
#include <xlsx/Sheet.h>
#include <xlsx/Cell.h>

class ExcelProcessor {
public:
    ExcelProcessor() {}

    std::vector<std::vector<xlsx::Cell>> read_excel(const std::string& file_name) {
        try {
            xlsx::Document doc;
            auto& sheet = doc.worksheets().begin()->second; // Get the first worksheet
            std::vector<std::vector<xlsx::Cell>> data;
            for (const auto& row : sheet) {
                std::vector<xlsx::Cell> row_data;
                for (const auto& cell : row) {
                    row_data.push_back(cell);
                }
                data.push_back(row_data);
            }
            return data;
        } catch (...) {
            return std::vector<std::vector<xlsx::Cell>>();
        }
    }

    int write_excel(const std::vector<std::vector<xlsx::Cell>>& data, const std::string& file_name) {
        try {
            xlsx::Document doc;
            auto& sheet = doc.add_worksheet("Sheet1");
            for (int i = 0; i < data.size(); i++) {
                for (int j = 0; j < data[i].size(); j++) {
                    sheet->write(i, j, data[i][j]);
                }
            }
            doc.save(file_name);
            return 1;
        } catch (...) {
            return 0;
        }
    }

    std::pair<int, std::string> process_excel_data(int N, const std::string& save_file_name) {
        std::vector<std::vector<xlsx::Cell>> data = read_excel(save_file_name);
        if (data.empty() || N >= static_cast<int>(data[0].size())) {
            return {0, ""};
        }

        std::vector<std::vector<xlsx::Cell>> new_data;
        for (const auto& row : data) {
            std::vector<xlsx::Cell> new_row;
            for (int i = 0; i < row.size(); i++) {
                if (i == N) {
                    std::string cell_str = row[i].to_string();
                    bool is_digit = true;
                    if (!cell_str.empty()) {
                        for (char c : cell_str) {
                            if (!std::isdigit(static_cast<unsigned char>(c))) {
                                is_digit = false;
                                break;
                            }
                        }
                    }
                    if (is_digit) {
                        new_row.push_back(row[i]);
                    } else {
                        std::transform(cell_str.begin(), cell_str.end(), cell_str.begin(), ::toupper);
                        new_row.push_back(xlsx::Cell(cell_str));
                    }
                } else {
                    new_row.push_back(row[i]);
                }
            }
            new_data.push_back(new_row);
        }

        std::size_t pos = save_file_name.find_last_of('.');
        std::string new_file_name = save_file_name.substr(0, pos + 1) + "_process.xlsx";
        int success = write_excel(new_data, new_file_name);
        return {success, new_file_name};
    }
};