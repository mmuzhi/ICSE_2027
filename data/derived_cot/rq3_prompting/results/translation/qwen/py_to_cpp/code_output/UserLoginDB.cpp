#include <sqlite3.h>
#include <string>

class UserLoginDB {
private:
    sqlite3* connection;
    sqlite3_stmt* cursor;

public:
    explicit UserLoginDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &connection);
        if (rc != SQLITE_OK) {
            // Handle error (optional, matches Python's implicit behavior)
        }
        cursor = nullptr;
    }

    ~UserLoginDB() {
        if (cursor) {
            sqlite3_finalize(cursor);
        }
        sqlite3_close(connection);
    }

    bool insert_user(const std::string& username, const std::string& password) {
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        int rc = sqlite3_prepare_v2(connection, sql, -1, &cursor, nullptr);
        if (rc != SQLITE_OK) {
            return false;
        }

        sqlite3_bind_text(cursor, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(cursor, 2, password.c_str(), -1, SQLITE_STATIC);

        int execute_rc = sqlite3_step(cursor);
        sqlite3_finalize(cursor);
        cursor = nullptr;

        if (execute_rc != SQLITE_DONE) {
            return false;
        }

        sqlite3_exec(connection, "COMMIT;", nullptr, nullptr, nullptr);
        return true;
    }

    std::vector<std::vector<std::string>> search_user_by_username(const std::string& username) {
        const char* sql = "SELECT * FROM users WHERE username = ?";
        int rc = sqlite3_prepare_v2(connection, sql, -1, &cursor, nullptr);
        if (rc != SQLITE_OK) {
            return {};
        }

        sqlite3_bind_text(cursor, 1, username.c_str(), -1, SQLITE_STATIC);
        int execute_rc = sqlite3_step(cursor);
        if (execute_rc != SQLITE_ROW && execute_rc != SQLITE_DONE) {
            sqlite3_finalize(cursor);
            cursor = nullptr;
            return {};
        }

        std::vector<std::vector<std::string>> result;
        while (execute_rc == SQLITE_ROW) {
            int num_columns = sqlite3_column_count(cursor);
            std::vector<std::string> row;
            for (int i = 0; i < num_columns; ++i) {
                const char* text = reinterpret_cast<const char*>(sqlite3_column_text(cursor, i));
                row.push_back(text ? std::string(text) : "");
            }
            result.push_back(row);
            execute_rc = sqlite3_step(cursor);
        }

        sqlite3_finalize(cursor);
        cursor = nullptr;
        return result;
    }

    bool delete_user_by_username(const std::string& username) {
        const char* sql = "DELETE FROM users WHERE username = ?";
        int rc = sqlite3_prepare_v2(connection, sql, -1, &cursor, nullptr);
        if (rc != SQLITE_OK) {
            return false;
        }

        sqlite3_bind_text(cursor, 1, username.c_str(), -1, SQLITE_STATIC);
        int execute_rc = sqlite3_step(cursor);
        sqlite3_finalize(cursor);
        cursor = nullptr;

        if (execute_rc != SQLITE_DONE) {
            return false;
        }

        sqlite3_exec(connection, "COMMIT;", nullptr, nullptr, nullptr);
        return true;
    }

    bool validate_user_login(const std::string& username, const std::string& password) {
        auto users = search_user_by_username(username);
        if (users.empty()) {
            return false;
        }

        auto& user = users[0];
        if (user.size() < 2 || user[1] != password) {
            return false;
        }

        return true;
    }
};