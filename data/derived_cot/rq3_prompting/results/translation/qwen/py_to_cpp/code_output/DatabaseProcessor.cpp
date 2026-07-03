#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>
#include <optional>

class DatabaseProcessor {
public:
    DatabaseProcessor(const std::string& database_name) : database_name_(database_name) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        sqlite3* db;
        char* error_msg = nullptr;

        int rc = sqlite3_open(database_name_.c_str(), &db);
        if (rc != SQLITE_OK) {
            // Handle error if needed, but Python doesn't throw exceptions
            return;
        }

        std::string create_query = "CREATE TABLE IF NOT EXISTS " + table_name + " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        rc = sqlite3_exec(db, create_query.c_str(), nullptr, nullptr, &error_msg);
        if (rc != SQLITE_OK) {
            // Handle error if needed
            sqlite3_free(error_msg);
        }

        sqlite3_close(db);
    }

    bool insert_into_database(const std::string& table_name, const std::vector<std::map<std::string, std::string>>& data) {
        sqlite3* db;
        char* error_msg = nullptr;

        int rc = sqlite3_open(database_name_.c_str(), &db);
        if (rc != SQLITE_OK) {
            return false;
        }

        sqlite3_stmt* stmt;
        std::string insert_query = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";
        rc = sqlite3_prepare_v2(db, insert_query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return false;
        }

        for (const auto& item : data) {
            sqlite3_bind_text(stmt, 1, item.at("name").c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, item.at("age").c_str(), -1, SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            sqlite3_clear_bindings(stmt);
            if (rc != SQLITE_DONE) {
                sqlite3_finalize(stmt);
                sqlite3_close(db);
                return false;
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_commit(db); // Ensure commit is called even if there are errors
        sqlite3_close(db);
        return true;
    }

    std::optional<std::vector<std::vector<std::string>>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        char* error_msg = nullptr;

        int rc = sqlite3_open(database_name_.c_str(), &db);
        if (rc != SQLITE_OK) {
            return std::nullopt;
        }

        sqlite3_stmt* stmt;
        std::string select_query = "SELECT * FROM " + table_name + " WHERE name = ?";
        rc = sqlite3_prepare_v2(db, select_query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return std::nullopt;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);

        std::vector<std::vector<std::string>> result;
        if (rc == SQLITE_ROW) {
            while (rc == SQLITE_ROW) {
                int num_columns = sqlite3_column_count(stmt);
                std::vector<std::string> row;
                for (int i = 0; i < num_columns; i++) {
                    const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                    row.push_back(text ? std::string(text) : "");
                }
                result.push_back(row);
                rc = sqlite3_step(stmt);
            }
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    bool delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* db;
        char* error_msg = nullptr;

        int rc = sqlite3_open(database_name_.c_str(), &db);
        if (rc != SQLITE_OK) {
            return false;
        }

        sqlite3_stmt* stmt;
        std::string delete_query = "DELETE FROM " + table_name + " WHERE name = ?";
        rc = sqlite3_prepare_v2(db, delete_query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return false;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);

        sqlite3_close(db);
        return true;
    }

private:
    std::string database_name_;
};