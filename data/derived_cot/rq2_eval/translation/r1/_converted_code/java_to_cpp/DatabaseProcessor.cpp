#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <any>

class DatabaseProcessor {
private:
    std::string databaseName;

public:
    DatabaseProcessor(const std::string& databaseName) : databaseName(databaseName) {}

    void create_table(const std::string& tableName, const std::string& key1, const std::string& key2) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        std::string query = "CREATE TABLE IF NOT EXISTS " + tableName +
                            " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        char* errMsg = nullptr;
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << (errMsg ? errMsg : "Unknown error") << std::endl;
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
    }

    void insert_into_database(const std::string& tableName, const std::vector<std::map<std::string, std::any>>& data) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        for (const auto& item : data) {
            try {
                std::string name = std::any_cast<std::string>(item.at("name"));
                int age = std::any_cast<int>(item.at("age"));
                std::string query = "INSERT INTO " + tableName + " (name, age) VALUES ('" + name + "', " + std::to_string(age) + ")";
                char* errMsg = nullptr;
                rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
                if (rc != SQLITE_OK) {
                    std::cerr << "SQL error: " << (errMsg ? errMsg : "Unknown error") << std::endl;
                    sqlite3_free(errMsg);
                }
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Bad any cast: " << e.what() << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << std::endl;
            }
        }

        sqlite3_close(db);
    }

    std::vector<std::map<std::string, std::any>>* searchDatabase(const std::string& tableName, const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return nullptr;
        }

        auto resultVec = new std::vector<std::map<std::string, std::any>>();
        std::string query = "SELECT * FROM " + tableName + " WHERE name = '" + name + "'";

        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            delete resultVec;
            return nullptr;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::map<std::string, std::any> row;
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* nameText = sqlite3_column_text(stmt, 1);
            int age = sqlite3_column_int(stmt, 2);

            row["id"] = id;
            row["name"] = std::string(reinterpret_cast<const char*>(nameText));
            row["age"] = age;
            resultVec->push_back(row);
        }

        if (rc != SQLITE_DONE) {
            std::cerr << "Error stepping: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        if (resultVec->empty()) {
            delete resultVec;
            return nullptr;
        } else {
            return resultVec;
        }
    }

    void delete_from_database(const std::string& tableName, const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        std::string query = "DELETE FROM " + tableName + " WHERE name = '" + name + "'";
        char* errMsg = nullptr;
        rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << (errMsg ? errMsg : "Unknown error") << std::endl;
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
    }
};