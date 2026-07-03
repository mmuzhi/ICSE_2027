#include <vector>
#include <string>
#include <map>
#include <optional>
#include <sstream>

class SQLGenerator {
private:
    std::string table_name;

    // Helper function to join a vector of strings
    std::string join(const std::vector<std::string>& vec) {
        if (vec.empty()) {
            return "";
        }
        std::string result;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i > 0) {
                result += ", ";
            }
            result += vec[i];
        }
        return result;
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::vector<std::string>& fields, std::optional<std::string> condition) {
        std::string fieldsStr;
        if (fields.empty()) {
            fieldsStr = "*";
        } else {
            fieldsStr = join(fields);
        }
        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (condition) {
            sql += " WHERE " + *condition;
        }
        return sql + ";";
    }

    std::string insert(const std::map<std::string, std::string>& data) {
        std::string fieldsStr;
        for (const auto& entry : data) {
            if (!fieldsStr.empty()) {
                fieldsStr += ", ";
            }
            fieldsStr += entry.first;
        }

        std::string valuesStr;
        for (const auto& entry : data) {
            if (!valuesStr.empty()) {
                valuesStr += ", ";
            }
            valuesStr += "'" + entry.second + "'";
        }

        return "INSERT INTO " + table_name + " (" + fieldsStr + ") VALUES (" + valuesStr + ");";
    }

    std::string update(const std::map<std::string, std::string>& data, std::optional<std::string> condition) {
        std::string setClause;
        for (const auto& entry : data) {
            if (!setClause.empty()) {
                setClause += ", ";
            }
            setClause += entry.first + " = '" + entry.second + "'";
        }

        std::string wherePart;
        if (condition) {
            wherePart = " WHERE " + *condition;
        }

        return "UPDATE " + table_name + " SET " + setClause + wherePart + ";";
    }

    std::string remove(const std::optional<std::string> condition) {
        std::string wherePart;
        if (condition) {
            wherePart = " WHERE " + *condition;
        }
        return "DELETE FROM " + table_name + wherePart + ";";
    }

    std::string selectFemaleUnderAge(int age) {
        return "SELECT * FROM " + table_name + " WHERE age < " + std::to_string(age) + " AND gender = 'female';";
    }

    std::string selectByAgeRange(int minAge, int maxAge) {
        return "SELECT * FROM " + table_name + " WHERE age BETWEEN " + std::to_string(minAge) + " AND " + std::to_string(maxAge) + ";";
    }
};