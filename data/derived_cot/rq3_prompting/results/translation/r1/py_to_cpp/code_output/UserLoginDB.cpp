#include <sqlite3.h>
#include <string>
#include <optional>
#include <utility>
#include <stdexcept>

class UserLoginDB {
public:
    UserLoginDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &connection);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to open database: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    ~UserLoginDB() {
        if (connection) {
            sqlite3_close(connection);
        }
    }

    void insert_user(const std::string& username, const std::string& password) {
        sqlite3_stmt* stmt = nullptr;
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to insert user: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_finalize(stmt);
    }

    std::optional<std::pair<std::string, std::string>> search_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt = nullptr;
        const char* sql = "SELECT * FROM users WHERE username = ?";
        if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            std::string found_username(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            std::string found_password(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            sqlite3_finalize(stmt);
            return std::make_pair(found_username, found_password);
        } else if (rc == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return std::nullopt;
        } else {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to search user: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    void delete_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt = nullptr;
        const char* sql = "DELETE FROM users WHERE username = ?";
        if (sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to delete user: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_finalize(stmt);
    }

    bool validate_user_login(const std::string& username, const std::string& password) {
        auto user = search_user_by_username(username);
        if (user.has_value() && user->second == password) {
            return true;
        }
        return false;
    }

private:
    sqlite3* connection = nullptr;
};