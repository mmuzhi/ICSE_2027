#include <sqlite3.h>
#include <iostream>
#include <string>
#include <cstring>

class UserLoginDB {
private:
    sqlite3* db;

    void createTable() {
        if (!db) return;

        const char* createTableQuery = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

public:
    UserLoginDB(const std::string& dbName) : db(nullptr) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            db = nullptr;
            return;
        }
        createTable();
    }

    ~UserLoginDB() {
        close();
    }

    void insertUser(const std::string& username, const std::string& password) {
        if (!db) return;

        const char* insertQuery = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind username: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return;
        }

        rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind password: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    std::string searchUserByUsername(const std::string& username) {
        if (!db) return "";

        const char* searchQuery = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, searchQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return "";
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind username: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return "";
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            const char* u = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* p = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string result = std::string(u) + "," + std::string(p);
            sqlite3_finalize(stmt);
            return result;
        } else if (rc == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return "";
        } else {
            std::cerr << "Search failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return "";
        }
    }

    void deleteUserByUsername(const std::string& username) {
        if (!db) return;

        const char* deleteQuery = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, deleteQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to bind username: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Delete failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        std::string user = searchUserByUsername(username);
        if (!user.empty()) {
            size_t pos = user.find(',');
            if (pos == std::string::npos) {
                return false;
            }
            std::string storedPassword = user.substr(pos + 1);
            return storedPassword == password;
        }
        return false;
    }

    void close() {
        if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }
};