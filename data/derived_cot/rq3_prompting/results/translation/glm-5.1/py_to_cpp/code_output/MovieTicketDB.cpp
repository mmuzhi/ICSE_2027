#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <sqlite3.h>

class MovieTicketDB {
private:
    sqlite3* db;

    void check_error(int rc, const std::string& context) {
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            std::string err_msg = context + ": " + sqlite3_errmsg(db);
            throw std::runtime_error(err_msg);
        }
    }

public:
    MovieTicketDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err_msg = "Can't open database: " + std::string(sqlite3_errmsg(db));
            sqlite3_close(db);
            throw std::runtime_error(err_msg);
        }
        create_table();
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
                           "customer_name TEXT);";
        
        char* err_msg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string error(err_msg);
            sqlite3_free(err_msg);
            throw std::runtime_error("SQL error in create_table: " + error);
        }
    }

    void insert_ticket(const std::string& movie_name, const std::string& theater_name, 
                       const std::string& seat_number, const std::string& customer_name) {
        const char* sql = "INSERT INTO tickets (movie_name, theater_name, seat_number, customer_name) VALUES (?, ?, ?, ?);";
        sqlite3_stmt* stmt;
        
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, "Failed to prepare statement in insert_ticket");

        sqlite3_bind_text(stmt, 1, movie_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, theater_name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, seat_number.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, customer_name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        check_error(rc, "Failed to execute statement in insert_ticket");

        sqlite3_finalize(stmt);
    }

    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> search_tickets_by_customer(const std::string& customer_name) {
        const char* sql = "SELECT * FROM tickets WHERE customer_name = ?;";
        sqlite3_stmt* stmt;
        
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, "Failed to prepare statement in search_tickets_by_customer");

        sqlite3_bind_text(stmt, 1, customer_name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> results;
        
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string movie_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string theater_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string seat_number = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string cust_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            
            results.emplace_back(id, movie_name, theater_name, seat_number, cust_name);
        }
        
        check_error(rc, "Failed to fetch rows in search_tickets_by_customer");

        sqlite3_finalize(stmt);
        return results;
    }

    void delete_ticket(int ticket_id) {
        const char* sql = "DELETE FROM tickets WHERE id = ?;";
        sqlite3_stmt* stmt;
        
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, "Failed to prepare statement in delete_ticket");

        sqlite3_bind_int(stmt, 1, ticket_id);

        rc = sqlite3_step(stmt);
        check_error(rc, "Failed to execute statement in delete_ticket");

        sqlite3_finalize(stmt);
    }
};