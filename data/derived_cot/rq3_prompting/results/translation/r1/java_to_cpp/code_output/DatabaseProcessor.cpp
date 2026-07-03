#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>
#include <sstream>

class DatabaseProcessor {
private:
    std::string databaseName;

    // Helper to execute a query that produces no result set
    void executeNonQuery(const std::string& query) {
        sqlite3* db = nullptr;
        char* errMsg = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "SQLite error: " << sqlite3_errmsg(db) << std::endl;
            if (db) sqlite3_close(db);
            return;
        }
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQLite error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        sqlite3_close(db);
    }

public:
    DatabaseProcessor(const std::string& databaseName)
        : databaseName(databaseName) {}

    void createTable(const std::string& tableName,
                     const std::string& key1,
                     const std::string& key2) {
        std::ostringstream query;
        query << "CREATE TABLE IF NOT EXISTS " << tableName
              << " (id INTEGER PRIMARY KEY, " << key1 << " TEXT, " << key2 << " INTEGER)";
        executeNonQuery(query.str());
    }

    void insertIntoDatabase(const std::string& tableName,
                            const std::vector<std::map<std::string, std::variant<int, std::string>>>& data) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "SQLite error: " << sqlite3_errmsg(db) << std::endl;
            if (db) sqlite3_close(db);
            return;
        }

        for (const auto& item : data) {
            // Extract values assuming keys "name" and "age" exist
            std::string name = std::get<std::string>(item.at("name"));
            int age = std::get<int>(item.at("age"));

            std::ostringstream query;
            query << "INSERT INTO " << tableName << " (name, age) VALUES ('"
                  << name << "', " << age << ")";

            char* errMsg = nullptr;
            rc = sqlite3_exec(db, query.str().c_str(), nullptr, nullptr, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQLite error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
        }
        sqlite3_close(db);
    }

    std::optional<std::vector<std::map<std::string, std::variant<int, std::string>>>>
    searchDatabase(const std::string& tableName, const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "SQLite error: " << sqlite3_errmsg(db) << std::endl;
            if (db) sqlite3_close(db);
            return std::nullopt;
        }

        std::ostringstream query;
        query << "SELECT * FROM " << tableName << " WHERE name = '" << name << "'";

        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQLite error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return std::nullopt;
        }

        std::vector<std::map<std::string, std::variant<int, std::string>>> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::map<std::string, std::variant<int, std::string>> row;
            row["id"] = sqlite3_column_int(stmt, 0);
            row["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            row["age"] = sqlite3_column_int(stmt, 2);
            result.push_back(row);
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (result.empty()) {
            return std::nullopt;  // mimic Java returning null
        }
        return result;
    }

    void deleteFromDatabase(const std::string& tableName, const std::string& name) {
        std::ostringstream query;
        query << "DELETE FROM " << tableName << " WHERE name = '" << name << "'";
        executeNonQuery(query.str());
    }
};