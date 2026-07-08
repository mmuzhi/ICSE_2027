#ifndef USER_LOGIN_DB_H
#define USER_LOGIN_DB_H

#include <sqlite3.h>
#include <string>
#include <optional>
#include <iostream>
#include <sstream>
#include <vector>

class UserLoginDB {
private:
    sqlite3* connection;

    void createTable() {
        const char* createTableQuery = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(connection, createTableQuery, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }

public:
    UserLoginDB(const std::string& dbName) : connection(nullptr) {
        int rc = sqlite3_open(dbName.c_str(), &connection);
        if (rc == SQLITE_OK) {
            createTable();
        } else {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            sqlite3_close(connection);
            connection = nullptr;
        }
    }

    void insertUser(const std::string& username, const std::string& password) {
        const char* insertQuery = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* pstmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, insertQuery, -1, &pstmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return;
        }
        sqlite3_bind_text(pstmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(pstmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        rc = sqlite3_step(pstmt);
        if (rc != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        sqlite3_finalize(pstmt);
    }

    std::optional<std::string> searchUserByUsername(const std::string& username) {
        const char* searchQuery = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* pstmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, searchQuery, -1, &pstmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return std::nullopt;
        }
        sqlite3_bind_text(pstmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        rc = sqlite3_step(pstmt);
        if (rc == SQLITE_ROW) {
            const char* usernameCol = reinterpret_cast<const char*>(sqlite3_column_text(pstmt, 0));
            const char* passwordCol = reinterpret_cast<const char*>(sqlite3_column_text(pstmt, 1));
            // Java's getString returns null for SQL NULL; concatenation converts null to "null"
            std::string usernameStr = usernameCol ? std::string(usernameCol) : "null";
            std::string passwordStr = passwordCol ? std::string(passwordCol) : "null";
            std::string result = usernameStr + "," + passwordStr;
            sqlite3_finalize(pstmt);
            return result;
        }
        sqlite3_finalize(pstmt);
        return std::nullopt;
    }

    void deleteUserByUsername(const std::string& username) {
        const char* deleteQuery = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* pstmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, deleteQuery, -1, &pstmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return;
        }
        sqlite3_bind_text(pstmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        rc = sqlite3_step(pstmt);
        if (rc != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        sqlite3_finalize(pstmt);
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        auto user = searchUserByUsername(username);
        if (user.has_value()) {
            // Replicate Java's String.split(",") — split on every comma, take index 1
            std::vector<std::string> parts;
            std::istringstream iss(*user);
            std::string part;
            while (std::getline(iss, part, ',')) {
                parts.push_back(part);
            }
            if (parts.size() > 1) {
                return parts[1] == password;
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

    ~UserLoginDB() {
        close();
    }

    // Prevent copying to avoid double-close
    UserLoginDB(const UserLoginDB&) = delete;
    UserLoginDB& operator=(const UserLoginDB&) = delete;
};

#endif // USER_LOGIN_DB_H