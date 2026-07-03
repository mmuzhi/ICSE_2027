#include <string>
#include <map>
#include <vector>
#include <stdexcept>

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, const std::map<std::string, std::string>& columns = {"*": "*"}, const std::map<std::string, std::string>* where = nullptr) {
        std::string columns_str = columns.size() == 1 && columns.begin()->first == "*" ? "*" : 
            std::format("{}", [&]() {
                std::vector<std::string> parts;
                for (const auto& [k, v] : columns) {
                    if (k == "*") continue; // Skip '*' if present
                    parts.push_back(k);
                }
                return std::format("{}.{}", parts.join(","), *columns.begin().second == "*" ? "*" : parts[0]);
            }());

        std::string query = std::format("SELECT {} FROM {}", columns_str, table);
        if (where) {
            std::vector<std::string> conditions;
            for (const auto& [k, v] : *where) {
                conditions.push_back(std::format("{}.='{}'", k, v));
            }
            query += " WHERE " + conditions.join(" AND ");
        }
        return query;
    }

    static std::string insert(const std::string& table, const std::map<std::string, std::string>& data) {
        std::vector<std::string> keys;
        std::vector<std::string> values;
        for (const auto& [k, v] : data) {
            keys.push_back(k);
            values.push_back(std::format("{}.='{}'", k, v));
        }
        return std::format("INSERT INTO {} ({}. {}) VALUES ({}. {})", table, keys.join(","), values.join(","));
    }

    static std::string delete_(const std::string& table, const std::map<std::string, std::string>* where = nullptr) {
        std::string query = std::format("DELETE FROM {}", table);
        if (where) {
            std::vector<std::string> conditions;
            for (const auto& [k, v] : *where) {
                conditions.push_back(std::format("{}.='{}'", k, v));
            }
            query += " WHERE " + conditions.join(" AND ");
        }
        return query;
    }

    static std::string update(const std::string& table, const std::map<std::string, std::string>& data, const std::map<std::string, std::string>* where = nullptr) {
        std::vector<std::string> updates;
        for (const auto& [k, v] : data) {
            updates.push_back(std::format("{}.='{}'", k, v));
        }
        std::string query = std::format("UPDATE {} SET {}", table, updates.join(","));
        if (where) {
            std::vector<std::string> conditions;
            for (const auto& [k, v] : *where) {
                conditions.push_back(std::format("{}.='{}'", k, v));
            }
            query += " WHERE " + conditions.join(" AND ");
        }
        return query;
    }
};