#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>

class MovieTicketDB {
private:
    sqlite3* db;

    void exec(const std::string& sql) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string error = errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error("SQLite error: " + error);
        }
    }

public:
    MovieTicketDB(const std::string& db_name) {
        if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
            std::string error = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Cannot open database: " + error);
        }
        create_table();
    }

    ~MovieTicketDB() {
        if (db) {
            sqlite3_close(db);
        }
    }

    void create_table() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS tickets (
                id INTEGER PRIMARY KEY,
                movie_name TEXT,
                theater_name TEXT,
                seat_number TEXT,
                customer_name TEXT
            )
        )";
        exec(sql);
    }

    void insert_ticket(const std::string& movie_name,
                       const std::string& theater_name,
                       const std::string& seat_number,
                       const std::string& customer_name) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_bind_text(stmt, 1, movie_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, theater_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, seat_number.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, customer_name.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }

    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>>
    search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT id, movie_name, theater_name, seat_number, customer_name FROM tickets WHERE customer_name = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_bind_text(stmt, 1, customer_name.c_str(), -1, SQLITE_TRANSIENT);
        std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> results;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string movie_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string theater_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string seat_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string customer_name_res = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            results.emplace_back(id, movie_name, theater_name, seat_number, customer_name_res);
        }
        sqlite3_finalize(stmt);
        return results;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_bind_int(stmt, 1, ticket_id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        sqlite3_finalize(stmt);
    }
};