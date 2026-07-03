#include <sqlite3.h>
#include <vector>
#include <tuple>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstring>

class MovieTicketDB {
private:
    sqlite3* db;

    void throw_sqlite_error(int rc) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }

    void commit() {
        char* errmsg = nullptr;
        int rc = sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            std::string error = errmsg ? errmsg : "Unknown error";
            sqlite3_free(errmsg);
            throw std::runtime_error("Commit failed: " + error);
        }
    }

public:
    MovieTicketDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    ~MovieTicketDB() {
        sqlite3_close(db);
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
                          "id INTEGER PRIMARY KEY,"
                          "movie_name TEXT,"
                          "theater_name TEXT,"
                          "seat_number TEXT,"
                          "customer_name TEXT)";
        char* errmsg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            std::string error = errmsg ? errmsg : "Unknown error";
            sqlite3_free(errmsg);
            throw std::runtime_error(error);
        }
        commit();
    }

    void insert_ticket(const std::string& movie_name, const std::string& theater_name,
                       const std::string& seat_number, const std::string& customer_name) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";
        auto deleter = [](sqlite3_stmt* stmt) { sqlite3_finalize(stmt); };
        std::unique_ptr<sqlite3_stmt, decltype(deleter)> stmt_ptr(nullptr, deleter);

        sqlite3_stmt* raw_stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &raw_stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw_sqlite_error(rc);
        }
        stmt_ptr.reset(raw_stmt);

        rc = sqlite3_bind_text(stmt_ptr.get(), 1, movie_name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);
        rc = sqlite3_bind_text(stmt_ptr.get(), 2, theater_name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);
        rc = sqlite3_bind_text(stmt_ptr.get(), 3, seat_number.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);
        rc = sqlite3_bind_text(stmt_ptr.get(), 4, customer_name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);

        rc = sqlite3_step(stmt_ptr.get());
        if (rc != SQLITE_DONE) {
            throw_sqlite_error(rc);
        }

        commit();
    }

    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>>
    search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";
        auto deleter = [](sqlite3_stmt* stmt) { sqlite3_finalize(stmt); };
        std::unique_ptr<sqlite3_stmt, decltype(deleter)> stmt_ptr(nullptr, deleter);

        sqlite3_stmt* raw_stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &raw_stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw_sqlite_error(rc);
        }
        stmt_ptr.reset(raw_stmt);

        rc = sqlite3_bind_text(stmt_ptr.get(), 1, customer_name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);

        std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> results;

        while ((rc = sqlite3_step(stmt_ptr.get())) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt_ptr.get(), 0);
            const unsigned char* movie_name = sqlite3_column_text(stmt_ptr.get(), 1);
            const unsigned char* theater_name = sqlite3_column_text(stmt_ptr.get(), 2);
            const unsigned char* seat_number = sqlite3_column_text(stmt_ptr.get(), 3);
            const unsigned char* customer_name_col = sqlite3_column_text(stmt_ptr.get(), 4);

            results.emplace_back(
                id,
                std::string(reinterpret_cast<const char*>(movie_name)),
                std::string(reinterpret_cast<const char*>(theater_name)),
                std::string(reinterpret_cast<const char*>(seat_number)),
                std::string(reinterpret_cast<const char*>(customer_name_col))
            );
        }

        if (rc != SQLITE_DONE) {
            throw_sqlite_error(rc);
        }

        return results;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";
        auto deleter = [](sqlite3_stmt* stmt) { sqlite3_finalize(stmt); };
        std::unique_ptr<sqlite3_stmt, decltype(deleter)> stmt_ptr(nullptr, deleter);

        sqlite3_stmt* raw_stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &raw_stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw_sqlite_error(rc);
        }
        stmt_ptr.reset(raw_stmt);

        rc = sqlite3_bind_int(stmt_ptr.get(), 1, ticket_id);
        if (rc != SQLITE_OK) throw_sqlite_error(rc);

        rc = sqlite3_step(stmt_ptr.get());
        if (rc != SQLITE_DONE) {
            throw_sqlite_error(rc);
        }

        commit();
    }
};