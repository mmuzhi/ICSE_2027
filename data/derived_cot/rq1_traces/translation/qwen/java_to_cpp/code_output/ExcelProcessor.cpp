#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <monostate>

// Hypothetical Excel library functions
namespace ExcelLib {
    // Reads an Excel file and returns the first sheet as a 2D vector of cells
    std::vector<std::vector<std::variant<std::string, int, std::monostate>>> readExcel(const std::string& fileName) {
        // Implementation would use a third-party Excel library
        // This is a placeholder
        return std::vector<std::vector<std::variant<std::string, int, std::monostate>>>();
    }

    // Writes a 2D vector of cells to an Excel file
    bool writeExcel(const std::vector<std::vector<std::variant<std::string, int, std::monostate>>>& data, const std::string& fileName) {
        // Implementation would use a third-party Excel library
        // This is a placeholder
        return true;
    }
}

// Define a type for cell value: string, int, or null
using CellValue = std::variant<std::string, int, std::monostate>;

class ExcelProcessor {
public:
    ExcelProcessor() = default;

    // Read an Excel file and return a 2D vector of CellValue
    std::vector<std::vector<CellValue>> readExcel(const std::string& fileName) {
        try {
            return ExcelLib::readExcel(fileName);
        } catch (...) {
            // Return empty data on error to mimic Java's null behavior
            return std::vector<std::vector<CellValue>>();
        }
    }

    // Write a 2D vector of CellValue to an Excel file, return true if successful
    bool writeExcel(const std::vector<std::vector<CellValue>>& data, const std::string& fileName) {
        try {
            return ExcelLib::writeExcel(data, fileName);
        } catch (...) {
            return false;
        }
    }

    // Process the Excel data: convert the N-th column to uppercase if string
    std::optional<std::string> processExcelData(int N, const std::string& saveFileName) {
        auto data = readExcel(saveFileName);
        // Check if data is empty or if N is out of bounds for the first row
        if (data.empty() || N >= data[0].size()) {
            return std::nullopt;
        }

        // We'll create newData by transforming the N-th column
        std::vector<std::vector<CellValue>> newData;
        for (auto& row : data) {
            std::vector<CellValue> newRow = row;
            // Get the value at position N
            auto& value = newRow[N];
            // If the value is a string, convert to uppercase
            if (std::holds_alternative<std::string>(value)) {
                std::string s = std::get<std::string>(value);
                // Convert to uppercase
                for (char& c : s) {
                    c = std::toupper(c);
                }
                newRow[N] = s;
            }
            // Otherwise, leave it as is
            newData.push_back(newRow);
        }

        // Generate new file name
        std::string newFileName = saveFileName;
        // Assuming the original file has extension .xlsx, we replace it
        if (newFileName.size() >= 5 && newFileName.substr(newFileName.size() - 5) == ".xlsx") {
            newFileName.replace(newFileName.size() - 5, 5, "_process.xlsx");
        } else {
            // If the extension is not .xlsx, append "_process.xlsx"
            newFileName += "_process.xlsx";
        }

        // Write the new data to the new file
        if (writeExcel(newData, newFileName)) {
            return newFileName;
        } else {
            return std::nullopt;
        }
    }
};