#include <string>
#include <vector>
#include <sstream>
#include <utility>

class SQLGenerator {
public:
    std::string table_name;

    SQLGenerator(std::string table_name) : table_name(std::move(table_name)) {}

    std::string select(std::vector<std::string> fields = {}, std::string condition = "") {
        std::string fields_str = "*";
        if (!fields.empty()) {
            std::ostringstream oss;
            for (size_t i = 0; i < fields.size(); ++i) {
                if (i > 0) oss << ", ";
                oss << fields[i];
            }
            fields_str = oss.str();
        }
        std::string sql = "SELECT " + fields_str + " FROM " + table_name;
        if (!condition.empty()) {
            sql += " WHERE " + condition;
        }
        return sql + ";";
    }

    std::string insert(std::vector<std::pair<std::string, std::string>> data) {
        std::ostringstream fields_oss, values_oss;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) {
                fields_oss << ", ";
                values_oss << ", ";
            }
            fields_oss << data[i].first;
            values_oss << "'" << data[i].second << "'";
        }
        std::string sql = "INSERT INTO " + table_name + " (" + fields_oss.str() + ") VALUES (" + values_oss.str() + ")";
        return sql + ";";
    }

    std::string update(std::vector<std::pair<std::string, std::string>> data, std::string condition) {
        std::ostringstream set_oss;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) set_oss << ", ";
            set_oss << data[i].first << " = '" << data[i].second << "'";
        }
        std::string sql = "UPDATE " + table_name + " SET " + set_oss.str() + " WHERE " + condition;
        return sql + ";";
    }

    std::string delete_(std::string condition) {
        std::string sql = "DELETE FROM " + table_name + " WHERE " + condition;
        return sql + ";";
    }

    std::string select_female_under_age(int age) {
        std::string condition = "age < " + std::to_string(age) + " AND gender = 'female'";
        return select({}, condition);
    }

    std::string select_by_age_range(int min_age, int max_age) {
        std::string condition = "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age);
        return select({}, condition);
    }
};