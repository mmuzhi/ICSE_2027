#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace org {
    namespace example {

        class SQLQueryBuilder {

        public:
            static std::string select(const std::string& table, const std::optional<std::string>& columns, const std::map<std::string, std::string>& where) {
                std::vector<std::string> columnsList;
                if (!columns) {
                    columnsList = {"*"};
                } else {
                    columnsList = {columns.value()};
                }
                return select(table, columnsList, where);
            }

            static std::string select(const std::string& table, const std::vector<std::string>& columns, const std::map<std::string, std::string>& where) {
                std::string query = "SELECT ";
                if (!columns.empty()) {
                    for (size_t i = 0; i < columns.size(); ++i) {
                        query += columns[i];
                        if (i < columns.size() - 1) {
                            query += ", ";
                        }
                    }
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
                values += ")";

                return query + values;
            }

            static std::string delete_(const std::string& table, const std::map<std::string, std::string>& where) {
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

        private:
            SQLQueryBuilder() = default; // Prevent instantiation
        };

    } // namespace example
} // namespace org

// For std::optional if not available in C++17 or earlier
#ifndef __cpp_lib_optional
    // Dummy implementation of std::optional for demonstration purposes
    // In practice, ensure C++17 or use boost::optional
    namespace std {
        template <typename T>
        class optional {
        private:
            bool m_has_value;
            T m_value;

        public:
            optional() : m_has_value(false) {}
            optional(const T& value) : m_has_value(true), m_value(value) {}
            ~optional() = default;

            bool has_value() const { return m_has_value; }
            const T& value() const {
                if (!m_has_value) {
                    throw std::runtime_error("value not available");
                }
                return m_value;
            }
        };
    }
#endif