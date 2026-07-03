#include <string>
#include <vector>
#include <utility>
#include <sstream>

class SQLGenerator {
private:
    std::string table_name;

    static std::string join(const std::vector<std::string>& tokens, const std::string& delimiter) {
        if (tokens.empty()) {
            return "";
        }
        std::string s = tokens[0];
        for (size_t i = 1; i < tokens.size(); ++i) {
            s += delimiter + tokens[i];
        }
        return s;
    }

    std::string build_select(const std::string& fields_str, const std::string& condition) const {
        std::string sql = "SELECT " + fields_str + " FROM " + table_name;
        if (!condition.empty()) {
            sql += " WHERE " + condition;
        }
        sql += ";";
        return sql;
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select() const {
        return build_select("*", "");
    }

    std::string select(const std::string& condition) const {
        return build_select("*", condition);
    }

    std::string select(const std::vector<std::string>& fields) const {
        std::string fields_str = join(fields, ", ");
        return build_select(fields_str, "");
    }

    std::string select(const std::vector<std::string>& fields, const std::string& condition) const {
        std::string fields_str = join(fields, ", ");
        return build_select(fields_str, condition);
    }

    std::string insert(const std::vector<std::pair<std::string, std::string>>& data) const {
        std::vector<std::string> fieldNames;
        std::vector<std::string> valuesQuoted;
        for (const auto& kv : data) {
            fieldNames.push_back(kv.first);
            valuesQuoted.push_back("'" + kv.second + "'");
        }
        std::string fields = join(fieldNames, ", ");
        std::string values = join(valuesQuoted, ", ");
        return "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + values + ");";
    }

    std::string update(const std::vector<std::pair<std::string, std::string>>& data, const std::string& condition) const {
        std::vector<std::string> setClauses;
        for (const auto& kv : data) {
            setClauses.push_back(kv.first + " = '" + kv.second + "'");
        }
        std::string set_clause = join(setClauses, ", ");
        return "UPDATE " + table_name + " SET " + set_clause + " WHERE " + condition + ";";
    }

    std::string delete_query(const std::string& condition) const {
        return "DELETE FROM " + table_name + " WHERE " + condition + ";";
    }

    std::string select_female_under_age(int age) const {
        std::string condition = "age < " + std::to_string(age) + " AND gender = 'female'";
        return select(condition);
    }

    std::string select_by_age_range(int min_age, int max_age) const {
        std::string condition = "age BETWEEN " + std::to_string(min_age) + " AND " + std::to_string(max_age);
        return select(condition);
    }
};