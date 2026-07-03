#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <optional>
#include <stdexcept>
#include <iostream>
#include <cstring>

class DatabaseProcessor {
private:
    std::string database_name;

public:
    DatabaseProcessor(const std::string& database_name) : database_name(database_name) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        std::string query = "CREATE TABLE IF NOT EXISTS " + table_name +
                            " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        char* errmsg = nullptr;
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            std::string err = errmsg;
            sqlite3_free(errmsg);
            sqlite3_close(db);
            throw std::runtime_error("Failed to create table: " + err);
        }

        sqlite3_close(db);
    }

    void insert_into_database(const std::string& table_name, const std::vector<std::pair<std::string, int>>& data) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        std::string insert_sql = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, insert_sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare insert statement: " + err);
        }

        for (const auto& row : data) {
            sqlite3_bind_text(stmt, 1, row.first.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, row.second);

            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                std::string err = sqlite3_errmsg(db);
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                throw std::runtime_error("Failed to insert data: " + err);
            }

            sqlite3_reset(stmt);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::optional<std::vector<std::tuple<int, std::string, int>>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        std::string select_sql = "SELECT * FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, select_sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare select statement: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int>> results;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* text = sqlite3_column_text(stmt, 1);
            std::string name_str(reinterpret_cast<const char*>(text));
            int age = sqlite3_column_int(stmt, 2);
            results.emplace_back(id, name_str, age);
        }

        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Failed to search database: " + err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (results.empty()) {
            return std::nullopt;
        }
        return results;
    }

    void delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        std::string delete_sql = "DELETE FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, delete_sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare delete statement: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Failed to delete data: " + err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};