#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

class SQLQueryBuilder {
public:
    // Overload for columns as a list (vector)
    static std::string select(const std::string& table,
                              const std::vector<std::string>& columns,
                              const std::map<std::string, std::string>& where = {}) {
        std::ostringstream query;
        query << "SELECT ";
        if (columns.empty()) {
            query << "*";
        } else {
            for (size_t i = 0; i < columns.size(); ++i) {
                if (i > 0) query << ", ";
                query << columns[i];
            }
        }
        query << " FROM " << table;
        if (!where.empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& [key, value] : where) {
                if (!first) query << " AND ";
                first = false;
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }

    // Overload for columns as a string (e.g., "*")
    static std::string select(const std::string& table,
                              const std::string& columns = "*",
                              const std::map<std::string, std::string>& where = {}) {
        std::ostringstream query;
        query << "SELECT " << columns << " FROM " << table;
        if (!where.empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& [key, value] : where) {
                if (!first) query << " AND ";
                first = false;
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }

    static std::string insert(const std::string& table,
                              const std::map<std::string, std::string>& data) {
        std::ostringstream query;
        query << "INSERT INTO " << table << " (";
        std::string keys, values;
        for (const auto& [key, value] : data) {
            if (!keys.empty()) {
                keys += ", ";
                values += ", ";
            }
            keys += key;
            values += "'" + value + "'";
        }
        query << keys << ") VALUES (" << values << ")";
        return query.str();
    }

    static std::string delete_query(const std::string& table,
                                    const std::map<std::string, std::string>& where = {}) {
        std::ostringstream query;
        query << "DELETE FROM " << table;
        if (!where.empty()) {
            query << " WHERE ";
            bool first = true;
            for (const auto& [key, value] : where) {
                if (!first) query << " AND ";
                first = false;
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }

    static std::string update(const std::string& table,
                              const std::map<std::string, std::string>& data,
                              const std::map<std::string, std::string>& where = {}) {
        std::ostringstream query;
        query << "UPDATE " << table << " SET ";
        bool first = true;
        for (const auto& [key, value] : data) {
            if (!first) query << ", ";
            first = false;
            query << key << "='" << value << "'";
        }
        if (!where.empty()) {
            query << " WHERE ";
            first = true;
            for (const auto& [key, value] : where) {
                if (!first) query << " AND ";
                first = false;
                query << key << "='" << value << "'";
            }
        }
        return query.str();
    }
};