#include <sqlite3.h>
#include <string>
#include <stdexcept>
#include <vector>
#include <cstdio>
#include <cerrno>

class SQLException : public std::runtime_error {
private:
    std::string message;
    std::string file;
    int line;
    std::string operation;

public:
    explicit SQLException(const std::string& msg, const std::string& file, int line, const std::string& op)
        : std::runtime_error(msg), message(msg), file(file), line(line), operation(op) {}

    void printStackTrace() {
        std::fprintf(stderr, "org::example::SQLException: %s (from %s at %s:%d)\n", 
                     message.c_str(), operation.c_str(), file.c_str(), line);
        std::vector<void*> trace(std::backtrace());
        std::fprintf(stderr, "Stack trace:\n");
        for (size_t i = 0; i < trace.size(); ++i) {
            char sym[256];
            std::sprintf(sym, "0x%zx", trace[i]);
            std::fprintf(stderr, "#%zu %s\n", i, sym);
        }
    }
};

class UserLoginDB {
private:
    sqlite3* db = nullptr;
    bool is_closed = false;

    static int callback(void* data, int argc, char** argv, char** azColName) {
        auto* result = static_cast<std::string*>(data);
        *result = "";
        for (int i = 0; i < argc; ++i) {
            if (!*result.empty()) *result += ',';
            *result += argv[i] ? argv[i] : "";
        }
        return SQLITE_OK;
    }

    void check_sqlite_error(int rc, const std::string& op) {
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, op);
        }
    }

public:
    UserLoginDB(const std::string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "open");
        }
        createTable();
    }

    ~UserLoginDB() {
        if (!is_closed && db != nullptr) {
            sqlite3_close(db);
        }
    }

    void close() {
        if (!is_closed && db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
            is_closed = true;
        }
    }

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)";
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "createTable");
        }
    }

    void insertUser(const std::string& username, const std::string& password) {
        std::string sql = "INSERT INTO users (username, password) VALUES (?, ?)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "insertUser");
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password.c_str(), password.size(), SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "insertUser execute");
        }

        sqlite3_finalize(stmt);
    }

    std::string searchUserByUsername(const std::string& username) {
        std::string result;
        std::string sql = "SELECT * FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "searchUserByUsername");
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            result = std::string(sqlite3_column_text(stmt, 0)) + ',';
            result += std::string(sqlite3_column_text(stmt, 1));
        } else if (rc != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "searchUserByUsername execute");
        }

        sqlite3_finalize(stmt);
        return result;
    }

    void deleteUserByUsername(const std::string& username) {
        std::string sql = "DELETE FROM users WHERE username = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "deleteUserByUsername");
        }

        sqlite3_bind_text(stmt, 1, username.c_str(), username.size(), SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db), __FILE__, __LINE__, "deleteUserByUsername execute");
        }

        sqlite3_finalize(stmt);
    }

    bool validateUserLogin(const std::string& username, const std::string& password) {
        std::string user = searchUserByUsername(username);
        if (user.empty()) return false;
        size_t pos = user.find(',');
        if (pos == std::string::npos) return false;
        return password == user.substr(pos + 1);
    }
};