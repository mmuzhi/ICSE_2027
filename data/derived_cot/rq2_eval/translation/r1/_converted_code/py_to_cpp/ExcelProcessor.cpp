#include <xlnt/xlnt.hpp>
#include <vector>
#include <variant>
#include <optional>
#include <algorithm>
#include <cctype>
#include <utility>
#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>

using CellValue = std::variant<std::string, int, double>;
using Row = std::vector<CellValue>;
using Data = std::vector<Row>;

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    std::optional<Data> read_excel(const std::string& file_name) {
        try {
            std::ifstream file(file_name);
            if (!file.good()) {
                return std::nullopt;
            }
            xlnt::workbook workbook;
            workbook.load(file_name);
            xlnt::worksheet sheet = workbook.active_sheet();

            Data data;
            for (auto row : sheet.rows()) {
                Row current_row;
                for (auto cell : row) {
                    if (cell.data_type() == xlnt::cell_type::empty) {
                        current_row.push_back(std::string(""));
                    } else if (cell.data_type() == xlnt::cell_type::number) {
                        if (cell.value<int>() == cell.value<double>()) {
                            current_row.push_back(cell.value<int>());
                        } else {
                            current_row.push_back(cell.value<double>());
                        }
                    } else {
                        current_row.push_back(cell.to_string());
                    }
                }
                data.push_back(current_row);
            }
            return data;
        } catch (...) {
            return std::nullopt;
        }
    }

    int write_excel(const Data& data, const std::string& file_name) {
        try {
            xlnt::workbook workbook;
            xlnt::worksheet sheet = workbook.active_sheet();

            int row_index = 1;
            for (const auto& row : data) {
                int col_index = 1;
                for (const auto& cell : row) {
                    if (std::holds_alternative<std::string>(cell)) {
                        sheet.cell(xlnt::cell_reference(col_index, row_index)).value(std::get<std::string>(cell));
                    } else if (std::holds_alternative<int>(cell)) {
                        sheet.cell(xlnt::cell_reference(col_index, row_index)).value(std::get<int>(cell));
                    } else if (std::holds_alternative<double>(cell)) {
                        sheet.cell(xlnt::cell_reference(col_index, row_index)).value(std::get<double>(cell));
                    }
                    col_index++;
                }
                row_index++;
            }
            workbook.save(file_name);
            return 1;
        } catch (...) {
            return 0;
        }
    }

    std::pair<int, std::string> process_excel_data(int N, const std::string& save_file_name) {
        auto data = read_excel(save_file_name);
        if (!data) {
            return {0, ""};
        }
        if (data->empty()) {
            throw std::out_of_range("Accessing row 0 of empty data");
        }
        if (N >= data->at(0).size()) {
            return {0, ""};
        }

        Data new_data;
        for (const auto& row : *data) {
            Row new_row = row;
            std::string str_value = cell_to_string(row[N]);
            if (is_digit(str_value)) {
                new_row.push_back(row[N]);
            } else {
                new_row.push_back(to_upper(str_value));
            }
            new_data.push_back(new_row);
        }

        std::string new_file_name = save_file_name;
        size_t pos = new_file_name.find_last_of('.');
        if (pos != std::string::npos) {
            new_file_name = new_file_name.substr(0, pos) + "_process.xlsx";
        } else {
            new_file_name += "_process.xlsx";
        }

        int success = write_excel(new_data, new_file_name);
        return {success, new_file_name};
    }

private:
    std::string cell_to_string(const CellValue& cell) const {
        if (std::holds_alternative<std::string>(cell)) {
            return std::get<std::string>(cell);
        } else if (std::holds_alternative<int>(cell)) {
            return std::to_string(std::get<int>(cell));
        } else if (std::holds_alternative<double>(cell)) {
            return std::to_string(std::get<double>(cell));
        }
        return "";
    }

    bool is_digit(const std::string& s) const {
        return !s.empty() && std::all_of(s.begin(), s.end(), [](unsigned char c) { return std::isdigit(c); });
    }

    std::string to_upper(const std::string& s) const {
        std::string result = s;
        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
        return result;
    }
};