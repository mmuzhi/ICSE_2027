#include <string>
#include <vector>
#include <map>
#include <any>
#include <optional>
#include <cstdio>
#include <sqlite3.h>

class DatabaseProcessor {
private:
    std::string databaseName;

public:
    DatabaseProcessor(std::string databaseName) : databaseName(std::move(databaseName)) {}

    void createTable(const std::string& tableName, const std::string& key1, const std::string& key2) {
        sqlite3* db;
        if (sqlite3_open(databaseName.c_str(), &db) == SQLITE_OK) {
            std::string query = "CREATE TABLE IF NOT EXISTS " + tableName + " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
            char* errMsg = nullptr;
            if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errMsg);
                sqlite3_free(errMsg);
            }
            sqlite3_close(db);
        }
    }

    void insertIntoDatabase(const std::string& tableName, const std::vector<std::map<std::string, std::any>>& data) {
        sqlite3* db;
        if (sqlite3_open(databaseName.c_str(), &db) == SQLITE_OK) {
            for (const auto& item : data) {
                std::string name_val = std::any_cast<std::string>(item.at("name"));
                int age_val = std::any_cast<int>(item.at("age"));
                std::string query = "INSERT INTO " + tableName + " (name, age) VALUES ('" + name_val + "', " + std::to_string(age_val) + ")";
                char* errMsg = nullptr;
                if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
                    fprintf(stderr, "SQL error: %s\n", errMsg);
                    sqlite3_free(errMsg);
                }
            }
            sqlite3_close(db);
        }
    }

    std::optional<std::vector<std::map<std::string, std::any>>> searchDatabase(const std::string& tableName, const std::string& name) {
        std::vector<std::map<std::string, std::any>> result;
        sqlite3* db;
        if (sqlite3_open(databaseName.c_str(), &db) == SQLITE_OK) {
            std::string query = "SELECT * FROM " + tableName + " WHERE name = '" + name + "'";
            sqlite3_stmt* stmt;
            if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
                while (sqlite3_step(stmt) == SQLITE_ROW) {
                    std::map<std::string, std::any> row;
                    row["id"] = sqlite3_column_int(stmt, 0);
                    const char* name_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                    row["name"] = name_text ? std::string(name_text) : std::string();
                    row["age"] = sqlite3_column_int(stmt, 2);
                    result.push_back(row);
                }
            } else {
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);
        }
        if (result.empty()) {
            return std::nullopt;
        }
        return result;
    }

    void deleteFromDatabase(const std::string& tableName, const std::string& name) {
        sqlite3* db;
        if (sqlite3_open(databaseName.c_str(), &db) == SQLITE_OK) {
            std::string query = "DELETE FROM " + tableName + " WHERE name = '" + name + "'";
            char* errMsg = nullptr;
            if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errMsg);
                sqlite3_free(errMsg);
            }
            sqlite3_close(db);
        }
    }
};