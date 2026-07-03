#include <string>
#include <vector>
#include <optional>
#include <utility>

class SQLGenerator {
private:
    std::string table_name;

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::optional<std::vector<std::string>>& fields = std::nullopt, 
                       const std::optional<std::string>& condition = std::nullopt) {
        std::string fields_str = "*";
        if (fields.has_value()) {
            fields_str = "";
            const auto& f = fields.value();
            for (size_t i = 0; i < f.size(); ++i) {
                if (i > 0) {
                    fields_str += ", ";
                }
                fields_str += f[i];
            }
        }
        
        std::string sql = "SELECT " + fields_str + " FROM " + table_name;
        if (condition.has_value()) {
            sql += " WHERE " + condition.value();
        }
        return sql + ";";
    }

    std::string insert(const std::vector<std::pair<std::string, std::string>>& data) {
        std::string fields = "";
        std::string values = "";
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) {
                fields += ", ";
                values += ", ";
            }
            fields += data[i].first;
            values += "'" + data[i].second + "'";
        }
        std::string sql = "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + values + ")";
        return sql + ";";
    }

    std::string update(const std::vector<std::pair<std::string, std::string>>& data, 
                       const std::string& condition) {
        std::string set_clause = "";
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) {
                set_clause += ", ";
            }
            set_clause += data[i].first + " = '" + data[i].second + "'";
        }
        std::string sql = "UPDATE " + table_name + " SET " + set_clause + " WHERE " + condition;
        return sql + ";";
    }

    // Note: 'delete' is a reserved keyword in C++, so 'delete_' is used instead.
    std::string delete_(const std::string& condition) {
        std::string sql = "DELETE FROM " + table_name + " WHERE " + condition;
        return sql + ";";
    }

    std::string select_female_under_age(int age) {
        std::string condition = "age < " + std::to_string(age) + " AND gender = 'female'";
        return select(std::nullopt, condition);
    }

    std::string select_by_age_range(int min_age, int max_age) {
        std::string condition = "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age);
        return select(std::nullopt, condition);
    }
};