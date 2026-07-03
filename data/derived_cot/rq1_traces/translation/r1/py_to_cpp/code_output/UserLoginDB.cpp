#include <sqlite3.h>
#include <iostream>
#include <optional>
#include <vector>
#include <string>
#include <stdexcept>

class UserLoginDB {
public:
    UserLoginDB(const std::string& db_name) {
        sqlite3* temp_db = nullptr;
        int rc = sqlite3_open(db_name.c_str(), &temp_db);
        if (rc != SQLITE_OK) {
            std::string errmsg = sqlite3_errmsg(temp_db);
            sqlite3_close(temp_db);
            throw std::runtime_error("Failed to open database: " + errmsg);
        }
        db = temp_db;
    }

    ~UserLoginDB() {
        sqlite3_close(db);
    }

    UserLoginDB(const UserLoginDB&) = delete;
    UserLoginDB& operator=(const UserLoginDB&) = delete;

    void insert_user(const std::string& username, const std::string& password) {
        const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        commit();
    }

    std::optional<std::vector<std::string>> search_user_by_username(const std::string& username) {
        const char* sql = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int ncols = sqlite3_column_count(stmt);
            std::vector<std::string> row;
            for (int i = 0; i < ncols; i++) {
                const unsigned char* col_text = sqlite3_column_text(stmt, i);
                if (col_text) {
                    row.push_back(std::string(reinterpret_cast<const char*>(col_text)));
                } else {
                    row.push_back("");
                }
            }
            sqlite3_finalize(stmt);
            return row;
        } else if (rc == SQLITE_DONE) {
            sqlite3_finalize(stmt);
            return std::nullopt;
        } else {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void delete_user_by_username(const std::string& username) {
        const char* sql = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
        commit();
    }

    bool validate_user_login(const std::string& username, const std::string& password) {
        auto user = search_user_by_username(username);
        if (user.has_value()) {
            std::vector<std::string> row = user.value();
            if (row.size() < 2) {
                return false;
            }
            if (row[1] == password) {
                return true;
            }
        }
        return false;
    }

private:
    sqlite3* db;

    void commit() {
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, "COMMIT", 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::string error = errMsg ? std::string(errMsg) : "unknown error";
            sqlite3_free(errMsg);
            throw std::runtime_error("Commit failed: " + error);
        }
    }
};