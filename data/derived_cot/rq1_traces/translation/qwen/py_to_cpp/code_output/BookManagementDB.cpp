#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <memory>

class BookManagementDB {
public:
    BookManagementDB(const std::string& db_name);
    ~BookManagementDB();

    void create_table();
    void add_book(const std::string& title, const std::string& author);
    void remove_book(int book_id);
    void borrow_book(int book_id);
    void return_book(int book_id);
    std::vector<std::tuple<int, std::string, std::string, int>> search_books();

private:
    sqlite3* db;
    sqlite3_stmt* stmt;
};

BookManagementDB::BookManagementDB(const std::string& db_name)
    : db(nullptr), stmt(nullptr) {
    int rc = sqlite3_open(db_name.c_str(), &db);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Cannot open database: " + std::string(sqlite3_errmsg(db)));
    }

    create_table();
}

BookManagementDB::~BookManagementDB() {
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }
}

void BookManagementDB::create_table() {
    const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                      "id INTEGER PRIMARY KEY,"
                      "title TEXT,"
                      "author TEXT,"
                      "available INTEGER)";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        if (errMsg) {
            throw std::runtime_error("SQL error: " + std::string(errMsg));
            sqlite3_free(errMsg);
        } else {
            throw std::runtime_error("SQL error but no message");
        }
    }
}

void BookManagementDB::add_book(const std::string& title, const std::string& author) {
    const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare INSERT statement: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute INSERT: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
}

void BookManagementDB::remove_book(int book_id) {
    const char* sql = "DELETE FROM books WHERE id = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare DELETE statement: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_int(stmt, 1, book_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute DELETE: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
}

void BookManagementDB::borrow_book(int book_id) {
    const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare UPDATE statement: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_int(stmt, 1, book_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute UPDATE: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
}

void BookManagementDB::return_book(int book_id) {
    const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare UPDATE statement: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_bind_int(stmt, 1, book_id);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        throw std::runtime_error("Failed to execute UPDATE: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);
}

std::vector<std::tuple<int, std::string, std::string, int>> BookManagementDB::search_books() {
    const char* sql = "SELECT * FROM books";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        throw std::runtime_error("Failed to prepare SELECT statement: " + std::string(sqlite3_errmsg(db)));
    }

    std::vector<std::tuple<int, std::string, std::string, int>> books;
    while (SQLITE_ROW == sqlite3_step(stmt)) {
        int id = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int available = sqlite3_column_int(stmt, 3);

        books.emplace_back(id, title, author, available);
    }

    sqlite3_clear_bindings(stmt);
    sqlite3_reset(stmt);

    return books;
}