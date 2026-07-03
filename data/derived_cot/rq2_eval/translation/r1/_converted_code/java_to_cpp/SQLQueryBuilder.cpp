#ifndef SQL_QUERY_BUILDER_H
#define SQL_QUERY_BUILDER_H

#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <regex>
#include <iterator>

namespace SQLQueryBuilder {

    namespace {
        inline std::vector<std::string> split_columns(const std::string& s) {
            if (s.empty()) {
                return {};
            }
            std::regex re(",\\s*");
            std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
            std::sregex_token_iterator end;
            std::vector<std::string> tokens;
            while (it != end) {
                tokens.push_back(*it);
                ++it;
            }
            while (!tokens.empty() && tokens.back().empty()) {
                tokens.pop_back();
            }
            return tokens;
        }
    }

    inline std::string select(const std::string& table, const std::vector<std::string>& columns, const std::vector<std::pair<std::string, std::string>>* where = nullptr) {
        std::ostringstream query;
        query << "SELECT ";
        if (columns.empty()) {
            query << "*";
        } else {
            for (size_t i = 0; i < columns.size(); ++i) {
                if (i > 0) {
                    query << ", ";
                }
                query << columns[i];
            }
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

    inline std::string select(const std::string& table, const std::string* columns, const std::vector<std::pair<std::string, std::string>>* where = nullptr) {
        if (columns == nullptr) {
            return select(table, std::vector<std::string>{"*"}, where);
        } else {
            std::vector<std::string> parts = split_columns(*columns);
            return select(table, parts, where);
        }
    }

    inline std::string insert(const std::string& table, const std::vector<std::pair<std::string, std::string>>& data) {
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

    inline std::string deleteQuery(const std::string& table, const std::vector<std::pair<std::string, std::string>>* where = nullptr) {
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

    inline std::string update(const std::string& table, const std::vector<std::pair<std::string, std::string>>& data, const std::vector<std::pair<std::string, std::string>>* where = nullptr) {
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

}

#endif