#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <sqlite3.h>

class BookManagementDB {
private:
    sqlite3* connection;

    // Helper to execute simple statements with one integer parameter
    void execute_with_int_param(const char* sql, int param) {
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        
        sqlite3_bind_int(stmt, 1, param);
        
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to execute statement: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_finalize(stmt);
    }

    // Helper to execute simple statements with two string parameters
    void execute_with_string_params(const char* sql, const std::string& param1, const std::string& param2) {
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        
        sqlite3_bind_text(stmt, 1, param1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, param2.c_str(), -1, SQLITE_TRANSIENT);
        
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to execute statement: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_finalize(stmt);
    }

public:
    BookManagementDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &connection);
        if (rc != SQLITE_OK) {
            std::string err_msg = "Cannot open database: " + std::string(sqlite3_errmsg(connection));
            sqlite3_close(connection);
            throw std::runtime_error(err_msg);
        }
        create_table();
    }

    ~BookManagementDB() {
        if (connection) {
            sqlite3_close(connection);
        }
    }

    // Disable copy constructor and assignment operator to prevent double-free of the connection
    BookManagementDB(const BookManagementDB&) = delete;
    BookManagementDB& operator=(const BookManagementDB&) = delete;

    // Enable move semantics
    BookManagementDB(BookManagementDB&& other) noexcept : connection(other.connection) {
        other.connection = nullptr;
    }

    BookManagementDB& operator=(BookManagementDB&& other) noexcept {
        if (this != &other) {
            if (connection) {
                sqlite3_close(connection);
            }
            connection = other.connection;
            other.connection = nullptr;
        }
        return *this;
    }

    void create_table() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS books (
                id INTEGER PRIMARY KEY,
                title TEXT,
                author TEXT,
                available INTEGER
            )
        )";
        
        char* err_msg = nullptr;
        int rc = sqlite3_exec(connection, sql, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string err_str = err_msg;
            sqlite3_free(err_msg);
            throw std::runtime_error("SQL error: " + err_str);
        }
    }

    void add_book(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        execute_with_string_params(sql, title, author);
    }

    void remove_book(int book_id) {
        const char* sql = "DELETE FROM books WHERE id = ?";
        execute_with_int_param(sql, book_id);
    }

    void borrow_book(int book_id) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
        execute_with_int_param(sql, book_id);
    }

    void return_book(int book_id) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
        execute_with_int_param(sql, book_id);
    }

    std::vector<std::tuple<int, std::string, std::string, int>> search_books() {
        const char* sql = "SELECT * FROM books";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(connection, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare statement: " + std::string(sqlite3_errmsg(connection)));
        }
        
        std::vector<std::tuple<int, std::string, std::string, int>> books;
        
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            
            const char* title_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string title = title_ptr ? title_ptr : "";
            
            const char* author_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string author = author_ptr ? author_ptr : "";
            
            int available = sqlite3_column_int(stmt, 3);
            
            books.emplace_back(id, title, author, available);
        }
        
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Failed to fetch data: " + std::string(sqlite3_errmsg(connection)));
        }
        
        sqlite3_finalize(stmt);
        return books;
    }
};