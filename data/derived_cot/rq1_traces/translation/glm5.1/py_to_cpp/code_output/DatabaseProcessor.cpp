#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>
#include <tuple>
#include <sqlite3.h>
#include <stdexcept>
#include <memory>

class DatabaseProcessor {
private:
    std::string database_name;

    // RAII wrapper for sqlite3*
    struct Sqlite3Deleter {
        void operator()(sqlite3* db) const { sqlite3_close(db); }
    };
    using Sqlite3Ptr = std::unique_ptr<sqlite3, Sqlite3Deleter>;

    // RAII wrapper for sqlite3_stmt*
    struct Sqlite3StmtDeleter {
        void operator()(sqlite3_stmt* stmt) const { sqlite3_finalize(stmt); }
    };
    using Sqlite3StmtPtr = std::unique_ptr<sqlite3_stmt, Sqlite3StmtDeleter>;

    // Helper to execute simple SQL queries
    void execute_simple(Sqlite3Ptr& db, const std::string& sql) {
        char* err_msg = nullptr;
        int rc = sqlite3_exec(db.get(), sql.c_str(), nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string error = err_msg;
            sqlite3_free(err_msg);
            throw std::runtime_error(error);
        }
    }

public:
    DatabaseProcessor(std::string database_name) : database_name(std::move(database_name)) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        sqlite3* db_raw;
        int rc = sqlite3_open(database_name.c_str(), &db_raw);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db_raw));
        }
        Sqlite3Ptr db(db_raw);

        std::string create_table_query = "CREATE TABLE IF NOT EXISTS " + table_name + 
                                          " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        execute_simple(db, create_table_query);
    }

    void insert_into_database(const std::string& table_name, const std::vector<std::map<std::string, std::variant<std::string, int>>>& data) {
        sqlite3* db_raw;
        int rc = sqlite3_open(database_name.c_str(), &db_raw);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db_raw));
        }
        Sqlite3Ptr db(db_raw);

        // Python's sqlite3 implicitly starts a transaction for data modification
        execute_simple(db, "BEGIN;");

        std::string insert_query = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";
        
        sqlite3_stmt* stmt_raw;
        rc = sqlite3_prepare_v2(db.get(), insert_query.c_str(), -1, &stmt_raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db.get()));
        }
        Sqlite3StmtPtr stmt(stmt_raw);

        for (const auto& item : data) {
            // Access dictionary keys as done in the Python code
            const auto& name_val = item.at("name");
            const auto& age_val = item.at("age");
            
            std::string name_str = std::get<std::string>(name_val);
            int age_int = std::get<int>(age_val);

            sqlite3_bind_text(stmt.get(), 1, name_str.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt.get(), 2, age_int);

            rc = sqlite3_step(stmt.get());
            if (rc != SQLITE_DONE) {
                throw std::runtime_error(sqlite3_errmsg(db.get()));
            }
            
            sqlite3_reset(stmt.get());
            sqlite3_clear_bindings(stmt.get());
        }

        // Python's conn.commit() explicitly commits the transaction
        execute_simple(db, "COMMIT;");
    }

    std::optional<std::vector<std::tuple<int, std::string, int>>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* db_raw;
        int rc = sqlite3_open(database_name.c_str(), &db_raw);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db_raw));
        }
        Sqlite3Ptr db(db_raw);

        std::string select_query = "SELECT * FROM " + table_name + " WHERE name = ?";
        
        sqlite3_stmt* stmt_raw;
        rc = sqlite3_prepare_v2(db.get(), select_query.c_str(), -1, &stmt_raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db.get()));
        }
        Sqlite3StmtPtr stmt(stmt_raw);

        sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int>> results;
        
        while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt.get(), 0);
            const unsigned char* name_text = sqlite3_column_text(stmt.get(), 1);
            std::string name_str = name_text ? reinterpret_cast<const char*>(name_text) : "";
            int age = sqlite3_column_int(stmt.get(), 2);
            results.emplace_back(id, name_str, age);
        }

        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db.get()));
        }

        if (results.empty()) {
            return std::nullopt;
        }
        return results;
    }

    void delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* db_raw;
        int rc = sqlite3_open(database_name.c_str(), &db_raw);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db_raw));
        }
        Sqlite3Ptr db(db_raw);

        // Python's sqlite3 implicitly starts a transaction for data modification
        execute_simple(db, "BEGIN;");

        std::string delete_query = "DELETE FROM " + table_name + " WHERE name = ?";
        
        sqlite3_stmt* stmt_raw;
        rc = sqlite3_prepare_v2(db.get(), delete_query.c_str(), -1, &stmt_raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db.get()));
        }
        Sqlite3StmtPtr stmt(stmt_raw);

        sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt.get());
        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db.get()));
        }

        // Python's conn.commit() explicitly commits the transaction
        execute_simple(db, "COMMIT;");
    }
};