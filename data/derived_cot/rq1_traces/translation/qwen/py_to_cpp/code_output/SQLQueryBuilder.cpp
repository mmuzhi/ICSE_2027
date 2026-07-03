#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <optional>

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, const std::vector<std::string>& columns = {"*"}, std::optional<std::map<std::string, std::string>> where = std::nullopt) {
        std::stringstream query;
        query << "SELECT ";
        if (columns[0] == "*") {
            query << "*";
        } else {
            for (size_t i = 0; i < columns.size(); i++) {
                if (i > 0) query << ", ";
                query << columns[i];
            }
        }
        query << " FROM " << table;
        if (where) {
            query << " WHERE ";
            for (const auto& [key, value] : *where) {
                if (&key != &(*where.begin()->first)) {
                    query << " AND ";
                }
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }

    static std::string insert(const std::string& table, const std::map<std::string, std::string>& data) {
        std::stringstream query;
        query << "INSERT INTO " << table << " (";
        for (const auto& [key, value] : data) {
            if (&key != &data.begin()->first) {
                query << ", ";
            }
            query << key;
        }
        query << ") VALUES (";
        for (const auto& [key, value] : data) {
            if (&key != &data.begin()->first) {
                query << ", ";
            }
            query << "'" << value << "'";
        }
        query << ")";
        return query.str();
    }

    static std::string delete_(const std::string& table, std::optional<std::map<std::string, std::string>> where = std::nullopt) {
        std::stringstream query;
        query << "DELETE FROM " << table;
        if (where) {
            query << " WHERE ";
            for (const auto& [key, value] : *where) {
                if (&key != &(*where.begin()->first)) {
                    query << " AND ";
                }
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }

    static std::string update(const std::string& table, const std::map<std::string, std::string>& data, std::optional<std::map<std::string, std::string>> where = std::nullopt) {
        std::stringstream query;
        query << "UPDATE " << table << " SET ";
        for (const auto& [key, value] : data) {
            if (&key != &data.begin()->first) {
                query << ", ";
            }
            query << key << "='" << value << "'";
        }
        if (where) {
            query << " WHERE ";
            for (const auto& [key, value] : *where) {
                if (&key != &(*where.begin()->first)) {
                    query << " AND ";
                }
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }
};