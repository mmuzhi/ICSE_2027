#include <sqlite3.h>
#include <string>
#include <iostream>
#include <cerrno>
#include <sstream>

class UserLoginDB {
private:
    sqlite3* db;

    void print_sqlite_error(const std::string& op) {
        int code = sqlite3_errcode(db);
        const char* msg = sqlite3_errmsg(db);
        std::cerr << "SQL error in " << op << ": " << msg << " (code " << code << ")" << std::endl;
    }

public:
    UserLoginDB(const std::string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            print_sqlite_error("open");
        } else {
            createTable();
        }
    }

    ~UserLoginDB() {
        if (db) {
            close();
        }
    }

    void close() {
        if (db) {
            int rc = sqlite3_close(db);
            db = nullptr;
            if (rc != SQLITE_OK) {
                print_sqlite_error("close");
            }
        }
    }

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            print_sqlite_error("createTable");
            if (errMsg) {
                sqlite3_free(errMsg);
            }
        }
    }

    void insertUser(const std::string& username, const std::string& password) {
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_sqlite_error("insertUser prepare");
        } else {
            sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password.c_str(), password.size(), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                print_sqlite_error("insertUser step");
            }
            sqlite3_finalize(stmt);
        }
    }

    std::string searchUserByUsername(const std::string& username) {
        const char* sql = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_sqlite_error("searchUserByUsername prepare");
        } else {
            sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            std::string result;
            if (rc == SQLITE_ROW) {
                const char* username_val = (const char*)sqlite3_column_text(stmt, 0);
                const char* password_val = (const char*)sqlite3_column_text(stmt, 1);
                if (username_val && password_val) {
                    result = std::string(username_val) + "," + std::string(password_val);
                }
            } else if (rc != SQLITE_DONE) {
                print_sqlite_error("searchUserByUsername step");
            }
            sqlite3_finalize(stmt);
        }
        return result;
    }

    void deleteUserByUsername(const std::string& username) {
        const char* sql = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_sqlite_error("deleteUserByUsername prepare");
        } else {
            sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                print_sqlite_error("deleteUserByUsername step");
            }
            sqlite3_finalize(stmt);
        }
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        std::string user = searchUserByUsername(username);
        if (user != "") {
            size_t pos = user.find(',');
            if (pos != std::string::npos) {
                std::string storedPassword = user.substr(pos + 1);
                return storedPassword == password;
            }
        }
        return false;
    }
};