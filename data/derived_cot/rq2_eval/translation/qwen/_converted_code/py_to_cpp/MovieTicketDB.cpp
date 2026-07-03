#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>

class SQLiteException : public std::runtime_error {
public:
    explicit SQLiteException(const std::string& message) : std::runtime_error(message) {}
};

class MovieTicketDB {
private:
    sqlite3* db;

    void throw_if_error(int rc, const std::string& op) {
        if (rc != SQLITE_OK) {
            const char* errMsg = sqlite3_errmsg(db);
            throw SQLiteException(std::string("SQLite error in ") + op + ": " + errMsg);
        }
    }

public:
    MovieTicketDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw SQLiteException("Failed to open database: " + std::string(sqlite3_errmsg(db)));
        }
    }

    ~MovieTicketDB() {
        if (db) {
            sqlite3_close(db);
        }
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
                           "id INTEGER PRIMARY KEY, "
                           "movie_name TEXT, "
                           "theater_name TEXT, "
                           "seat_number TEXT, "
                           "customer_name TEXT)";
        
        int rc = sqlite3_exec(db, sql, 0, 0, 0);
        throw_if_error(rc, "sqlite3_exec in create_table");
    }

    void insert_ticket(const std::string& movie_name, const std::string& theater_name, const std::string& seat_number, const std::string& customer_name) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";

        int rc = sqlite3_prepare_v2(db, sql, -1, 0, 0);
        throw_if_error(rc, "sqlite3_prepare_v2");

        sqlite3_bind_text(0, movie_name.c_str(), movie_name.size(), SQLITE_TRANSIENT);
        sqlite3_bind_text(1, theater_name.c_str(), theater_name.size(), SQLITE_TRANSIENT);
        sqlite3_bind_text(2, seat_number.c_str(), seat_number.size(), SQLITE_TRANSIENT);
        sqlite3_bind_text(3, customer_name.c_str(), customer_name.size(), SQLITE_TRANSIENT);

        rc = sqlite3_step(0);
        if (rc != SQLITE_DONE) {
            throw_if_error(rc, "sqlite3_step");
        }

        sqlite3_finalize(0);
    }

    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";

        int rc = sqlite3_prepare_v2(db, sql, -1, 0, 0);
        throw_if_error(rc, "sqlite3_prepare_v2");

        sqlite3_bind_text(0, customer_name.c_str(), customer_name.size(), SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> result;
        while (1) {
            rc = sqlite3_step(0);
            if (rc == SQLITE_ROW) {
                int id = sqlite3_column_int(0);
                const char* movie_name = reinterpret_cast<const char*>(sqlite3_column_text(0));
                const char* theater_name = reinterpret_cast<const char*>(sqlite3_column_text(1));
                const char* seat_number = reinterpret_cast<const char*>(sqlite3_column_text(2));
                const char* customer = reinterpret_cast<const char*>(sqlite3_column_text(3));

                result.push_back(std::make_tuple(
                    id,
                    std::string(movie_name, movie_name + sqlite3_column_bytes(0)),
                    std::string(theater_name, theater_name + sqlite3_column_bytes(1)),
                    std::string(seat_number, seat_number + sqlite3_column_bytes(2)),
                    std::string(customer, customer + sqlite3_column_bytes(3))
                ));
            } else if (rc == SQLITE_DONE) {
                break;
            } else {
                throw_if_error(rc, "sqlite3_step");
            }
        }

        sqlite3_finalize(0);
        return result;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";

        int rc = sqlite3_prepare_v2(db, sql, -1, 0, 0);
        throw_if_error(rc, "sqlite3_prepare_v2");

        sqlite3_bind_int(0, ticket_id);

        rc = sqlite3_step(0);
        if (rc != SQLITE_DONE) {
            throw_if_error(rc, "sqlite3_step");
        }

        sqlite3_finalize(0);
    }
};