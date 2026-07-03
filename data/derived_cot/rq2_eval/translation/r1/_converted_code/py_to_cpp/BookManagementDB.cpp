#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>

class BookManagementDB {
private:
    sqlite3* db;

public:
    BookManagementDB(const std::string& db_name) {
        if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        create_table();
    }

    ~BookManagementDB() {
        sqlite3_close(db);
    }

    void create_table() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                          "id INTEGER PRIMARY KEY,"
                          "title TEXT,"
                          "author TEXT,"
                          "available INTEGER)";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string error = "SQL error: ";
            error += errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error(error);
        }
    }

    void add_book(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_text(stmt, 1, title.c_str(), title.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, author.c_str(), author.length(), SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);

        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void remove_book(int book_id) {
        const char* sql = "DELETE FROM books WHERE id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt, 1, book_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);

        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void borrow_book(int book_id) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt, 1, book_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);

        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void return_book(int book_id) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_bind_int(stmt, 1, book_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);

        if (sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    std::vector<std::tuple<int, std::string, std::string, int>> search_books() {
        const char* sql = "SELECT * FROM books";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        std::vector<std::tuple<int, std::string, std::string, int>> books;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* title = sqlite3_column_text(stmt, 1);
            const unsigned char* author = sqlite3_column_text(stmt, 2);
            int available = sqlite3_column_int(stmt, 3);

            books.emplace_back(
                id,
                std::string(reinterpret_cast<const char*>(title)),
                std::string(reinterpret_cast<const char*>(author)),
                available
            );
        }

        sqlite3_finalize(stmt);
        return books;
    }
};