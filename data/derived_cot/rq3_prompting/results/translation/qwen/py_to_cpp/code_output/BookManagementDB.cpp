#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>

class BookManagementDB {
private:
    sqlite3* db;
    sqlite3_stmt* stmt;

public:
    BookManagementDB(const std::string& db_name) {
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(db)));
        }
        create_table();
    }

    ~BookManagementDB() {
        sqlite3_close(db);
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books (id INTEGER PRIMARY KEY, title TEXT, author TEXT, available INTEGER)";
        char* errmsg = nullptr;
        int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to create table: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to commit after create_table: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
    }

    void add_book(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare insert statement: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Failed to insert book: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to commit after insert: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
    }

    void remove_book(int book_id) {
        const char* sql = "DELETE FROM books WHERE id = ?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare delete statement: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_bind_int(stmt, 1, book_id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Failed to delete book: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to commit after delete: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
    }

    void borrow_book(int book_id) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare borrow statement: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_bind_int(stmt, 1, book_id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Failed to borrow book: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to commit after borrow: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
    }

    void return_book(int book_id) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare return statement: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_bind_int(stmt, 1, book_id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Failed to return book: " + std::string(sqlite3_errmsg(db)));
        }
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "COMMIT", nullptr, nullptr, &errmsg);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to commit after return: " + std::string(errmsg));
        }
        sqlite3_free(errmsg);
    }

    std::vector<std::tuple<int, std::string, std::string, int>> search_books() {
        std::vector<std::tuple<int, std::string, std::string, int>> books;
        const char* sql = "SELECT * FROM books";
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Failed to prepare search statement: " + std::string(sqlite3_errmsg(db)));
        }
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int available = sqlite3_column_int(stmt, 3);
            books.push_back(std::make_tuple(id, title, author, available));
        }
        sqlite3_finalize(stmt);
        return books;
    }
};