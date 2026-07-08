#ifndef BOOK_MANAGEMENT_DB_H
#define BOOK_MANAGEMENT_DB_H

#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

class BookManagementDB {
public:
    class Book {
    private:
        int id_;
        std::string title_;
        std::string author_;
        int available_;

    public:
        Book(int id, const std::string& title, const std::string& author, int available)
            : id_(id), title_(title), author_(author), available_(available) {}

        int getId() const { return id_; }
        const std::string& getTitle() const { return title_; }
        const std::string& getAuthor() const { return author_; }
        int getAvailable() const { return available_; }

        std::string toString() const {
            return "Book{id=" + std::to_string(id_) +
                   ", title='" + title_ + '\'' +
                   ", author='" + author_ + '\'' +
                   ", available=" + std::to_string(available_) +
                   '}';
        }
    };

private:
    sqlite3* connection_;

    // RAII guard for sqlite3_stmt*, mirrors Java's try-with-resources
    class StmtGuard {
    public:
        sqlite3_stmt* stmt;
        explicit StmtGuard(sqlite3_stmt* s) : stmt(s) {}
        ~StmtGuard() { if (stmt) sqlite3_finalize(stmt); }
        StmtGuard(const StmtGuard&) = delete;
        StmtGuard& operator=(const StmtGuard&) = delete;
    };

    void createTable() {
        const char* sql =
            "CREATE TABLE IF NOT EXISTS books ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT, "
            "author TEXT, "
            "available INTEGER"
            ")";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(connection_, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::string msg = errMsg ? errMsg : "unknown error";
            sqlite3_free(errMsg);
            throw std::runtime_error("createTable: " + msg);
        }
    }

public:
    explicit BookManagementDB(const std::string& dbName) : connection_(nullptr) {
        int rc = sqlite3_open(dbName.c_str(), &connection_);
        if (rc != SQLITE_OK) {
            std::string msg = connection_ ? sqlite3_errmsg(connection_) : "cannot open database";
            sqlite3_close(connection_);
            throw std::runtime_error("BookManagementDB: " + msg);
        }
        try {
            createTable();
        } catch (...) {
            sqlite3_close(connection_);
            connection_ = nullptr;
            throw;
        }
    }

    ~BookManagementDB() {
        if (connection_) {
            sqlite3_close(connection_);
        }
    }

    BookManagementDB(const BookManagementDB&) = delete;
    BookManagementDB& operator=(const BookManagementDB&) = delete;

    void addBook(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        sqlite3_stmt* raw = nullptr;
        int rc = sqlite3_prepare_v2(connection_, sql, -1, &raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("addBook: " + std::string(sqlite3_errmsg(connection_)));
        }
        StmtGuard guard(raw);

        rc = sqlite3_bind_text(guard.stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("addBook: " + std::string(sqlite3_errmsg(connection_)));
        }

        rc = sqlite3_bind_text(guard.stmt, 2, author.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("addBook: " + std::string(sqlite3_errmsg(connection_)));
        }

        rc = sqlite3_step(guard.stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("addBook: " + std::string(sqlite3_errmsg(connection_)));
        }
    }

    void removeBook(int bookId) {
        const char* sql = "DELETE FROM books WHERE id = ?";
        sqlite3_stmt* raw = nullptr;
        int rc = sqlite3_prepare_v2(connection_, sql, -1, &raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("removeBook: " + std::string(sqlite3_errmsg(connection_)));
        }
        StmtGuard guard(raw);

        rc = sqlite3_bind_int(guard.stmt, 1, bookId);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("removeBook: " + std::string(sqlite3_errmsg(connection_)));
        }

        rc = sqlite3_step(guard.stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("removeBook: " + std::string(sqlite3_errmsg(connection_)));
        }
    }

    void borrowBook(int bookId) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
        sqlite3_stmt* raw = nullptr;
        int rc = sqlite3_prepare_v2(connection_, sql, -1, &raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("borrowBook: " + std::string(sqlite3_errmsg(connection_)));
        }
        StmtGuard guard(raw);

        rc = sqlite3_bind_int(guard.stmt, 1, bookId);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("borrowBook: " + std::string(sqlite3_errmsg(connection_)));
        }

        rc = sqlite3_step(guard.stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("borrowBook: " + std::string(sqlite3_errmsg(connection_)));
        }
    }

    void returnBook(int bookId) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
        sqlite3_stmt* raw = nullptr;
        int rc = sqlite3_prepare_v2(connection_, sql, -1, &raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("returnBook: " + std::string(sqlite3_errmsg(connection_)));
        }
        StmtGuard guard(raw);

        rc = sqlite3_bind_int(guard.stmt, 1, bookId);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("returnBook: " + std::string(sqlite3_errmsg(connection_)));
        }

        rc = sqlite3_step(guard.stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("returnBook: " + std::string(sqlite3_errmsg(connection_)));
        }
    }

    std::vector<Book> searchBooks() {
        const char* sql = "SELECT * FROM books";
        sqlite3_stmt* raw = nullptr;
        int rc = sqlite3_prepare_v2(connection_, sql, -1, &raw, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("searchBooks: " + std::string(sqlite3_errmsg(connection_)));
        }
        StmtGuard guard(raw);

        std::vector<Book> books;
        while ((rc = sqlite3_step(guard.stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(guard.stmt, 0);
            const char* titleText = reinterpret_cast<const char*>(sqlite3_column_text(guard.stmt, 1));
            const char* authorText = reinterpret_cast<const char*>(sqlite3_column_text(guard.stmt, 2));
            int available = sqlite3_column_int(guard.stmt, 3);

            books.emplace_back(id,
                titleText ? titleText : "",
                authorText ? authorText : "",
                available);
        }

        if (rc != SQLITE_DONE) {
            throw std::runtime_error("searchBooks: " + std::string(sqlite3_errmsg(connection_)));
        }

        return books;
    }
};

#endif // BOOK_MANAGEMENT_DB_H