#include <string>
#include <vector>
#include <utility>

class SQLQueryBuilder {
public:
    using Dict = std::vector<std::pair<std::string, std::string>>;

    static std::string select(const std::string& table, const std::vector<std::string>& columns = {"*"}, const Dict& where = {}) {
        std::string cols_str;
        for (size_t i = 0; i < columns.size(); ++i) {
            if (i > 0) cols_str += ", ";
            cols_str += columns[i];
        }
        std::string query = "SELECT " + cols_str + " FROM " + table;
        if (!where.empty()) {
            query += " WHERE ";
            for (size_t i = 0; i < where.size(); ++i) {
                if (i > 0) query += " AND ";
                query += where[i].first + "='" + where[i].second + "'";
            }
        }
        return query;
    }

    static std::string insert(const std::string& table, const Dict& data) {
        std::string keys, values;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) {
                keys += ", ";
                values += ", ";
            }
            keys += data[i].first;
            values += "'" + data[i].second + "'";
        }
        return "INSERT INTO " + table + " (" + keys + ") VALUES (" + values + ")";
    }

    static std::string delete_(const std::string& table, const Dict& where = {}) {
        std::string query = "DELETE FROM " + table;
        if (!where.empty()) {
            query += " WHERE ";
            for (size_t i = 0; i < where.size(); ++i) {
                if (i > 0) query += " AND ";
                query += where[i].first + "='" + where[i].second + "'";
            }
        }
        return query;
    }

    static std::string update(const std::string& table, const Dict& data, const Dict& where = {}) {
        std::string update_str;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i > 0) update_str += ", ";
            update_str += data[i].first + "='" + data[i].second + "'";
        }
        std::string query = "UPDATE " + table + " SET " + update_str;
        if (!where.empty()) {
            query += " WHERE ";
            for (size_t i = 0; i < where.size(); ++i) {
                if (i > 0) query += " AND ";
                query += where[i].first + "='" + where[i].second + "'";
            }
        }
        return query;
    }
};