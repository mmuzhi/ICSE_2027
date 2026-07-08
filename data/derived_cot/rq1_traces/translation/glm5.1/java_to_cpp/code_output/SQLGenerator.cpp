#pragma once

#include <map>
#include <string>
#include <vector>

class SQLGenerator {
private:
    const std::string table_name;

    static std::string join(const std::vector<std::string>& v, const std::string& delimiter) {
        std::string result;
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) result += delimiter;
            result += v[i];
        }
        return result;
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::vector<std::string>* fields, const std::string* condition) {
        std::string fieldsStr = (fields == nullptr) ? "*" : join(*fields, ", ");
        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (condition != nullptr) {
            sql += " WHERE " + *condition;
        }
        return sql + ";";
    }

    std::string insert(const std::map<std::string, std::string>& data) {
        // std::map is already sorted by key, matching Java's TreeMap behavior
        std::string fieldsStr;
        std::string valuesStr;
        bool first = true;
        for (const auto& pair : data) {
            if (!first) {
                fieldsStr += ", ";
                valuesStr += ", ";
            }
            fieldsStr += pair.first;
            valuesStr += "'" + pair.second + "'";
            first = false;
        }
        return "INSERT INTO " + table_name + " (" + fieldsStr + ") VALUES (" + valuesStr + ");";
    }

    std::string update(const std::map<std::string, std::string>& data, const std::string& condition) {
        std::string setClause;
        bool first = true;
        for (const auto& pair : data) {
            if (!first) {
                setClause += ", ";
            }
            setClause += pair.first + " = '" + pair.second + "'";
            first = false;
        }
        return "UPDATE " + table_name + " SET " + setClause + " WHERE " + condition + ";";
    }

    // Named delete_ because 'delete' is a C++ keyword
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