#pragma once
#include <string>
#include <vector>
#include <map>
#include <optional>

class SQLGenerator {
private:
    std::string table_name;

    static std::string join(const std::vector<std::string>& parts, const std::string& delim) {
        std::string result;
        for (size_t i = 0; i < parts.size(); ++i) {
            if (i > 0) result += delim;
            result += parts[i];
        }
        return result;
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::optional<std::vector<std::string>>& fields, const std::optional<std::string>& condition) {
        std::string fieldsStr = fields.has_value() ? join(*fields, ", ") : "*";
        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (condition.has_value()) {
            sql += " WHERE " + *condition;
        }
        return sql + ";";
    }

    std::string insert(const std::map<std::string, std::string>& data) {
        std::vector<std::string> keys, vals;
        for (const auto& [k, v] : data) {
            keys.push_back(k);
            vals.push_back("'" + v + "'");
        }
        return "INSERT INTO " + table_name + " (" + join(keys, ", ") + ") VALUES (" + join(vals, ", ") + ");";
    }

    std::string update(const std::map<std::string, std::string>& data, const std::string& condition) {
        std::vector<std::string> setParts;
        for (const auto& [k, v] : data) {
            setParts.push_back(k + " = '" + v + "'");
        }
        return "UPDATE " + table_name + " SET " + join(setParts, ", ") + " WHERE " + condition + ";";
    }

    std::string delete_(const std::string& condition) {
        return "DELETE FROM " + table_name + " WHERE " + condition + ";";
    }

    std::string selectFemaleUnderAge(int age) {
        return "SELECT * FROM " + table_name + " WHERE age < " + std::to_string(age) + " AND gender = 'female';";
    }

    std::string selectByAgeRange(int minAge, int maxAge) {
        return "SELECT * FROM " + table_name + " WHERE age BETWEEN " + std::to_string(minAge) + " AND " + std::to_string(maxAge) + ";";
    }
};