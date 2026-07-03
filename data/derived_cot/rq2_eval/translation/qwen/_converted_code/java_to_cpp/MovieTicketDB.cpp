#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

class MovieTicketDB {
private:
    sqlite3* db;

    void print_error(sqlite3* db, const char* msg) {
        if (db) {
            std::cerr << msg << " " << sqlite3_errmsg(db) << std::endl;
        } else {
            std::cerr << msg << std::endl;
        }
    }

public:
    MovieTicketDB(const std::string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            print_error(db, "Cannot open database");
            db = nullptr;
        }
        create_table();
    }

    ~MovieTicketDB() {
        close_connection();
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "movie_name TEXT, "
            "theater_name TEXT, "
            "seat_number TEXT, "
            "customer_name TEXT)";
        
        if (!db) return;

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc == SQLITE_OK) {
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        } else {
            print_error(db, "CREATE TABLE failed");
        }
    }

    void insert_ticket(const std::string& movieName, const std::string& theaterName, const std::string& seatNumber, const std::string& customerName) {
        if (!db) return;

        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_error(db, "Failed to prepare insert statement");
            return;
        }

        sqlite3_bind_text(stmt, 1, movieName.c_str(), movieName.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, theaterName.c_str(), theaterName.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, seatNumber.c_str(), seatNumber.size(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, customerName.c_str(), customerName.size(), SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            print_error(db, "Insert failed");
        }

        sqlite3_finalize(stmt);
    }

    std::vector<Ticket> searchTicketsByCustomer(const std::string& customerName) {
        if (!db) return {};

        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_error(db, "Failed to prepare search statement");
            return {};
        }

        sqlite3_bind_text(stmt, 1, customerName.c_str(), customerName.size(), SQLITE_STATIC);

        std::vector<Ticket> tickets;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* movieName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* theaterName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            const char* seatNumber = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            const char* customerNameCol = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

            tickets.push_back(Ticket(id, movieName, theaterName, seatNumber, customerNameCol));
        }

        if (rc != SQLITE_DONE) {
            print_error(db, "Search failed");
        }

        sqlite3_finalize(stmt);
        return tickets;
    }

    void delete_ticket(int ticketId) {
        if (!db) return;

        const char* sql = "DELETE FROM tickets WHERE id = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            print_error(db, "Failed to prepare delete statement");
            return;
        }

        sqlite3_bind_int(stmt, 1, ticketId);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            print_error(db, "Delete failed");
        }

        sqlite3_finalize(stmt);
    }

    void close_connection() {
        if (db) {
            int rc = sqlite3_close(db);
            if (rc != SQLITE_OK && rc != SQLITE_BUSY) {
                std::cerr << "Failed to close database properly" << std::endl;
            }
            db = nullptr;
        }
    }

    struct Ticket {
        int id;
        std::string movieName;
        std::string theaterName;
        std::string seatNumber;
        std::string customerName;

        Ticket(int id, const char* movieName, const char* theaterName, const char* seatNumber, const char* customerName)
            : id(id), 
              movieName(movieName),
              theaterName(theaterName),
              seatNumber(seatNumber),
              customerName(customerName) {}

        Ticket(int id, const std::string& movieName, const std::string& theaterName, const std::string& seatNumber, const std::string& customerName)
            : id(id), 
              movieName(movieName),
              theaterName(theaterName),
              seatNumber(seatNumber),
              customerName(customerName) {}
    };
};

int main() {
    // Example usage
    MovieTicketDB db("tickets.db");
    db.insert_ticket("Inception", "Regal", "A1", "Alice");
    auto tickets = db.searchTicketsByCustomer("Alice");
    for (const auto& ticket : tickets) {
        std::cout << "Ticket ID: " << ticket.id << ", Movie: " << ticket.movieName << std::endl;
    }
    db.delete_ticket(1);
    return 0;
}