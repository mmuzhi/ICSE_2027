#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

// Trim leading and trailing whitespace
static std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace(static_cast<unsigned char>(*start))) {
        ++start;
    }
    auto end = s.end();
    while (end != start && std::isspace(static_cast<unsigned char>(*(end-1)))) {
        --end;
    }
    return std::string(start, end);
}

// Split by comma, then trim each token
static std::vector<std::string> splitColumns(const std::string& s) {
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    // If the input was empty, getline still produces one empty token.
    // In Java, "".split(",\\s*") returns [""], which is a single empty column.
    // We keep that behavior: if string is empty, result is one empty string.
    // But if the string was *, we handle it before splitting.
    return tokens;
}

// Join strings with ", "
static std::string join(const std::vector<std::string>& parts) {
    if (parts.empty()) return "";
    std::string result = parts[0];
    for (size_t i = 1; i < parts.size(); ++i) {
        result += ", " + parts[i];
    }
    return result;
}

class SQLQueryBuilder {
public:
    // Overload: columns as string (can be null)
    static std::string select(
        const std::string& table,
        const char* columns,  // nullptr means *
        const std::vector<std::pair<std::string, std::string>>& where
    ) {
        std::string cols;
        if (columns == nullptr) {
            cols = "*";
        } else {
            cols = columns;
        }
        // Split columns string and call the array overload
        return select(table, splitColumns(cols), where);
    }

    // Overload: columns as array of strings
    static std::string select(
        const std::string& table,
        const std::vector<std::string>& columns,
        const std::vector<std::pair<std::string, std::string>>& where
    ) {
        std::string query = "SELECT ";
        if (!columns.empty()) {
            query += join(columns);
        } else {
            query += "*";
        }
        query += " FROM " + table;

        if (!where.empty()) {
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

    static std::string insert(
        const std::string& table,
        const std::vector<std::pair<std::string, std::string>>& data
    ) {
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
        values += ")";

        return query + values;
    }

    static std::string del(
        const std::string& table,
        const std::vector<std::pair<std::string, std::string>>& where
    ) {
        std::string query = "DELETE FROM " + table;

        if (!where.empty()) {
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

    static std::string update(
        const std::string& table,
        const std::vector<std::pair<std::string, std::string>>& data,
        const std::vector<std::pair<std::string, std::string>>& where
    ) {
        std::string query = "UPDATE " + table + " SET ";

        bool first = true;
        for (const auto& entry : data) {
            if (!first) {
                query += ", ";
            }
            query += entry.first + "='" + entry.second + "'";
            first = false;
        }

        if (!where.empty()) {
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