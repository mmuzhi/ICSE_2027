#include <vector>
#include <string>
#include <map>
#include <optional>

class SQLGenerator {
private:
    std::string table_name;

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    // select
    std::string select(const std::optional<std::vector<std::string>>& fields = std::nullopt, const std::optional<std::string>& condition = std::nullopt) {
        std::string field_string;
        if (fields) {
            if (!fields->empty()) {
                for (size_t i = 0; i < fields->size(); i++) {
                    if (i > 0) {
                        field_string += ", ";
                    }
                    field_string += (*fields)[i];
                }
            }
        } else {
            field_string = "*";
        }

        std::string sql = "SELECT " + field_string + " FROM " + table_name;

        if (condition) {
            sql += " WHERE " + *condition;
        }

        sql += ";";
        return sql;
    }

    // insert
    std::string insert(const std::map<std::string, std::string>& data) {
        std::string field_list;
        std::string value_list;

        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it != data.begin()) {
                field_list += ", ";
                value_list += ", ";
            }
            field_list += it->first;
            value_list += "'" + it->second + "'";
        }

        std::string sql = "INSERT INTO " + table_name + " (" + field_list + ") VALUES (" + value_list + ");";
        return sql;
    }

    // update
    std::string update(const std::map<std::string, std::string>& data, const std::optional<std::string>& condition) {
        std::string set_clause;
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it != data.begin()) {
                set_clause += ", ";
            }
            set_clause += it->first + " = '" + it->second + "'";
        }

        std::string sql = "UPDATE " + table_name + " SET " + set_clause;
        if (condition) {
            sql += " WHERE " + *condition;
        }
        sql += ";";
        return sql;
    }

    // delete (to avoid keyword)
    std::string delete_(const std::optional<std::string>& condition) {
        std::string sql = "DELETE FROM " + table_name;
        if (condition) {
            sql += " WHERE " + *condition;
        }
        sql += ";";
        return sql;
    }

    // helper methods
    std::string select_female_under_age(int age) {
        std::string condition = "age < " + std::to_string(age) + " AND gender = 'female'";
        return select(std::nullopt, condition);
    }

    std::string select_by_age_range(int min_age, int max_age) {
        std::string condition = "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age);
        return select(std::nullopt, condition);
    }
};