#pragma once

#include <OpenXLSX.hpp>
#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <algorithm>
#include <cctype>

using Object = std::variant<std::nullptr_t, std::string, int>;

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    std::optional<std::vector<std::vector<Object>>> readExcel(const std::string& fileName) {
        std::vector<std::vector<Object>> data;
        try {
            OpenXLSX::XLDocument doc;
            doc.open(fileName);
            auto wb = doc.workbook();
            auto ws = wb.worksheet(0);

            uint32_t rowCount = ws.rowCount();
            uint32_t colCount = ws.columnCount();

            for (uint32_t r = 1; r <= rowCount; ++r) {
                std::vector<Object> rowData;
                for (uint32_t c = 1; c <= colCount; ++c) {
                    auto cell = ws.cell(r, c);
                    auto val = cell.value();
                    auto type = val.type();

                    if (type == OpenXLSX::XLValueType::String) {
                        rowData.emplace_back(val.get<std::string>());
                    } else if (type == OpenXLSX::XLValueType::Integer) {
                        rowData.emplace_back(val.get<int>());
                    } else if (type == OpenXLSX::XLValueType::Float) {
                        rowData.emplace_back(static_cast<int>(val.get<double>()));
                    } else {
                        rowData.emplace_back(nullptr);
                    }
                }
                data.push_back(std::move(rowData));
            }
        } catch (...) {
            return std::nullopt;
        }
        return data;
    }

    bool writeExcel(const std::vector<std::vector<Object>>& data, const std::string& fileName) {
        try {
            OpenXLSX::XLDocument doc;
            doc.create(fileName);
            auto wb = doc.workbook();
            auto ws = wb.worksheet(0);
            ws.setName("Sheet1");

            for (size_t i = 0; i < data.size(); ++i) {
                const auto& rowData = data[i];
                for (size_t j = 0; j < rowData.size(); ++j) {
                    auto cell = ws.cell(static_cast<uint32_t>(i + 1),
                                        static_cast<uint32_t>(j + 1));
                    const auto& value = rowData[j];
                    if (std::holds_alternative<std::string>(value)) {
                        cell.value() = std::get<std::string>(value);
                    } else if (std::holds_alternative<int>(value)) {
                        cell.value() = std::get<int>(value);
                    }
                    // nullptr_t: leave cell empty
                }
            }
            doc.save();
            return true;
        } catch (...) {
            return false;
        }
    }

    std::optional<std::string> processExcelData(int N, const std::string& saveFileName) {
        auto dataOpt = readExcel(saveFileName);
        if (!dataOpt.has_value() || N >= static_cast<int>(dataOpt->at(0).size())) {
            return std::nullopt;
        }

        auto& data = *dataOpt;
        std::vector<std::vector<Object>> newData;

        for (const auto& row : data) {
            std::vector<Object> newRow(row);
            const auto& value = row.at(N);
            if (std::holds_alternative<std::string>(value)) {
                std::string upper = std::get<std::string>(value);
                std::transform(upper.begin(), upper.end(), upper.begin(),
                               [](unsigned char c) { return std::toupper(c); });
                newRow.emplace_back(std::move(upper));
            } else {
                newRow.emplace_back(value);
            }
            newData.push_back(std::move(newRow));
        }

        std::string newFileName = saveFileName;
        auto pos = newFileName.find(".xlsx");
        if (pos != std::string::npos) {
            newFileName.replace(pos, 5, "_process.xlsx");
        }

        bool success = writeExcel(newData, newFileName);
        return success ? std::optional<std::string>(newFileName) : std::nullopt;
    }
};