#include <string>
#include <optional>
#include <utility>
#include <sqlite3.h>

class UserLoginDB {
private:
    sqlite3* db;

public:
    UserLoginDB(const std::string& db_name) {
        sqlite3_open(db_name.c_str(), &db);
    }

    ~UserLoginDB() {
        sqlite3_close(db);
    }

    void insert_user(const std::string& username, const std::string& password) {
        sqlite3_stmt* stmt;
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    std::optional<std::pair<std::string, std::string>> search_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt;
        const char* sql = "SELECT * FROM users WHERE username = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            std::string user = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string pass = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            sqlite3_finalize(stmt);
            return std::make_pair(user, pass);
        }
        sqlite3_finalize(stmt);
        return std::nullopt;
    }

    void delete_user_by_username(const std::string& username) {
        sqlite3_stmt* stmt;
        const char* sql = "DELETE FROM users WHERE username = ?";
        sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    bool validate_user_login(const std::string& username, const std::string& password) {
        auto user = search_user_by_username(username);
        if (user.has_value() && user->second == password) {
            return true;
        }
        return false;
    }
};