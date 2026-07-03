#include <sqlite3.h>
#include <vector>
#include <tuple>
#include <string>
#include <memory>
#include <optional>
#include <stdexcept>

struct Person {
    std::string name;
    int age;
};

class DatabaseProcessor {
private:
    std::string database_name;

    void throw_sqlite_error(sqlite3* db, const std::string& message) {
        std::string error_msg = message + ": " + sqlite3_errmsg(db);
        sqlite3_close(db);
        throw std::runtime_error(error_msg);
    }

public:
    explicit DatabaseProcessor(const std::string& db_name) : database_name(db_name) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        sqlite3* db;
        if (sqlite3_open(database_name.c_str(), &db) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to open database");
        }

        std::string sql = "CREATE TABLE IF NOT EXISTS " + table_name + 
                          " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";

        char* err_msg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK) {
            std::string error = "SQL error: " + std::string(err_msg);
            sqlite3_free(err_msg);
            throw_sqlite_error(db, error);
        }

        sqlite3_close(db);
    }

    void insert_into_database(const std::string& table_name, const std::vector<Person>& data) {
        sqlite3* db;
        if (sqlite3_open(database_name.c_str(), &db) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to open database");
        }

        std::string sql = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to prepare statement");
        }

        for (const auto& person : data) {
            sqlite3_bind_text(stmt, 1, person.name.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, person.age);

            if (sqlite3_step(stmt) != SQLITE_DONE) {
                sqlite3_finalize(stmt);
                throw_sqlite_error(db, "Failed to execute insert");
            }
            sqlite3_reset(stmt);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::optional<std::vector<std::tuple<int, std::string, int>>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        if (sqlite3_open(database_name.c_str(), &db) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to open database");
        }

        std::string sql = "SELECT * FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to prepare statement");
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int>> results;
        int step_result;
        while ((step_result = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name_text = sqlite3_column_text(stmt, 1);
            int age = sqlite3_column_int(stmt, 2);
            results.push_back(std::make_tuple(id, std::string(reinterpret_cast<const char*>(name_text)), age));
        }

        if (step_result != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw_sqlite_error(db, "Failed during step");
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (results.empty()) {
            return std::nullopt;
        } else {
            return results;
        }
    }

    void delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        if (sqlite3_open(database_name.c_str(), &db) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to open database");
        }

        std::string sql = "DELETE FROM " + table_name + " WHERE name = ?";
        sqlite3_stmt* stmt;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw_sqlite_error(db, "Failed to prepare statement");
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw_sqlite_error(db, "Failed to execute delete");
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};