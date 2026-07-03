#include <xlnt/xlnt.hpp>
#include <optional>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

class CellValue {
public:
    enum class Type { Null, Int, String };

    CellValue() : type_(Type::Null) {}
    CellValue(int value) : type_(Type::Int), int_value_(value) {}
    CellValue(const std::string& value) : type_(Type::String), string_value_(value) {}

    Type getType() const { return type_; }

    int asInt() const {
        if (type_ != Type::Int) {
            throw std::runtime_error("Not an integer");
        }
        return int_value_;
    }

    const std::string& asString() const {
        if (type_ != Type::String) {
            throw std::runtime_error("Not a string");
        }
        return string_value_;
    }

private:
    Type type_;
    int int_value_;
    std::string string_value_;
};

using Data = std::vector<std::vector<CellValue>>;

std::optional<Data> readExcel(const std::string& fileName) {
    try {
        xlnt::workbook wb;
        wb.load(fileName);
        auto sheet = wb.active_sheet();
        Data data;

        for (auto row : sheet.rows()) {
            if (row.begin() == row.end()) {
                continue;
            }

            std::vector<CellValue> rowData;
            for (auto cell : row) {
                if (cell.data_type() == xlnt::cell_type::empty) {
                    continue;
                }

                if (cell.data_type() == xlnt::cell_type::string) {
                    rowData.push_back(CellValue(cell.to_string()));
                } else if (cell.data_type() == xlnt::cell_type::number) {
                    double d = cell.value<double>();
                    rowData.push_back(CellValue(static_cast<int>(d)));
                } else {
                    rowData.push_back(CellValue());
                }
            }
            data.push_back(rowData);
        }
        return data;
    } catch (...) {
        return std::nullopt;
    }
}

bool writeExcel(const Data& data, const std::string& fileName) {
    try {
        xlnt::workbook wb;
        auto sheet = wb.active_sheet();
        sheet.title("Sheet1");

        for (std::size_t i = 0; i < data.size(); i++) {
            auto row = data[i];
            for (std::size_t j = 0; j < row.size(); j++) {
                const CellValue& value = row[j];
                if (value.getType() == CellValue::Type::String) {
                    sheet.cell(xlnt::column_t(j + 1), i + 1).value(value.asString());
                } else if (value.getType() == CellValue::Type::Int) {
                    sheet.cell(xlnt::column_t(j + 1), i + 1).value(value.asInt());
                }
            }
        }
        wb.save(fileName);
        return true;
    } catch (...) {
        return false;
    }
}

std::optional<std::string> processExcelData(int N, const std::string& saveFileName) {
    std::optional<Data> data = readExcel(saveFileName);
    if (!data || data->empty() || N >= data.value()[0].size()) {
        return std::nullopt;
    }

    Data newData;
    for (const auto& row : data.value()) {
        std::vector<CellValue> newRow = row;
        if (N < row.size()) {
            const CellValue& value = row[N];
            if (value.getType() == CellValue::Type::String) {
                std::string upperStr = value.asString();
                std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(),
                    [](unsigned char c) { return std::toupper(c); });
                newRow.push_back(CellValue(upperStr));
            } else {
                newRow.push_back(value);
            }
        } else {
            newRow.push_back(CellValue());
        }
        newData.push_back(newRow);
    }

    std::string newFileName = saveFileName;
    size_t pos = newFileName.find(".xlsx");
    if (pos != std::string::npos) {
        newFileName.replace(pos, 5, "_process.xlsx");
    } else {
        newFileName += "_process.xlsx";
    }

    bool success = writeExcel(newData, newFileName);
    return success ? std::optional<std::string>(newFileName) : std::nullopt;
}