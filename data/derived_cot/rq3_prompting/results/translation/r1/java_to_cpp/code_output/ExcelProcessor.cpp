#include <xlnt/xlnt.hpp>

#include <algorithm>
#include <any>
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    std::optional<std::vector<std::vector<std::any>>>
    readExcel(const std::string& fileName) {
        try {
            xlnt::workbook wb;
            wb.load(fileName);
            xlnt::worksheet ws = wb.sheet_by_index(0);

            std::vector<std::vector<std::any>> data;
            for (auto row : ws.rows(false)) {
                std::vector<std::any> rowData;
                for (auto cell : row.cells()) {
                    switch (cell.data_type()) {
                    case xlnt::cell::type::string:
                        rowData.emplace_back(cell.to_string());
                        break;
                    case xlnt::cell::type::number:
                        rowData.emplace_back(
                            static_cast<int>(cell.value<double>()));
                        break;
                    default:
                        rowData.emplace_back(); // empty any = null
                        break;
                    }
                }
                data.push_back(std::move(rowData));
            }
            return data;
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }

    bool writeExcel(const std::vector<std::vector<std::any>>& data,
                    const std::string& fileName) {
        try {
            xlnt::workbook wb;
            xlnt::worksheet ws = wb.active_sheet();
            ws.title("Sheet1");

            for (std::size_t i = 0; i < data.size(); ++i) {
                xlnt::row row = ws.row(static_cast<xlnt::row_t>(i + 1));
                const auto& rowData = data[i];
                for (std::size_t j = 0; j < rowData.size(); ++j) {
                    const auto& value = rowData[j];
                    xlnt::cell cell = row.cell(static_cast<xlnt::column_t>(j + 1));
                    if (value.type() == typeid(std::string)) {
                        cell.value(std::any_cast<std::string>(value));
                    } else if (value.type() == typeid(int)) {
                        cell.value(std::any_cast<int>(value));
                    }
                    // else: null – leave cell empty
                }
            }

            wb.save(fileName);
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }

    std::optional<std::string>
    processExcelData(int N, const std::string& saveFileName) {
        auto dataOpt = readExcel(saveFileName);
        if (!dataOpt || dataOpt->empty() ||
            static_cast<std::size_t>(N) >= (*dataOpt)[0].size()) {
            return std::nullopt;
        }

        const auto& data = *dataOpt;
        std::vector<std::vector<std::any>> newData;
        for (const auto& row : data) {
            std::vector<std::any> newRow = row; // copy
            const auto& value = row[N];
            if (value.type() == typeid(std::string)) {
                std::string upper =
                    std::any_cast<std::string>(value);
                std::transform(upper.begin(), upper.end(), upper.begin(),
                               ::toupper);
                newRow.push_back(std::move(upper));
            } else {
                newRow.push_back(value); // copy original (including null)
            }
            newData.push_back(std::move(newRow));
        }

        std::string newFileName = saveFileName;
        auto pos = newFileName.find(".xlsx");
        if (pos != std::string::npos) {
            newFileName.replace(pos, 5, "_process.xlsx");
        } else {
            // fallback: just append suffix (should not happen with valid name)
            newFileName += "_process.xlsx";
        }

        bool success = writeExcel(newData, newFileName);
        return success ? std::optional<std::string>(std::move(newFileName))
                       : std::nullopt;
    }
};