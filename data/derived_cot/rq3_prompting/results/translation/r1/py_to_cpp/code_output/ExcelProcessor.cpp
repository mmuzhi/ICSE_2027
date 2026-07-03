#include <vector>
#include <string>
#include <variant>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

// Assuming OpenXLSX library is available (https://github.com/troldal/OpenXLSX)
// Compile with -lOpenXLSX or similar.
#include <OpenXLSX/OpenXLSX.hpp>

using namespace OpenXLSX;

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    // Read Excel file; returns list of rows (each row is a list of cells).
    // Returns empty vector on failure.
    std::vector<std::vector<std::variant<int, double, std::string>>> read_excel(const std::string& file_name) {
        std::vector<std::vector<std::variant<int, double, std::string>>> data;
        try {
            XLDocument doc;
            doc.open(file_name);
            auto wks = doc.workbook().activeWorksheet();
            // Determine range
            auto range = wks.usedRange();
            if (!range) {
                doc.close();
                return data; // empty
            }
            // Iterate rows
            for (auto row = range.firstRow(); row <= range.lastRow(); ++row) {
                std::vector<std::variant<int, double, std::string>> row_data;
                for (auto col = range.firstColumn(); col <= range.lastColumn(); ++col) {
                    XLValueType type = wks.valueType(row, col);
                    if (type == XLValueType::Integer) {
                        row_data.push_back(wks.value<int>(row, col));
                    } else if (type == XLValueType::Float) {
                        row_data.push_back(wks.value<double>(row, col));
                    } else { // String, Boolean, etc. – treat as string
                        row_data.push_back(wks.value<std::string>(row, col));
                    }
                }
                data.push_back(std::move(row_data));
            }
            doc.close();
        } catch (...) {
            // Return empty on error
        }
        return data;
    }

    // Write data to Excel file.
    // Returns 1 on success, 0 on failure.
    int write_excel(const std::vector<std::vector<std::variant<int, double, std::string>>>& data,
                    const std::string& file_name) {
        try {
            XLDocument doc;
            doc.create(file_name);
            auto wks = doc.workbook().activeWorksheet();
            for (size_t r = 0; r < data.size(); ++r) {
                for (size_t c = 0; c < data[r].size(); ++c) {
                    const auto& cell = data[r][c];
                    std::visit([&](auto&& arg) {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, int>) {
                            wks.cell(r + 1, c + 1).value() = arg;
                        } else if constexpr (std::is_same_v<T, double>) {
                            wks.cell(r + 1, c + 1).value() = arg;
                        } else {
                            wks.cell(r + 1, c + 1).value() = std::string(arg);
                        }
                    }, cell);
                }
            }
            doc.save();
            doc.close();
            return 1;
        } catch (...) {
            return 0;
        }
    }

    // Process Excel data: make column N uppercase (if not numeric) and append as new column.
    // Returns {success (0/1), new file name}.
    std::pair<int, std::string> process_excel_data(int N, const std::string& save_file_name) {
        auto data = read_excel(save_file_name);
        if (data.empty() || N < 0 || (size_t)N >= data[0].size()) {
            return {0, ""};
        }
        std::vector<std::vector<std::variant<int, double, std::string>>> new_data;
        for (const auto& row : data) {
            std::vector<std::variant<int, double, std::string>> new_row = row; // copy
            // Process column N
            const auto& cell = row[N];
            std::string cell_str = to_string(cell);
            // Check if cell_str is all digits (including minus? Python .isdigit() returns False for '-' and ' ')
            // We replicate python's str(x).isdigit() which returns True only if all characters are digits.
            bool all_digits = !cell_str.empty() && std::all_of(cell_str.begin(), cell_str.end(), ::isdigit);
            if (!all_digits) {
                // Uppercase the string representation and add as new column
                std::string upper_str = cell_str;
                std::transform(upper_str.begin(), upper_str.end(), upper_str.begin(), ::toupper);
                new_row.push_back(std::move(upper_str));
            } else {
                // Keep original value (without conversion) and add it as new column
                new_row.push_back(cell);
            }
            new_data.push_back(std::move(new_row));
        }
        // Generate new file name: replace .xlsx with '_process.xlsx'
        std::string new_file_name = save_file_name;
        size_t dot_pos = new_file_name.rfind('.');
        if (dot_pos != std::string::npos) {
            new_file_name = new_file_name.substr(0, dot_pos) + "_process.xlsx";
        } else {
            new_file_name += "_process.xlsx";
        }
        int success = write_excel(new_data, new_file_name);
        return {success, new_file_name};
    }

private:
    // Helper to convert variant to string (for .isdigit() check)
    static std::string to_string(const std::variant<int, double, std::string>& v) {
        return std::visit([](auto&& arg) -> std::string {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) {
                return std::to_string(arg);
            } else if constexpr (std::is_same_v<T, double>) {
                return std::to_string(arg);
            } else {
                return arg;
            }
        }, v);
    }
};