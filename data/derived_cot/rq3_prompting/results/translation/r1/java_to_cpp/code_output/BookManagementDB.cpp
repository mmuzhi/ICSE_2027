#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>

class BookManagementDB {
private:
    sqlite3* connection;

    void createTable() {
        const char* createTableSQL =
            "CREATE TABLE IF NOT EXISTS books ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT, "
            "author TEXT, "
            "available INTEGER"
            ")";
        char* errMsg = nullptr;
        if (sqlite3_exec(connection, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string error(errMsg);
            sqlite3_free(errMsg);
            throw std::runtime_error("Create table failed: " + error);
        }
    }

public:
    BookManagementDB(const std::string& dbName) {
        if (sqlite3_open(dbName.c_str(), &connection) != SQLITE_OK) {
            std::string error = sqlite3_errmsg(connection);
            sqlite3_close(connection);
            throw std::runtime_error("Cannot open database: " + error);
        }
        createTable();
    }

    ~BookManagementDB() {
        if (connection) {
            sqlite3_close(connection);
        }
    }

    // Non-copyable, non-movable because sqlite3* is a raw pointer we manage.
    BookManagementDB(const BookManagementDB&) = delete;
    BookManagementDB& operator=(const BookManagementDB&) = delete;

    void addBook(const std::string& title, const std::string& author) {
        const char* insertSQL = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection));
        }
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::string error = sqlite3_errmsg(connection);
            sqlite3_finalize(stmt);
            throw std::runtime_error("Insert failed: " + error);
        }
        sqlite3_finalize(stmt);
    }

    void removeBook(int bookId) {
        const char* deleteSQL = "DELETE FROM books WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, deleteSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::string error = sqlite3_errmsg(connection);
            sqlite3_finalize(stmt);
            throw std::runtime_error("Delete failed: " + error);
        }
        sqlite3_finalize(stmt);
    }

    void borrowBook(int bookId) {
        const char* updateSQL = "UPDATE books SET available = 0 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, updateSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::string error = sqlite3_errmsg(connection);
            sqlite3_finalize(stmt);
            throw std::runtime_error("Borrow failed: " + error);
        }
        sqlite3_finalize(stmt);
    }

    void returnBook(int bookId) {
        const char* updateSQL = "UPDATE books SET available = 1 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, updateSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::string error = sqlite3_errmsg(connection);
            sqlite3_finalize(stmt);
            throw std::runtime_error("Return failed: " + error);
        }
        sqlite3_finalize(stmt);
    }

    struct Book {
        int id;
        std::string title;
        std::string author;
        int available;

        Book(int id, const std::string& title, const std::string& author, int available)
            : id(id), title(title), author(author), available(available) {}

        std::string toString() const {
            std::ostringstream oss;
            oss << "Book{id=" << id
                << ", title='" << title << '\''
                << ", author='" << author << '\''
                << ", available=" << available << '}';
            return oss.str();
        }
    };

    std::vector<Book> searchBooks() {
        const char* selectSQL = "SELECT * FROM books";
        sqlite3_stmt* stmt = nullptr;
        if (sqlite3_prepare_v2(connection, selectSQL, -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(connection));
        }
        std::vector<Book> books;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* titleText = sqlite3_column_text(stmt, 1);
            const unsigned char* authorText = sqlite3_column_text(stmt, 2);
            int available = sqlite3_column_int(stmt, 3);
            std::string title = titleText ? reinterpret_cast<const char*>(titleText) : "";
            std::string author = authorText ? reinterpret_cast<const char*>(authorText) : "";
            books.emplace_back(id, title, author, available);
        }
        sqlite3_finalize(stmt);
        return books;
    }
};