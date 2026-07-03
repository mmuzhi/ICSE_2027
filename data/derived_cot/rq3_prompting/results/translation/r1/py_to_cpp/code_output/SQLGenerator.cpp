#include <string>
#include <vector>
#include <sstream>
#include <utility>

class SQLGenerator {
public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    // SELECT: if fields is empty, use "*"; if condition is empty, no WHERE clause.
    std::string select(const std::vector<std::string>& fields = {},
                       const std::string& condition = "") const {
        std::string fields_str;
        if (fields.empty()) {
            fields_str = "*";
        } else {
            std::ostringstream oss;
            for (size_t i = 0; i < fields.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << fields[i];
            }
            fields_str = oss.str();
        }

        std::ostringstream sql;
        sql << "SELECT " << fields_str << " FROM " << table_name;
        if (!condition.empty()) {
            sql << " WHERE " << condition;
        }
        sql << ";";
        return sql.str();
    }

    // INSERT: data is a vector of (field_name, value) pairs preserving order.
    std::string insert(const std::vector<std::pair<std::string, std::string>>& data) const {
        std::ostringstream fields, values;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) {
                fields << ", ";
                values << ", ";
            }
            fields << data[i].first;
            values << "'" << data[i].second << "'";
        }

        std::ostringstream sql;
        sql << "INSERT INTO " << table_name << " (" << fields.str()
            << ") VALUES (" << values.str() << ");";
        return sql.str();
    }

    // UPDATE: data as vector of pairs; condition is required.
    std::string update(const std::vector<std::pair<std::string, std::string>>& data,
                       const std::string& condition) const {
        std::ostringstream set_clause;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) set_clause << ", ";
            set_clause << data[i].first << " = '" << data[i].second << "'";
        }

        std::ostringstream sql;
        sql << "UPDATE " << table_name << " SET " << set_clause.str()
            << " WHERE " << condition << ";";
        return sql.str();
    }

    // DELETE: method name changed from "delete" because it is a C++ keyword.
    std::string delete_record(const std::string& condition) const {
        std::ostringstream sql;
        sql << "DELETE FROM " << table_name << " WHERE " << condition << ";";
        return sql.str();
    }

    // Query by age and gender.
    std::string select_female_under_age(int age) const {
        std::string condition = "age < " + std::to_string(age) + " AND gender = 'female'";
        return select({}, condition);
    }

    // Query by age range.
    std::string select_by_age_range(int min_age, int max_age) const {
        std::string condition = "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age);
        return select({}, condition);
    }

private:
    std::string table_name;
};