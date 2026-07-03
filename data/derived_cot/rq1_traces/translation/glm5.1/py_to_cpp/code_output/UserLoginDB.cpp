#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <sqlite3.h>

class UserLoginDB {
private:
    sqlite3* db;

public:
    UserLoginDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err_msg = db ? sqlite3_errmsg(db) : "out of memory";
            sqlite3_close(db);
            throw std::runtime_error("Cannot open database: " + err_msg);
        }
    }

    ~UserLoginDB() {
        if (db) {
            sqlite3_close(db);
        }
    }

    // Disable copy constructor and assignment operator to prevent double-free
    UserLoginDB(const UserLoginDB&) = delete;
    UserLoginDB& operator=(const UserLoginDB&) = delete;

    // Enable move semantics
    UserLoginDB(UserLoginDB&& other) noexcept : db(other.db) {
        other.db = nullptr;
    }

    UserLoginDB& operator=(UserLoginDB&& other) noexcept {
        if (this != &other) {
            if (db) {
                sqlite3_close(db);
            }
            db = other.db;
            other.db = nullptr;
        }
        return *this;
    }

    void insert_user(const std::string& username, const std::string& password) {
        sqlite3_stmt* stmt;
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("SQL error: " + std::string(sqlite3_errmsg(db)));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL bind error: " + err_msg);
        }

        rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL bind error: " + err_msg);
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL error: " + err_msg);
        }
        sqlite3_finalize(stmt);
    }

    std::optional<std::vector<std::optional<std::string>>> search_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT * FROM users WHERE username = ?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("SQL error: " + std::string(sqlite3_errmsg(db)));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL bind error: " + err_msg);
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int cols = sqlite3_column_count(stmt);
            std::vector<std::optional<std::string>> row;
            row.reserve(cols);
            for (int i = 0; i < cols; ++i) {
                const unsigned char* text = sqlite3_column_text(stmt, i);
                if (text) {
                    row.emplace_back(std::string(reinterpret_cast<const char*>(text)));
                } else {
                    row.emplace_back(std::nullopt);
                }
            }
            sqlite3_finalize(stmt);
            return row;
        } else if (rc == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return std::nullopt;
        } else {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL error: " + err_msg);
        }
    }

    void delete_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt;
        const char* sql = "DELETE FROM users WHERE username = ?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("SQL error: " + std::string(sqlite3_errmsg(db)));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL bind error: " + err_msg);
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err_msg = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            throw std::runtime_error("SQL error: " + err_msg);
        }
        sqlite3_finalize(stmt);
    }

    bool validate_user_login(const std::string& username, const std::string& password) {
        auto user = search_user_by_username(username);
        // user->at(1) corresponds to user[1] in Python. 
        // It throws std::out_of_range if the index is invalid, matching Python's IndexError.
        if (user.has_value() && user->at(1).has_value() && user->at(1).value() == password) {
            return true;
        }
        return false;
    }
};