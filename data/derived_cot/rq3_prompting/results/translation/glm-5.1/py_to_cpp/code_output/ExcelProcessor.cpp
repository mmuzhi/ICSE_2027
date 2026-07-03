#include <OpenXLSX.hpp>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <cctype>
#include <utility>

class ExcelProcessor {
public:
    ExcelProcessor() {}

    std::optional<std::vector<std::vector<std::string>>> read_excel(const std::string& file_name) {
        std::vector<std::vector<std::string>> data;
        try {
            OpenXLSX::XLDocument doc;
            doc.open(file_name);
            auto wb = doc.workbook();
            auto ws = wb.worksheet(wb.worksheetNames()[0]);

            uint32_t numRows = ws.rowCount();
            uint32_t numCols = ws.columnCount();

            for (uint32_t r = 1; r <= numRows; ++r) {
                std::vector<std::string> row_data;
                for (uint32_t c = 1; c <= numCols; ++c) {
                    row_data.push_back(cell_to_string(ws.cell(r, c)));
                }
                data.push_back(std::move(row_data));
            }

            doc.close();
            return data;
        } catch (...) {
            return std::nullopt;
        }
    }

    int write_excel(const std::vector<std::vector<std::string>>& data, const std::string& file_name) {
        try {
            OpenXLSX::XLDocument doc;
            doc.create(file_name);
            auto wb = doc.workbook();
            auto ws = wb.worksheet(wb.worksheetNames()[0]);

            for (uint32_t i = 0; i < static_cast<uint32_t>(data.size()); ++i) {
                for (uint32_t j = 0; j < static_cast<uint32_t>(data[i].size()); ++j) {
                    ws.cell(i + 1, j + 1).value() = data[i][j];
                }
            }

            doc.save();
            doc.close();
            return 1;
        } catch (...) {
            return 0;
        }
    }

    std::pair<int, std::string> process_excel_data(int N, const std::string& save_file_name) {
        auto data_opt = read_excel(save_file_name);
        if (!data_opt.has_value() || N >= static_cast<int>(data_opt->at(0).size())) {
            return {0, ""};
        }

        auto& data = *data_opt;
        std::vector<std::vector<std::string>> new_data;

        for (auto& row : data) {
            std::vector<std::string> new_row = row;
            const std::string& val = row[N];
            if (!is_all_digits(val)) {
                std::string upper_val = val;
                std::transform(upper_val.begin(), upper_val.end(), upper_val.begin(),
                    [](unsigned char c) { return std::toupper(c); });
                new_row.push_back(std::move(upper_val));
            } else {
                new_row.push_back(val);
            }
            new_data.push_back(std::move(new_row));
        }

        std::string base = save_file_name;
        auto dot_pos = base.find('.');
        if (dot_pos != std::string::npos) {
            base = base.substr(0, dot_pos);
        }
        std::string new_file_name = base + "_process.xlsx";

        int success = write_excel(new_data, new_file_name);
        return {success, new_file_name};
    }

private:
    static std::string cell_to_string(const OpenXLSX::XLCell& cell) {
        auto val = cell.value();
        switch (val.type()) {
            case OpenXLSX::XLValueType::String:
                return val.get<std::string>();
            case OpenXLSX::XLValueType::Integer:
                return std::to_string(val.get<int64_t>());
            case OpenXLSX::XLValueType::Float:
                return std::to_string(val.get<double>());
            case OpenXLSX::XLValueType::Boolean:
                return val.get<bool>() ? "True" : "False";
            default:
                return "";
        }
    }

    static bool is_all_digits(const std::string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        }
        return true;
    }
};