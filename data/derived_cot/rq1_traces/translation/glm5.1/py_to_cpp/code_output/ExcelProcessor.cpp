#include <OpenXLSX.hpp>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <algorithm>
#include <cctype>

class ExcelProcessor {
public:
    ExcelProcessor() {}

    /**
     * Reading data from Excel files
     * @param file_name Excel file name to read
     * @return Data in Excel, or std::nullopt on failure
     */
    std::optional<std::vector<std::vector<std::string>>> read_excel(const std::string& file_name) {
        try {
            OpenXLSX::XLDocument doc;
            doc.open(file_name);
            auto sheet = doc.workbook().worksheet(doc.workbook().sheetNames().front());
            std::vector<std::vector<std::string>> data;
            for (auto& row : sheet.rows()) {
                std::vector<std::string> rowData;
                for (auto& cell : row.cells()) {
                    if (cell.value().type() == OpenXLSX::XLValueType::Empty) {
                        // openpyxl returns None for empty cells, which becomes "None" in str()
                        rowData.push_back("None");
                    } else {
                        rowData.push_back(cell.value().getString());
                    }
                }
                data.push_back(rowData);
            }
            doc.close();
            return data;
        } catch (...) {
            return std::nullopt;
        }
    }

    /**
     * Write data to the specified Excel file
     * @param data Data to be written
     * @param file_name Excel file name to write to
     * @return 1 on success, 0 on failure
     */
    int write_excel(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        try {
            OpenXLSX::XLDocument doc;
            doc.create(file_name);
            auto sheet = doc.workbook().addWorksheet("Sheet1");
            for (size_t i = 0; i < data.size(); ++i) {
                auto row = sheet.row(i + 1);   // OpenXLSX rows are 1-indexed
                row.setValues(data[i]);
            }
            doc.save();
            doc.close();
            return 1;
        } catch (...) {
            return 0;
        }
    }

    /**
     * Change the specified column in the Excel file to uppercase
     * @param N The serial number of the column that want to change
     * @param save_file_name source file name
     * @return On failure 0 (int), on success a pair of (success_code, new_file_name)
     *
     * Note: The return type mimics the Python code exactly:
     *       - returns 0 (int) if data is missing or N is out of range
     *       - returns std::pair<int, std::string> on success
     */
    std::variant<int, std::pair<int, std::string>> process_excel_data(int N, const std::string& save_file_name) {
        auto data = read_excel(save_file_name);
        if (!data || N >= static_cast<int>(data->at(0).size())) {
            return 0;
        }

        std::vector<std::vector<std::string>> new_data;
        for (const auto& row : *data) {
            std::vector<std::string> new_row = row;
            std::string cellValue = row.at(N);

            // Replicate Python's str(row[N]).isdigit()
            bool isDigit = !cellValue.empty() &&
                           std::all_of(cellValue.begin(), cellValue.end(),
                                       [](unsigned char c) { return std::isdigit(c); });

            if (!isDigit) {
                std::string upperVal = cellValue;
                std::transform(upperVal.begin(), upperVal.end(), upperVal.begin(),
                               [](unsigned char c) { return std::toupper(c); });
                new_row.push_back(upperVal);
            } else {
                new_row.push_back(cellValue);
            }
            new_data.push_back(new_row);
        }

        // Create new file name: original_name + "_process.xlsx"
        size_t dotPos = save_file_name.find_last_of('.');
        std::string new_file_name = (dotPos == std::string::npos ? save_file_name : save_file_name.substr(0, dotPos)) + "_process.xlsx";

        int success = write_excel(new_data, new_file_name);
        return std::make_pair(success, new_file_name);
    }
};