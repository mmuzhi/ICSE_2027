#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <regex>

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, const std::string& columns, const std::map<std::string, std::string>& where) {
        if (columns.empty()) {
            return select(table, std::vector<std::string>(), where);
        } else {
            std::vector<std::string> parts;
            std::regex re(",\\s*");
            std::sregex_token_iterator it(columns.begin(), columns.end(), re, -1);
            std::string token;
            while ((token = *it++)) {
                parts.push_back(token);
            }
            return select(table, parts, where);
        }
    }

    static std::string select(const std::string& table, const std::vector<std::string>& columns, const std::map<std::string, std::string>& where) {
        std::string query = "SELECT ";
        if (!columns.empty()) {
            for (size_t i = 0; i < columns.size(); ++i) {
                if (i != 0) {
                    query += ", ";
                }
                query += columns[i];
            }
        } else {
            query += "*";
        }
        query += " FROM " + table;

        if (where.size() > 0) {
            query += " WHERE ";
            bool first = true;
            for (const auto& entry : where) {
                if (!first) {
                    query += " AND ";
                }
                query += entry.first + "='" + entry.second + "'";
                first = false;
            }
        }
        return query;
    }

    static std::string insert(const std::string& table, const std::map<std::string, std::string>& data) {
        std::string query = "INSERT INTO " + table + " (";
        std::string values = " VALUES (";
        bool first = true;

        for (const auto& entry : data) {
            if (!first) {
                query += ", ";
                values += ", ";
            }
            query += entry.first;
            values += "'" + entry.second + "'";
            first = false;
        }

        query += ")";
        query += values + ")";
        return query;
    }

    static std::string delete_(const std::string& table, const std::map<std::string, std::string>& where) {
        std::string query = "DELETE FROM " + table;

        if (where.size() > 0) {
            query += " WHERE ";
            bool first = true;
            for (const auto& entry : where) {
                if (!first) {
                    query += " AND ";
                }
                query += entry.first + "='" + entry.second + "'";
                first = false;
            }
        }
        return query;
    }

    static std::string update(const std::string& table, const std::map<std::string, std::string>& data, const std::map<std::string, std::string>& where) {
        std::string query = "UPDATE " + table + " SET ";
        bool first = true;

        for (const auto& entry : data) {
            if (!first) {
                query += ", ";
            }
            query += entry.first + "='" + entry.second + "'";
            first = false;
        }

        if (where.size() > 0) {
            query += " WHERE ";
            bool firstWhere = true;
            for (const auto& entry : where) {
                if (!firstWhere) {
                    query += " AND ";
                }
                query += entry.first + "='" + entry.second + "'";
                firstWhere = false;
            }
        }
        return query;
    }
};