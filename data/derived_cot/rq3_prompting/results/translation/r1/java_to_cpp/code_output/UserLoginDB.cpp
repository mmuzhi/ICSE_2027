#include <iostream>
#include <string>
#include <optional>
#include <sqlite3.h>

class UserLoginDB {
private:
    sqlite3* db;

    void executeSQL(const std::string& sql) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

public:
    UserLoginDB(const std::string& dbName) : db(nullptr) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
            db = nullptr;
            return;
        }
        createTable();
    }

    ~UserLoginDB() {
        close();
    }

    void createTable() {
        if (!db) return;
        const std::string sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        executeSQL(sql);
    }

    void insertUser(const std::string& username, const std::string& password) {
        if (!db) return;
        const std::string sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Insert error: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    std::optional<std::string> searchUserByUsername(const std::string& username) {
        if (!db) return std::nullopt;
        const std::string sql = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
            return std::nullopt;
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        std::optional<std::string> result = std::nullopt;
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            const char* pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            if (user && pass) {
                result = std::string(user) + "," + std::string(pass);
            }
        }
        sqlite3_finalize(stmt);
        return result;
    }

    void deleteUserByUsername(const std::string& username) {
        if (!db) return;
        const std::string sql = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Prepare error: " << sqlite3_errmsg(db) << std::endl;
            return;
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Delete error: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        auto userOpt = searchUserByUsername(username);
        if (userOpt.has_value()) {
            std::string user = userOpt.value();
            size_t commaPos = user.find(',');
            if (commaPos != std::string::npos) {
                std::string storedPassword = user.substr(commaPos + 1);
                return storedPassword == password;
            }
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