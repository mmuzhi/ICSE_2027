#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>

class MovieTicketDB {
private:
    struct Connection {
        sqlite3* db;
        Connection(const std::string& dbName) : db(nullptr) {
            int rc = sqlite3_open(dbName.c_str(), &db);
            if (rc != SQLITE_OK) {
                throw std::runtime_error("Unable to open database: " + std::string(sqlite3_errmsg(db)));
            }
        }
        ~Connection() {
            if (db) sqlite3_close(db);
        }
        operator sqlite3*&() { return db; }
        sqlite3* get() const { return db; }
    };

    struct Statement {
        sqlite3_stmt* stmt;
        Statement(sqlite3* db, const std::string& sql) {
            int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
            }
        }
        ~Statement() {
            if (stmt) sqlite3_finalize(stmt);
        }
        int execute() {
            int rc = sqlite3_step(stmt);
            if (rc == SQLITE_DONE || rc == SQLITE_ROW) {
                return rc;
            }
            throw std::runtime_error("Statement execution error: " + std::string(sqlite3_errmsg(db)));
        }
        operator sqlite3_stmt*&() { return stmt; }
    };

    struct PreparedStatement : Statement {
        PreparedStatement(sqlite3* db, const std::string& sql)
            : Statement(db, sql) {}
        void bind(int index, const std::string& value) {
            sqlite3_bind_text(operator sqlite3_stmt*&, index, value.c_str(), 
                             static_cast<int>(value.size()), SQLITE_TRANSIENT);
        }
        void bind(int index, int value) {
            sqlite3_bind_int(operator sqlite3_stmt*&, index, value);
        }
    };

    std::unique_ptr<Connection> conn;

    void createTable() {
        const std::string sql = R"(
            CREATE TABLE IF NOT EXISTS tickets (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                movie_name TEXT,
                theater_name TEXT,
                seat_number TEXT,
                customer_name TEXT
            )
        )";
        try (Statement stmt{conn->get(), sql}) {
            stmt.execute();
        }
    }

public:
    MovieTicketDB(const std::string& dbName) : conn(std::make_unique<Connection>(dbName)) {
        try {
            createTable();
        } catch (const std::exception& e) {
            std::cerr << "Error creating table: " << e.what() << std::endl;
        }
    }

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
    };

    void insertTicket(const std::string& movieName, const std::string& theaterName,
                     const std::string& seatNumber, const std::string& customerName) {
        const std::string sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?)";
        try (PreparedStatement pstmt{conn->get(), sql}) {
            pstmt.bind(1, movieName);
            pstmt.bind(2, theaterName);
            pstmt.bind(3, seatNumber);
            pstmt.bind(4, customerName);
            pstmt.execute();
        } catch (const std::exception& e) {
            std::cerr << "Error inserting ticket: " << e.what() << std::endl;
        }
    }

    std::vector<Ticket> searchTicketsByCustomer(const std::string& customerName) {
        const std::string sql = "SELECT * FROM tickets WHERE customer_name = ?";
        std::vector<Ticket> tickets;
        try (PreparedStatement pstmt{conn->get(), sql}) {
            pstmt.bind(1, customerName);
            pstmt.execute();
            while (sqlite3_step(pstmt.operator sqlite3_stmt*&) == SQLITE_ROW) {
                int id = sqlite3_column_int(pstmt.operator sqlite3_stmt*&, 0);
                const char* movie = sqlite3_column_text(pstmt.operator sqlite3_stmt*&, 1);
                const char* theater = sqlite3_column_text(pstmt.operator sqlite3_stmt*&, 2);
                const char* seat = sqlite3_column_text(pstmt.operator sqlite3_stmt*&, 3);
                const char* cust = sqlite3_column_text(pstmt.operator sqlite3_stmt*&, 4);
                tickets.push_back(Ticket(id, 
                                         movie ? movie : "", 
                                         theater ? theater : "", 
                                         seat ? seat : "", 
                                         cust ? cust : ""));
            }
        } catch (const std::exception& e) {
            std::cerr << "Error searching tickets: " << e.what() << std::endl;
        }
        return tickets;
    }

    void deleteTicket(int ticketId) {
        const std::string sql = "DELETE FROM tickets WHERE id = ?";
        try (PreparedStatement pstmt{conn->get(), sql}) {
            pstmt.bind(1, ticketId);
            pstmt.execute();
        } catch (const std::exception& e) {
            std::cerr << "Error deleting ticket: " << e.what() << std::endl;
        }
    }

    void close() {
        // Connection is automatically closed by the destructor
    }
};