#include <sqlite3.h>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

// Custom deleter for sqlite3* (connection)
struct ConnectionDeleter {
    void operator()(sqlite3* ptr) const {
        if (ptr) {
            sqlite3_close(ptr);
        }
    }
};

// Custom deleter for sqlite3_stmt* (statement)
struct StatementDeleter {
    void operator()(sqlite3_stmt* ptr) const {
        if (ptr) {
            sqlite3_finalize(ptr);
        }
    }
};

class MovieTicketDB {
private:
    std::unique_ptr<sqlite3, ConnectionDeleter> connection;
    std::unique_ptr<sqlite3_stmt, StatementDeleter> cursor;

public:
    MovieTicketDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), connection.get());
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }
        create_table();
    }

    ~MovieTicketDB() = default;

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
            "id INTEGER PRIMARY KEY, "
            "movie_name TEXT, "
            "theater_name TEXT, "
            "seat_number TEXT, "
            "customer_name TEXT)";
        char* errorMsg;
        if (sqlite3_exec(connection.get(), sql, nullptr, nullptr, &errorMsg) != SQLITE_OK) {
            if (errorMsg) {
                std::cerr << "SQL error: " << errorMsg << std::endl;
                sqlite3_free(errorMsg);
            }
        }
        sqlite3_exec(connection.get(), "COMMIT", nullptr, nullptr, nullptr);
    }

    void insert_ticket(const std::string& movie_name, const std::string& theater_name, const std::string& seat_number, const std::string& customer_name) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";

        // Prepare the statement
        int rc = sqlite3_prepare_v2(connection.get(), sql, -1, cursor.get(), nullptr);
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }

        // Bind parameters
        sqlite3_bind_text(cursor.get(), 1, movie_name.c_str(), movie_name.size(), SQLITE_STATIC);
        sqlite3_bind_text(cursor.get(), 2, theater_name.c_str(), theater_name.size(), SQLITE_STATIC);
        sqlite3_bind_text(cursor.get(), 3, seat_number.c_str(), seat_number.size(), SQLITE_STATIC);
        sqlite3_bind_text(cursor.get(), 4, customer_name.c_str(), customer_name.size(), SQLITE_STATIC);

        // Execute
        if (sqlite3_step(cursor.get()) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }

        // Finalize the statement
        sqlite3_finalize(cursor.release());
        sqlite3_exec(connection.get(), "COMMIT", nullptr, nullptr, nullptr);
    }

    std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";

        // Prepare the statement
        int rc = sqlite3_prepare_v2(connection.get(), sql, -1, cursor.get(), nullptr);
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }

        // Bind parameter
        sqlite3_bind_text(cursor.get(), 1, customer_name.c_str(), customer_name.size(), SQLITE_STATIC);

        // Execute and fetch results
        std::vector<std::tuple<std::string, std::string, std::string, std::string, std::string>> tickets;
        if (sqlite3_step(cursor.get()) == SQLITE_ROW) {
            do {
                int id = sqlite3_column_int(cursor.get(), 0);
                const char* movie_name = reinterpret_cast<const char*>(sqlite3_column_text(cursor.get(), 1));
                const char* theater_name = reinterpret_cast<const char*>(sqlite3_column_text(cursor.get(), 2));
                const char* seat_number = reinterpret_cast<const char*>(sqlite3_column_text(cursor.get(), 3));
                const char* customer_name = reinterpret_cast<const char*>(sqlite3_column_text(cursor.get(), 4));

                // Convert each column to string
                std::string row_id = std::to_string(id);
                std::string row_movie(movie_name);
                std::string row_theater(theater_name);
                std::string row_seat(seat_number);
                std::string row_customer(customer_name);

                tickets.push_back(std::make_tuple(row_id, row_movie, row_theater, row_seat, row_customer));
            } while (sqlite3_step(cursor.get()) == SQLITE_ROW);
        }

        // Finalize the statement
        sqlite3_finalize(cursor.release());
        // No commit needed for SELECT

        return tickets;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";

        // Prepare the statement
        int rc = sqlite3_prepare_v2(connection.get(), sql, -1, cursor.get(), nullptr);
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }

        // Bind parameter
        sqlite3_bind_int(cursor.get(), 1, ticket_id);

        // Execute
        if (sqlite3_step(cursor.get()) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(connection.get()));
        }

        // Finalize the statement
        sqlite3_finalize(cursor.release());
        sqlite3_exec(connection.get(), "COMMIT", nullptr, nullptr, nullptr);
    }
};