#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

class SQLGenerator {
private:
    std::string table_name;

    // Helper to join strings with delimiter
    static std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
        if (parts.empty()) return "";
        std::ostringstream oss;
        for (size_t i = 0; i < parts.size(); ++i) {
            if (i > 0) oss << delimiter;
            oss << parts[i];
        }
        return oss.str();
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::vector<std::string>* fields, const std::string* condition) {
        std::string fieldsStr;
        if (fields == nullptr) {
            fieldsStr = "*";
        } else {
            fieldsStr = join(*fields, ", ");
        }
        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (condition != nullptr) {
            sql += " WHERE " + *condition;
        }
        return sql + ";";
    }

    std::string insert(const std::map<std::string, std::string>& data) {
        // std::map is already sorted by key (like TreeMap)
        std::vector<std::string> fieldNames;
        std::vector<std::string> values;
        for (const auto& entry : data) {
            fieldNames.push_back(entry.first);
            values.push_back("'" + entry.second + "'");
        }
        std::string fields = join(fieldNames, ", ");
        std::string vals = join(values, ", ");
        return "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + vals + ");";
    }

    std::string update(const std::map<std::string, std::string>& data, const std::string& condition) {
        // std::map is sorted by key
        std::vector<std::string> setClauses;
        for (const auto& entry : data) {
            setClauses.push_back(entry.first + " = '" + entry.second + "'");
        }
        std::string setStr = join(setClauses, ", ");
        return "UPDATE " + table_name + " SET " + setStr + " WHERE " + condition + ";";
    }

    std::string del(const std::string& condition) {
        return "DELETE FROM " + table_name + " WHERE " + condition + ";";
    }

    std::string selectFemaleUnderAge(int age) {
        return "SELECT * FROM " + table_name + " WHERE age < " + std::to_string(age) + " AND gender = 'female';";
    }

    std::string selectByAgeRange(int minAge, int maxAge) {
        return "SELECT * FROM " + table_name + " WHERE age BETWEEN " + std::to_string(minAge) + " AND " + std::to_string(maxAge) + ";";
    }
};