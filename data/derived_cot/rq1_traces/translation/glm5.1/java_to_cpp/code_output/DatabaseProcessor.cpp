#ifndef DATABASE_PROCESSOR_H
#define DATABASE_PROCESSOR_H

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

    // Note: Java's static block loading the JDBC driver is unnecessary in C++;
    // sqlite3 is linked directly at compile time.

public:
    DatabaseProcessor(const std::string& databaseName) : databaseName(databaseName) {}

    void createTable(const std::string& tableName, const std::string& key1, const std::string& key2) {
        sqlite3* db;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        std::string query = "CREATE TABLE IF NOT EXISTS " + tableName +
            " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";

        char* errMsg = nullptr;
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
    }

    void insertIntoDatabase(const std::string& tableName, const std::vector<std::map<std::string, std::any>>& data) {
        sqlite3* db;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        for (const auto& item : data) {
            const std::string& nameVal = std::any_cast<const std::string&>(item.at("name"));
            int ageVal = std::any_cast<int>(item.at("age"));

            char query[1024];
            snprintf(query, sizeof(query),
                "INSERT INTO %s (name, age) VALUES ('%s', %d)",
                tableName.c_str(), nameVal.c_str(), ageVal);

            char* errMsg = nullptr;
            rc = sqlite3_exec(db, query, nullptr, nullptr, &errMsg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", errMsg);
                sqlite3_free(errMsg);
            }
        }

        sqlite3_close(db);
    }

    // Returns std::nullopt when no results found (mirrors Java's null return),
    // otherwise returns the vector of row maps.
    std::optional<std::vector<std::map<std::string, std::any>>> searchDatabase(const std::string& tableName, const std::string& name) {
        std::vector<std::map<std::string, std::any>> result;

        sqlite3* db;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return std::nullopt;
        }

        std::string query = "SELECT * FROM " + tableName + " WHERE name = '" + name + "'";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return std::nullopt;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::map<std::string, std::any> row;
            row["id"] = sqlite3_column_int(stmt, 0);
            const unsigned char* text = sqlite3_column_text(stmt, 1);
            row["name"] = text ? std::string(reinterpret_cast<const char*>(text)) : std::string();
            row["age"] = sqlite3_column_int(stmt, 2);
            result.push_back(row);
        }

        if (rc != SQLITE_DONE) {
            fprintf(stderr, "SQL error during iteration: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (result.empty()) {
            return std::nullopt;
        }
        return result;
    }

    void deleteFromDatabase(const std::string& tableName, const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return;
        }

        std::string query = "DELETE FROM " + tableName + " WHERE name = '" + name + "'";

        char* errMsg = nullptr;
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
    }
};

#endif