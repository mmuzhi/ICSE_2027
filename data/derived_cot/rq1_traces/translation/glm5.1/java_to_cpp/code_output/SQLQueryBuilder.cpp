#ifndef SQL_QUERY_BUILDER_H
#define SQL_QUERY_BUILDER_H

#include <string>
#include <vector>
#include <utility>
#include <regex>

// Preserves insertion order, matching Java's LinkedHashMap behavior
using OrderedMap = std::vector<std::pair<std::string, std::string>>;

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, const char* columns, const OrderedMap* where) {
        std::string cols = (columns != nullptr) ? columns : "*";
        std::vector<std::string> colArray = regexSplit(cols, ",\\s*");
        return select(table, colArray, where);
    }

    static std::string select(const std::string& table, const std::vector<std::string>& columns, const OrderedMap* where) {
        std::string query = "SELECT ";
        if (!columns.empty()) {
            query += join(columns, ", ");
        } else {
            query += "*";
        }
        query += " FROM ";
        query += table;

        if (where != nullptr && !where->empty()) {
            query += " WHERE ";
            bool first = true;
            for (const auto& entry : *where) {
                if (!first) {
                    query += " AND ";
                }
                query += entry.first;
                query += "='";
                query += entry.second;
                query += "'";
                first = false;
            }
        }
        return query;
    }

    static std::string insert(const std::string& table, const OrderedMap& data) {
        std::string query = "INSERT INTO ";
        query += table;
        query += " (";
        std::string values = " VALUES (";

        bool first = true;
        for (const auto& entry : data) {
            if (!first) {
                query += ", ";
                values += ", ";
            }
            query += entry.first;
            values += "'";
            values += entry.second;
            values += "'";
            first = false;
        }

        query += ")";
        values += ")";

        return query + values;
    }

    // Named delete_ because 'delete' is a C++ keyword
    static std::string delete_(const std::string& table, const OrderedMap* where) {
        std::string query = "DELETE FROM ";
        query += table;

        if (where != nullptr && !where->empty()) {
            query += " WHERE ";
            bool first = true;
            for (const auto& entry : *where) {
                if (!first) {
                    query += " AND ";
                }
                query += entry.first;
                query += "='";
                query += entry.second;
                query += "'";
                first = false;
            }
        }
        return query;
    }

    static std::string update(const std::string& table, const OrderedMap& data, const OrderedMap* where) {
        std::string query = "UPDATE ";
        query += table;
        query += " SET ";

        bool first = true;
        for (const auto& entry : data) {
            if (!first) {
                query += ", ";
            }
            query += entry.first;
            query += "='";
            query += entry.second;
            query += "'";
            first = false;
        }

        if (where != nullptr && !where->empty()) {
            query += " WHERE ";
            bool firstWhere = true;
            for (const auto& entry : *where) {
                if (!firstWhere) {
                    query += " AND ";
                }
                query += entry.first;
                query += "='";
                query += entry.second;
                query += "'";
                firstWhere = false;
            }
        }
        return query;
    }

private:
    static std::vector<std::string> regexSplit(const std::string& s, const std::string& pattern) {
        std::vector<std::string> result;
        std::regex re(pattern);
        std::sregex_token_iterator it(s.begin(), s.end(), re, -1);
        std::sregex_token_iterator end;
        for (; it != end; ++it) {
            result.push_back(it->str());
        }
        // Match Java's String.split() behavior: remove trailing empty strings
        while (!result.empty() && result.back().empty()) {
            result.pop_back();
        }
        return result;
    }

    static std::string join(const std::vector<std::string>& v, const std::string& delimiter) {
        std::string result;
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) {
                result += delimiter;
            }
            result += v[i];
        }
        return result;
    }
};

#endif