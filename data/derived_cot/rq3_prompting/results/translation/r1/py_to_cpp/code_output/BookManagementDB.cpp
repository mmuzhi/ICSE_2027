#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>

struct Book {
    int id;
    std::string title;
    std::string author;
    int available;
};

class BookManagementDB {
private:
    sqlite3* db;

    void check_error(int rc, sqlite3* db, const std::string& msg) const {
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            throw std::runtime_error(msg + ": " + sqlite3_errmsg(db));
        }
    }

public:
    BookManagementDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        check_error(rc, db, "Failed to open database");
        create_table();
    }

    ~BookManagementDB() {
        if (db) {
            sqlite3_close(db);
        }
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                          "id INTEGER PRIMARY KEY, "
                          "title TEXT, "
                          "author TEXT, "
                          "available INTEGER"
                          ");";
        char* err_msg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string error = err_msg ? err_msg : "Unknown error";
            sqlite3_free(err_msg);
            throw std::runtime_error("Failed to create table: " + error);
        }
    }

    void add_book(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1);";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, db, "Failed to prepare add_book statement");
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_TRANSIENT);
        rc = sqlite3_step(stmt);
        check_error(rc, db, "Failed to execute add_book");
        sqlite3_finalize(stmt);
    }

    void remove_book(int book_id) {
        const char* sql = "DELETE FROM books WHERE id = ?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, db, "Failed to prepare remove_book statement");
        sqlite3_bind_int(stmt, 1, book_id);
        rc = sqlite3_step(stmt);
        check_error(rc, db, "Failed to execute remove_book");
        sqlite3_finalize(stmt);
    }

    void borrow_book(int book_id) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, db, "Failed to prepare borrow_book statement");
        sqlite3_bind_int(stmt, 1, book_id);
        rc = sqlite3_step(stmt);
        check_error(rc, db, "Failed to execute borrow_book");
        sqlite3_finalize(stmt);
    }

    void return_book(int book_id) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, db, "Failed to prepare return_book statement");
        sqlite3_bind_int(stmt, 1, book_id);
        rc = sqlite3_step(stmt);
        check_error(rc, db, "Failed to execute return_book");
        sqlite3_finalize(stmt);
    }

    std::vector<Book> search_books() {
        const char* sql = "SELECT * FROM books;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        check_error(rc, db, "Failed to prepare search_books statement");
        std::vector<Book> books;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            Book b;
            b.id = sqlite3_column_int(stmt, 0);
            const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            b.title = title ? title : "";
            const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            b.author = author ? author : "";
            b.available = sqlite3_column_int(stmt, 3);
            books.push_back(b);
        }
        if (rc != SQLITE_DONE) {
            check_error(rc, db, "Failed to fetch books");
        }
        sqlite3_finalize(stmt);
        return books;
    }
};