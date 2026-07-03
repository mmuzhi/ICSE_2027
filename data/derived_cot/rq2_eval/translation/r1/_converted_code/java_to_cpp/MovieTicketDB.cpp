#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <string>

class MovieTicketDB {
public:
    struct Ticket {
        int id;
        std::string movieName;
        std::string theaterName;
        std::string seatNumber;
        std::string customerName;

        Ticket(int id, const std::string& movieName, const std::string& theaterName,
               const std::string& seatNumber, const std::string& customerName)
            : id(id), movieName(movieName), theaterName(theaterName),
              seatNumber(seatNumber), customerName(customerName) {}

        int getId() const { return id; }
        std::string getMovieName() const { return movieName; }
        std::string getTheaterName() const { return theaterName; }
        std::string getSeatNumber() const { return seatNumber; }
        std::string getCustomerName() const { return customerName; }
    };

    MovieTicketDB(const std::string& dbName) : db(nullptr) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            db = nullptr;
            return;
        }
        create_table();
    }

    ~MovieTicketDB() {
        close_connection();
    }

    void close_connection() {
        if (db) {
            if (sqlite3_close(db) != SQLITE_OK) {
                std::cerr << "Failed to close database: " << sqlite3_errmsg(db) << std::endl;
            }
            db = nullptr;
        }
    }

    void insert_ticket(const std::string& movieName, const std::string& theaterName,
                      const std::string& seatNumber, const std::string& customerName) {
        if (!db) return;

        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_text(stmt, 1, movieName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, theaterName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, seatNumber.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, customerName.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

    std::vector<Ticket> searchTicketsByCustomer(const std::string& customerName) {
        std::vector<Ticket> tickets;
        if (!db) return tickets;

        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";
        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return tickets;
        }

        sqlite3_bind_text(stmt, 1, customerName.c_str(), -1, SQLITE_STATIC);

        int rc;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* movie = sqlite3_column_text(stmt, 1);
            const unsigned char* theater = sqlite3_column_text(stmt, 2);
            const unsigned char* seat = sqlite3_column_text(stmt, 3);
            const unsigned char* customer = sqlite3_column_text(stmt, 4);

            tickets.emplace_back(id,
                std::string(reinterpret_cast<const char*>(movie)),
                std::string(reinterpret_cast<const char*>(theater)),
                std::string(reinterpret_cast<const char*>(seat)),
                std::string(reinterpret_cast<const char*>(customer)));
        }

        if (rc != SQLITE_DONE) {
            std::cerr << "Error during query: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        return tickets;
    }

    void delete_ticket(int ticketId) {
        if (!db) return;

        const char* sql = "DELETE FROM tickets WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        sqlite3_bind_int(stmt, 1, ticketId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
    }

private:
    sqlite3* db;

    void create_table() {
        if (!db) return;

        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "movie_name TEXT, "
            "theater_name TEXT, "
            "seat_number TEXT, "
            "customer_name TEXT)";
        char* errMsg = nullptr;

        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
};