#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>
#include <stdexcept>

class BookManagementDB {
public:
    class Book {
    private:
        int id;
        std::string title;
        std::string author;
        int available;

    public:
        Book(int id, const std::string& title, const std::string& author, int available)
            : id(id), title(title), author(author), available(available) {}

        int getId() const { return id; }
        const std::string& getTitle() const { return title; }
        const std::string& getAuthor() const { return author; }
        int getAvailable() const { return available; }

        std::string toString() const {
            return "Book{id=" + std::to_string(id) +
                   ", title='" + title + '\'' +
                   ", author='" + author + '\'' +
                   ", available=" + std::to_string(available) +
                   '}';
        }
    };

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
        int rc = sqlite3_exec(connection, createTableSQL, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::string err = errMsg ? errMsg : "unknown error";
            sqlite3_free(errMsg);
            throw std::runtime_error("createTable failed: " + err);
        }
    }

public:
    BookManagementDB(const std::string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &connection);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(connection);
            sqlite3_close(connection);
            throw std::runtime_error("Cannot open database: " + err);
        }
        createTable();
    }

    ~BookManagementDB() {
        if (connection) {
            sqlite3_close(connection);
        }
    }

    BookManagementDB(const BookManagementDB&) = delete;
    BookManagementDB& operator=(const BookManagementDB&) = delete;

    void addBook(const std::string& title, const std::string& author) {
        const char* insertSQL = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, insertSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("addBook prepare failed: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_TRANSIENT);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("addBook step failed: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    void removeBook(int bookId) {
        const char* deleteSQL = "DELETE FROM books WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, deleteSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("removeBook prepare failed: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("removeBook step failed: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    void borrowBook(int bookId) {
        const char* updateSQL = "UPDATE books SET available = 0 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, updateSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("borrowBook prepare failed: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("borrowBook step failed: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    void returnBook(int bookId) {
        const char* updateSQL = "UPDATE books SET available = 1 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, updateSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("returnBook prepare failed: " + std::string(sqlite3_errmsg(connection)));
        }
        sqlite3_bind_int(stmt, 1, bookId);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("returnBook step failed: " + std::string(sqlite3_errmsg(connection)));
        }
    }

    std::vector<Book> searchBooks() {
        const char* selectSQL = "SELECT * FROM books";
        std::vector<Book> books;
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(connection, selectSQL, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("searchBooks prepare failed: " + std::string(sqlite3_errmsg(connection)));
        }
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int available = sqlite3_column_int(stmt, 3);
            books.emplace_back(id,
                title ? title : "",
                author ? author : "",
                available);
        }
        sqlite3_finalize(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("searchBooks step failed: " + std::string(sqlite3_errmsg(connection)));
        }
        return books;
    }
};