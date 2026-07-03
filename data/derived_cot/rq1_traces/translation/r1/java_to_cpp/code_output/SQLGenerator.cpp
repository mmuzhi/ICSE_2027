#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <stdexcept>
#include <exception>

class NullPointerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "NullPointerException";
    }
};

class SQLGenerator {
private:
    std::string table_name;

    static std::string joinVector(const std::vector<std::string>& vec, const std::string& delimiter = ", ") {
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i != 0) {
                oss << delimiter;
            }
            oss << vec[i];
        }
        return oss.str();
    }

public:
    SQLGenerator(const std::string& table_name) : table_name(table_name) {}

    std::string select(const std::vector<std::string>* fields, const std::string* condition) {
        std::string fieldsStr;
        if (fields) {
            fieldsStr = joinVector(*fields);
        } else {
            fieldsStr = "*";
        }

        std::string sql = "SELECT " + fieldsStr + " FROM " + table_name;
        if (condition) {
            sql += " WHERE " + *condition;
        }
        sql += ";";
        return sql;
    }

    template <typename Map>
    std::string insert(const Map& data) {
        std::map<std::string, std::string> sortedData(data.begin(), data.end());
        std::vector<std::string> keys;
        for (const auto& pair : sortedData) {
            keys.push_back(pair.first);
        }
        std::string fields = joinVector(keys);

        std::vector<std::string> values;
        for (const auto& pair : sortedData) {
            values.push_back("'" + pair.second + "'");
        }
        std::string valuesStr = joinVector(values);

        return "INSERT INTO " + table_name + " (" + fields + ") VALUES (" + valuesStr + ");";
    }

    template <typename Map>
    std::string update(const Map& data, const std::string* condition) {
        if (condition == nullptr) {
            throw NullPointerException();
        }
        std::map<std::string, std::string> sortedData(data.begin(), data.end());
        std::vector<std::string> assignments;
        for (const auto& pair : sortedData) {
            assignments.push_back(pair.first + " = '" + pair.second + "'");
        }
        std::string setClause = joinVector(assignments);

        return "UPDATE " + table_name + " SET " + setClause + " WHERE " + *condition + ";";
    }

    std::string delete_(const std::string* condition) {
        if (condition == nullptr) {
            throw NullPointerException();
        }
        return "DELETE FROM " + table_name + " WHERE " + *condition + ";";
    }

    std::string selectFemaleUnderAge(int age) {
        return "SELECT * FROM " + table_name + " WHERE age < " + std::to_string(age) + " AND gender = 'female';";
    }

    std::string selectByAgeRange(int minAge, int maxAge) {
        return "SELECT * FROM " + table_name + " WHERE age BETWEEN " + std::to_string(minAge) + " AND " + std::to_string(maxAge) + ";";
    }
};