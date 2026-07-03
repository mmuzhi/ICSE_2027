#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>

class DatabaseProcessor {
private:
    std::string database_name;

public:
    DatabaseProcessor(const std::string& database_name) : database_name(database_name) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        std::string create_table_query = "CREATE TABLE IF NOT EXISTS " + table_name + " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);

        if (rc) {
            throw std::runtime_error("Cannot open database: " + sqlite3_errmsg(db));
        }

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, create_table_query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare create table statement: " + sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    void insert_into_database(const std::string& table_name, const std::vector<std::map<std::string, std::string>>& data) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);

        if (rc) {
            throw std::runtime_error("Cannot open database: " + sqlite3_errmsg(db));
        }

        std::string insert_query = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, insert_query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare insert statement: " + sqlite3_errmsg(db));
        }

        for (const auto& row : data) {
            if (row.find("name") == row.end() || row.find("age") == row.end()) {
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                throw std::runtime_error("Missing 'name' or 'age' in row");
            }

            sqlite3_bind_text(stmt, 1, row.at("name").c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, row.at("age").c_str(), -1, SQLITE_STATIC);

            rc = sqlite3_step(stmt);

            if (rc != SQLITE_DONE) {
                sqlite3_clear_bindings(stmt);
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                throw std::runtime_error("Failed to insert row: " + sqlite3_errmsg(db));
            }

            sqlite3_clear_bindings(stmt);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::vector<std::vector<std::string>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);

        if (rc) {
            throw std::runtime_error("Cannot open database: " + sqlite3_errmsg(db));
        }

        std::string select_query = "SELECT * FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, select_query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare select statement: " + sqlite3_errmsg(db));
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);

        std::vector<std::vector<std::string>> results;

        if (rc == SQLITE_ROW) {
            int num_columns = sqlite3_column_count(stmt);
            while (rc == SQLITE_ROW) {
                std::vector<std::string> row;
                for (int i = 0; i < num_columns; i++) {
                    const char* column_value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    if (column_value) {
                        row.push_back(column_value);
                    } else {
                        row.push_back("");
                    }
                }
                results.push_back(row);
                rc = sqlite3_step(stmt);
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (results.empty()) {
            return std::vector<std::vector<std::string>>();
        }

        return results;
    }

    void delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);

        if (rc) {
            throw std::runtime_error("Cannot open database: " + sqlite3_errmsg(db));
        }

        std::string delete_query = "DELETE FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, delete_query.c_str(), -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare delete statement: " + sqlite3_errmsg(db));
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);

        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Failed to delete rows: " + sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};