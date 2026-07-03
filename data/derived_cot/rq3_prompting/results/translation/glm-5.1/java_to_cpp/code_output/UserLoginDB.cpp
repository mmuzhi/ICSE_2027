#include <sqlite3.h>
#include <string>
#include <iostream>

class UserLoginDB {
private:
    sqlite3* connection;

    void createTable() {
        const char* query = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_step(stmt);
        } else {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        if (stmt) sqlite3_finalize(stmt);
    }

public:
    UserLoginDB(const std::string& dbName) : connection(nullptr) {
        if (sqlite3_open(dbName.c_str(), &connection) != SQLITE_OK) {
            std::cerr << (connection ? sqlite3_errmsg(connection) : "Failed to open database") << std::endl;
            if (connection) {
                sqlite3_close(connection);
                connection = nullptr;
            }
        } else {
            createTable();
        }
    }

    void insertUser(const std::string& username, const std::string& password) {
        const char* query = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) != SQLITE_DONE) {
                std::cerr << sqlite3_errmsg(connection) << std::endl;
            }
        } else {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        if (stmt) sqlite3_finalize(stmt);
    }

    std::string searchUserByUsername(const std::string& username) {
        const char* query = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                const char* uname = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                const char* pwd = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string result = std::string(uname ? uname : "") + "," + std::string(pwd ? pwd : "");
                sqlite3_finalize(stmt);
                return result;
            }
        } else {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        if (stmt) sqlite3_finalize(stmt);
        return "";
    }

    void deleteUserByUsername(const std::string& username) {
        const char* query = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, query, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
            if (sqlite3_step(stmt) != SQLITE_DONE) {
                std::cerr << sqlite3_errmsg(connection) << std::endl;
            }
        } else {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        if (stmt) sqlite3_finalize(stmt);
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        std::string user = searchUserByUsername(username);
        if (!user.empty()) {
            size_t commaPos = user.find(',');
            if (commaPos != std::string::npos) {
                return user.substr(commaPos + 1) == password;
            }
        }
        return false;
    }

    void close() {
        if (connection != nullptr) {
            sqlite3_close(connection);
            connection = nullptr;
        }
    }
};