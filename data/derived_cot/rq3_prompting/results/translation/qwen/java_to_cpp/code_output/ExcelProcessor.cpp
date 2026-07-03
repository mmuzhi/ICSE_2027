#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <xlsxwriter/xlsxwriter.h>
#include <xlsxreader/xlsxreader.h>

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    std::optional<std::vector<std::vector<std::variant<std::string, int, std::nullptr_t>>>> readExcel(const std::string& fileName) {
        auto* file = xlsx_open(fileName.c_str(), "r");
        if (!file) {
            return std::nullopt;
        }

        auto* sheet = xlsx_file_get_sheet(file, 0);
        if (!sheet) {
            xlsx_close(file);
            return std::nullopt;
        }

        std::vector<std::vector<std::variant<std::string, int, std::nullptr_t>>> data;
        for (int i = 0; i < xlsx_sheet_get_row_count(sheet); ++i) {
            auto* row = xlsx_sheet_get_row(sheet, i);
            if (!row) continue;

            std::vector<std::variant<std::string, int, std::nullptr_t>> rowData;
            for (int j = 0; j < xlsx_row_get_cell_count(row); ++j) {
                auto* cell = xlsx_row_get_cell(row, j);
                if (!cell) continue;

                std::variant<std::string, int, std::nullptr_t> value;
                switch (xlsx_cell_get_type(cell)) {
                    case XLSX_CELL_STRING:
                        value = xlsx_cell_get_string(cell);
                        break;
                    case XLSX_CELL_NUMERIC:
                        value = static_cast<int>(xlsx_cell_get_numeric(cell));
                        break;
                    default:
                        value = nullptr;
                        break;
                }
                rowData.push_back(value);
            }
            if (!rowData.empty()) {
                data.push_back(rowData);
            }
        }

        xlsx_close(file);
        return data;
    }

    bool writeExcel(const std::vector<std::vector<std::variant<std::string, int, std::nullptr_t>>>& data, const std::string& fileName) {
        auto create = xlsx_create_t{0};
        create.overwrite = 1;
        auto* file = xlsx_create_file(fileName.c_str(), &create);
        if (!file) return false;

        auto* sheet = xlsx_file_add_sheet(file, "Sheet1");
        if (!sheet) {
            xlsx_close(file);
            return false;
        }

        for (int i = 0; i < data.size(); ++i) {
            auto* row = xlsx_sheet_add_row(sheet);
            if (!row) {
                xlsx_close(file);
                return false;
            }

            for (int j = 0; j < data[i].size(); ++j) {
                auto* cell = xlsx_row_add_cell(row);
                if (!cell) {
                    xlsx_close(file);
                    return false;
                }

                if (std::holds_alternative<std::string>(data[i][j])) {
                    xlsx_cell_set_string(cell, std::get<std::string>(data[i][j]).c_str());
                } else if (std::holds_alternative<int>(data[i][j])) {
                    xlsx_cell_set_numeric(cell, static_cast<double>(std::get<int>(data[i][j])));
                }
            }
        }

        xlsx_close(file);
        return true;
    }

    std::string processExcelData(int N, const std::string& saveFileName) {
        auto data = readExcel(saveFileName);
        if (!data || data.value().empty() || N >= data.value()[0].size()) {
            return nullptr;
        }

        std::vector<std::vector<std::variant<std::string, int, std::nullptr_t>>> newData;
        for (const auto& row : data.value()) {
            std::vector<std::variant<std::string, int, std::nullptr_t>> newRow(row.begin(), row.end());
            if (std::holds_alternative<std::string>(newRow[N])) {
                std::string original = std::get<std::string>(newRow[N]);
                std::string upper(original.begin(), original.end());
                std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
                newRow[N] = upper;
            }
            newData.push_back(newRow);
        }

        std::string newFileName = saveFileName;
        if (newFileName.size() >= 5 && newFileName.substr(newFileName.size() - 5) == ".xlsx") {
            newFileName = newFileName.substr(0, newFileName.size() - 5) + "_process.xlsx";
        } else {
            newFileName += "_process.xlsx";
        }

        if (writeExcel(newData, newFileName)) {
            return newFileName;
        } else {
            return nullptr;
        }
    }
};