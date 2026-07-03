#include <string>
#include <vector>
#include <tuple>
#include <sqlite3.h>
#include <stdexcept>

class MovieTicketDB {
private:
    sqlite3* connection;

public:
    MovieTicketDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &connection);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(connection);
            sqlite3_close(connection);
            throw std::runtime_error("Failed to open database: " + err);
        }
        create_table();
    }

    ~MovieTicketDB() {
        if (connection) {
            sqlite3_close(connection);
        }
    }

    // Disable copy to match Python's non-copyable connection behavior
    MovieTicketDB(const MovieTicketDB&) = delete;
    MovieTicketDB& operator=(const MovieTicketDB&) = delete;

    void create_table() {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS tickets ("
            "id INTEGER PRIMARY KEY,"
            "movie_name TEXT,"
            "theater_name TEXT,"
            "seat_number TEXT,"
            "customer_name TEXT"
            ")";

        char* err_msg = nullptr;
        int rc = sqlite3_exec(connection, sql, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string err(err_msg);
            sqlite3_free(err_msg);
            throw std::runtime_error("Failed to create table: " + err);
        }
    }

    void insert_ticket(const std::string& movie_name, const std::string& theater_name,
                       const std::string& seat_number, const std::string& customer_name) {
        const char* sql =
            "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) "
            "VALUES (?, ?, ?, ?)";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }

        sqlite3_bind_text(stmt, 1, movie_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, theater_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, seat_number.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, customer_name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE) {
            throw std::runtime_error("Failed to insert ticket: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>>
    search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }

        sqlite3_bind_text(stmt, 1, customer_name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> tickets;

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string movie_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string theater_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            std::string seat_number(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            std::string cust_name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));

            tickets.emplace_back(id, std::move(movie_name), std::move(theater_name),
                                 std::move(seat_number), std::move(cust_name));
        }

        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE) {
            throw std::runtime_error("Failed to fetch tickets: " + std::string(sqlite3_errmsg(connection)));
        }

        return tickets;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }

        sqlite3_bind_int(stmt, 1, ticket_id);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (rc != SQLITE_DONE) {
            throw std::runtime_error("Failed to delete ticket: " + std::string(sqlite3_errmsg(connection)));
        }
    }
};