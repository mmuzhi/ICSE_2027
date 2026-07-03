#pragma once

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <regex>

using Map = std::vector<std::pair<std::string, std::string>>;

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, const char* columns, const Map* where) {
        std::string cols = (columns == nullptr) ? std::string("*") : std::string(columns);
        std::regex re(",\\s*");
        std::sregex_token_iterator it(cols.begin(), cols.end(), re, -1);
        std::sregex_token_iterator end;
        std::vector<std::string> colVec(it, end);
        return select(table, colVec, where);
    }

    static std::string select(const std::string& table, const std::vector<std::string>& columns, const Map* where) {
        std::ostringstream query;
        query << "SELECT ";
        if (!columns.empty()) {
            for (size_t i = 0; i < columns.size(); ++i) {
                if (i > 0) query << ", ";
                query << columns[i];
            }
        } else {
            query << "*";
        }
        query << " FROM " << table;

        if (where != nullptr && !where->empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& entry : *where) {
                if (!first) {
                    query << " AND ";
                }
                query << entry.first << "='" << entry.second << "'";
                first = false;
            }
        }
        return query.str();
    }

    static std::string insert(const std::string& table, const Map& data) {
        std::ostringstream query;
        std::ostringstream values;
        query << "INSERT INTO " << table << " (";
        values << " VALUES (";

        bool first = true;
        for (const auto& entry : data) {
            if (!first) {
                query << ", ";
                values << ", ";
            }
            query << entry.first;
            values << "'" << entry.second << "'";
            first = false;
        }

        query << ")";
        values << ")";

        return query.str() + values.str();
    }

    static std::string deleteFrom(const std::string& table, const Map* where) {
        std::ostringstream query;
        query << "DELETE FROM " << table;

        if (where != nullptr && !where->empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& entry : *where) {
                if (!first) {
                    query << " AND ";
                }
                query << entry.first << "='" << entry.second << "'";
                first = false;
            }
        }
        return query.str();
    }

    static std::string update(const std::string& table, const Map& data, const Map* where) {
        std::ostringstream query;
        query << "UPDATE " << table << " SET ";

        bool first = true;
        for (const auto& entry : data) {
            if (!first) {
                query << ", ";
            }
            query << entry.first << "='" << entry.second << "'";
            first = false;
        }

        if (where != nullptr && !where->empty()) {
            query << " WHERE ";
            bool firstWhere = true;
            for (const auto& entry : *where) {
                if (!firstWhere) {
                    query << " AND ";
                }
                query << entry.first << "='" << entry.second << "'";
                firstWhere = false;
            }
        }
        return query.str();
    }
};