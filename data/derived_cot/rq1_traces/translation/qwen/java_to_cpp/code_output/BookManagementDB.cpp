#include <sqlite3.h>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>

class BookManagementDB {
public:
    class Book {
    public:
        int id;
        std::string title;
        std::string author;
        int available;

        Book(int id, const std::string& title, const std::string& author, int available)
            : id(id), title(title), author(author), available(available) {}

        friend std::ostream& operator<<(std::ostream& os, const Book& book) {
            return os << "Book{" << "id=" << book.id
                     << ", title='" << book.title << '\''
                     << ", author='" << book.author << '\''
                     << ", available=" << book.available << '}';
        }
    };

    explicit BookManagementDB(const std::string& dbName)
        : db(nullptr), error_message(nullptr) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Cannot open database");
        }
        createTable();
    }

    ~BookManagementDB() {
        if (db) {
            sqlite3_close(db);
        }
        if (error_message) {
            sqlite3_free(error_message);
        }
    }

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "title TEXT, "
                          "author TEXT, "
                          "available INTEGER)";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            error_message = errMsg;
            throw std::runtime_error("Failed to create table");
        }
    }

    void addBook(const std::string& title, const std::string& author) {
        const char* sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to prepare statement");
        }

        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to insert book");
        }

        sqlite3_finalize(stmt);
    }

    void removeBook(int bookId) {
        const char* sql = "DELETE FROM books WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to prepare statement");
        }

        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to delete book");
        }

        sqlite3_finalize(stmt);
    }

    void borrowBook(int bookId) {
        const char* sql = "UPDATE books SET available = 0 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to prepare statement");
        }

        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to borrow book");
        }

        sqlite3_finalize(stmt);
    }

    void returnBook(int bookId) {
        const char* sql = "UPDATE books SET available = 1 WHERE id = ?";
        sqlite3_stmt* stmt = nullptr;
        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to prepare statement");
        }

        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to return book");
        }

        sqlite3_finalize(stmt);
    }

    std::vector<Book> searchBooks() {
        const char* sql = "SELECT * FROM books";
        std::vector<Book> books;
        sqlite3_stmt* stmt = nullptr;

        int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            error_message = sqlite3_errmsg(db);
            throw std::runtime_error("Failed to prepare statement");
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* title = sqlite3_column_text(stmt, 1);
            const char* author = sqlite3_column_text(stmt, 2);
            int available = sqlite3_column_int(stmt, 3);
            books.emplace_back(id, title ? std::string(title) : "", author ? std::string(author) : "", available);
        }

        sqlite3_finalize(stmt);
        return books;
    }

private:
    sqlite3* db;
    char* error_message;
};

// Example usage
int main() {
    try {
        BookManagementDB db("books.db");
        db.addBook("The C++ Programming Language", "Bjarne Stroustrup");
        auto books = db.searchBooks();
        for (const auto& book : books) {
            std::cout << book << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}