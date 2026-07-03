#include <string>
#include <map>
#include <vector>
#include <sstream>

class SQLGenerator {
private:
    std::string table_name;

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::vector<std::string>& fields, const std::string& condition) {
        std::string fieldsStr;
        if (fields.empty()) {
            fieldsStr = "*";
        } else {
            for (size_t i = 0; i < fields.size(); ++i) {
                if (i > 0) {
                    fieldsStr += ", ";
                }
                fieldsStr += fields[i];
            }
        }
        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (!condition.empty()) {
            sql += " WHERE " + condition;
        }
        return sql + ";";
    }

    template <typename MapT>
    std::string insert(MapT data) {
        std::map<std::string, std::string> sortedData;
        for (const auto& entry : data) {
            sortedData[entry.first] = entry.second;
        }
        std::string fields;
        for (const auto& entry : sortedData) {
            if (!fields.empty()) {
                fields += ", ";
            }
            fields += entry.first;
        }
        std::string values;
        for (const auto& entry : sortedData) {
            if (!values.empty()) {
                values += ", ";
            }
            values += "'" + entry.second + "'";
        }
        return "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + values + ");";
    }

    template <typename MapT>
    std::string update(MapT data, const std::string& condition) {
        std::map<std::string, std::string> sortedData;
        for (const auto& entry : data) {
            sortedData[entry.first] = entry.second;
        }
        std::string setClause;
        for (const auto& entry : sortedData) {
            if (!setClause.empty()) {
                setClause += ", ";
            }
            setClause += entry.first + " = '" + entry.second + "'";
        }
        return "UPDATE " + table_name + " SET " + setClause + " WHERE " + condition + ";";
    }

    std::string delete_query(const std::string& condition) {
        return "DELETE FROM " + table_name + " WHERE " + condition + ";";
    }

    std::string select_female_under_age(int age) {
        return "SELECT * FROM " + table_name + " WHERE age < " + std::to_string(age) + " AND gender = 'female';";
    }

    std::string select_by_age_range(int minAge, int maxAge) {
        return "SELECT * FROM " + table_name + " WHERE age BETWEEN " + std::to_string(minAge) + " AND " + std::to_string(maxAge) + ";";
    }
};