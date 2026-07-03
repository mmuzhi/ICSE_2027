#include <string>
#include <vector>
#include <map>

class SQLQueryBuilder {
public:
    static std::string select(const std::string& table, 
                              const std::vector<std::string>& columns = {"*"}, 
                              const std::map<std::string, std::string>& where = {}) {
        std::string columns_str;
        if (columns.empty()) {
            columns_str = "*";
        } else {
            for (auto it = columns.begin(); it != columns.end(); ++it) {
                if (it != columns.begin()) {
                    columns_str += ", ";
                }
                columns_str += *it;
            }
        }

        std::string query = "SELECT " + columns_str + " FROM " + table;
        if (!where.empty()) {
            query += " WHERE ";
            for (auto it = where.begin(); it != where.end(); ++it) {
                if (it != where.begin()) {
                    query += " AND ";
                }
                query += it->first + "='" + it->second + "'";
            }
        }
        return query;
    }

    static std::string insert(const std::string& table, 
                              const std::map<std::string, std::string>& data) {
        if (data.empty()) {
            return "INSERT INTO " + table + " () VALUES ()";
        }
        std::string keys;
        std::string values;
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it != data.begin()) {
                keys += ", ";
                values += ", ";
            }
            keys += it->first;
            values += "'" + it->second + "'";
        }
        return "INSERT INTO " + table + " (" + keys + ") VALUES (" + values + ")";
    }

    static std::string delete_(const std::string& table, 
                              const std::map<std::string, std::string>& where = {}) {
        std::string query = "DELETE FROM " + table;
        if (!where.empty()) {
            query += " WHERE ";
            for (auto it = where.begin(); it != where.end(); ++it) {
                if (it != where.begin()) {
                    query += " AND ";
                }
                query += it->first + "='" + it->second + "'";
            }
        }
        return query;
    }

    static std::string update(const std::string& table, 
                              const std::map<std::string, std::string>& data, 
                              const std::map<std::string, std::string>& where = {}) {
        if (data.empty()) {
            return "UPDATE " + table + " SET ";
        }
        std::string update_str;
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it != data.begin()) {
                update_str += ", ";
            }
            update_str += it->first + "='" + it->second + "'";
        }

        std::string query = "UPDATE " + table + " SET " + update_str;
        if (!where.empty()) {
            query += " WHERE ";
            for (auto it = where.begin(); it != where.end(); ++it) {
                if (it != where.begin()) {
                    query += " AND ";
                }
                query += it->first + "='" + it->second + "'";
            }
        }
        return query;
    }
};