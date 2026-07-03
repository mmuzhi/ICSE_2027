#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <any>
#include <sstream>
#include <sqlite3.h>

class DatabaseProcessor {
private:
    std::string databaseName;

    struct DatabaseHandle {
        sqlite3* db = nullptr;
        ~DatabaseHandle() {
            if (db) {
                sqlite3_close(db);
            }
        }
    };

public:
    DatabaseProcessor(const std::string& databaseName) : databaseName(databaseName) {}

    void createTable(const std::string& tableName, const std::string& key1, const std::string& key2) {
        std::string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";

        DatabaseHandle db;
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db.db, sql.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            if (errMsg) sqlite3_free(errMsg);
        }
    }

    void insertIntoDatabase(const std::string& tableName, const std::vector<std::map<std::string, std::any>>& data) {
        for (const auto& item : data) {
            try {
                std::string nameValue = std::any_cast<std::string>(item.at("name"));
                int ageValue = std::any_cast<int>(item.at("age"));

                std::string sql = "INSERT INTO " + tableName + " (name, age) VALUES ('" + nameValue + "', " + std::to_string(ageValue) + ")";

                DatabaseHandle db;
                char* errMsg = nullptr;
                int rc = sqlite3_exec(db.db, sql.c_str(), nullptr, nullptr, &errMsg);
                if (rc != SQLITE_OK) {
                    std::cerr << "SQL error: " << errMsg << std::endl;
                    if (errMsg) sqlite3_free(errMsg);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error processing item: " << e.what() << std::endl;
            }
        }
    }

    std::vector<std::map<std::string, std::any>> searchDatabase(const std::string& tableName, const std::string& name) {
        std::string sql = "SELECT * FROM " + tableName + " WHERE name = '" + name + "'";

        DatabaseHandle db;
        sqlite3_stmt* stmt = nullptr;
        char* errMsg = nullptr;
        int rc = sqlite3_prepare_v2(db.db, sql.c_str(), -1, &stmt, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << errMsg << std::endl;
            if (errMsg) sqlite3_free(errMsg);
            return {};
        }

        std::vector<std::map<std::string, std::any>> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* nameValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);

            std::map<std::string, std::any> row;
            row["id"] = id;
            row["name"] = nameValue ? std::string(nameValue) : std::string();
            row["age"] = age;
            result.push_back(row);
        }

        sqlite3_finalize(stmt);
        return result;
    }

    void deleteFromDatabase(const std::string& tableName, const std::string& name) {
        std::string sql = "DELETE FROM " + tableName + " WHERE name = '" + name + "'";

        DatabaseHandle db;
        sqlite3_stmt* stmt = nullptr;
        char* errMsg = nullptr;
        int rc = sqlite3_prepare_v2(db.db, sql.c_str(), -1, &stmt, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << errMsg << std::endl;
            if (errMsg) sqlite3_free(errMsg);
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Failed to delete row: " << sqlite3_errmsg(db.db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }
};