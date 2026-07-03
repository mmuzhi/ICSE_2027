#ifndef MOVIE_TICKET_DB_H
#define MOVIE_TICKET_DB_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

class MovieTicketDB {
public:
    class Ticket {
    private:
        int id;
        std::string movieName;
        std::string theaterName;
        std::string seatNumber;
        std::string customerName;

    public:
        Ticket(int id, const std::string& movieName, const std::string& theaterName,
               const std::string& seatNumber, const std::string& customerName)
            : id(id), movieName(movieName), theaterName(theaterName),
              seatNumber(seatNumber), customerName(customerName) {}

        int getId() const { return id; }
        const std::string& getMovieName() const { return movieName; }
        const std::string& getTheaterName() const { return theaterName; }
        const std::string& getSeatNumber() const { return seatNumber; }
        const std::string& getCustomerName() const { return customerName; }
    };

private:
    sqlite3* connection;

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS tickets ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "movie_name TEXT, "
                "theater_name TEXT, "
                "seat_number TEXT, "
                "customer_name TEXT)";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(connection, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << (errMsg ? errMsg : "unknown error") << std::endl;
            sqlite3_free(errMsg);
        }
    }

    static std::string columnText(sqlite3_stmt* stmt, int col) {
        const unsigned char* text = sqlite3_column_text(stmt, col);
        return text ? reinterpret_cast<const char*>(text) : std::string();
    }

public:
    MovieTicketDB(const std::string& dbName) : connection(nullptr) {
        int rc = sqlite3_open(dbName.c_str(), &connection);
        if (rc != SQLITE_OK) {
            std::cerr << (connection ? sqlite3_errmsg(connection) : "failed to open database") << std::endl;
            if (connection) {
                sqlite3_close(connection);
                connection = nullptr;
            }
        } else {
            createTable();
        }
    }

    void insertTicket(const std::string& movieName, const std::string& theaterName,
                      const std::string& seatNumber, const std::string& customerName) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return;
        }
        sqlite3_bind_text(stmt, 1, movieName.c_str(), static_cast<int>(movieName.size()), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, theaterName.c_str(), static_cast<int>(theaterName.size()), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, seatNumber.c_str(), static_cast<int>(seatNumber.size()), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, customerName.c_str(), static_cast<int>(customerName.size()), SQLITE_TRANSIENT);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    std::vector<Ticket> searchTicketsByCustomer(const std::string& customerName) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?";
        std::vector<Ticket> tickets;
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return tickets;
        }
        sqlite3_bind_text(stmt, 1, customerName.c_str(), static_cast<int>(customerName.size()), SQLITE_TRANSIENT);
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            tickets.emplace_back(
                sqlite3_column_int(stmt, 0),
                columnText(stmt, 1),
                columnText(stmt, 2),
                columnText(stmt, 3),
                columnText(stmt, 4)
            );
        }
        if (rc != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        sqlite3_finalize(stmt);
        return tickets;
    }

    void deleteTicket(int ticketId) {
        const char* sql = "DELETE FROM tickets WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
            return;
        }
        sqlite3_bind_int(stmt, 1, ticketId);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << sqlite3_errmsg(connection) << std::endl;
        }
        sqlite3_finalize(stmt);
    }

    void close() {
        if (connection != nullptr) {
            sqlite3_close(connection);
            connection = nullptr;
        }
    }

    ~MovieTicketDB() {
        close();
    }
};

#endif // MOVIE_TICKET_DB_H