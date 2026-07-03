#include <string>
#include <map>

class SQLGenerator {
private:
    std::string table_name;

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(std::map<std::string, std::string> fields = {}, std::string condition = "") {
        if (fields.empty()) {
            return "SELECT * FROM " + table_name + (condition.empty() ? ";" : " WHERE " + condition + ";");
        }

        std::string fields_str;
        for (const auto& kv : fields) {
            if (!fields_str.empty()) {
                fields_str += ", ";
            }
            fields_str += kv.first;
        }

        std::string sql = "SELECT " + fields_str + " FROM " + table_name;
        if (!condition.empty()) {
            sql += " WHERE " + condition;
        }
        sql += ';';
        return sql;
    }

    std::string insert(std::map<std::string, std::string> data) {
        if (data.empty()) {
            return "INSERT INTO " + table_name + "() VALUES();";
        }

        std::string fields;
        std::string values;

        for (const auto& kv : data) {
            if (!fields.empty()) {
                fields += ", ";
                values += ", ";
            }
            fields += kv.first;
            values += '\'' + kv.second + '\'';
        }

        return "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + values + ");";
    }

    std::string update(std::map<std::string, std::string> data, const std::string& condition) {
        if (data.empty()) {
            return "UPDATE " + table_name + " SET () WHERE " + condition + ';';
        }

        std::string set_clause;
        for (const auto& kv : data) {
            if (!set_clause.empty()) {
                set_clause += ", ";
            }
            set_clause += kv.first + " = '";
            set_clause += kv.second;
            set_clause += '\'';
        }

        return "UPDATE " + table_name + " SET " + set_clause + " WHERE " + condition + ';';
    }

    std::string delete_query(const std::string& condition) {
        return "DELETE FROM " + table_name + (condition.empty() ? ';' : " WHERE " + condition + ';');
    }

    std::string select_female_under_age(int age) {
        return select({}, "age < " + std::to_string(age) + " AND gender = 'female'");
    }

    std::string select_by_age_range(int min_age, int max_age) {
        return select({}, "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age));
    }
};