#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>

class SQLException : public std::runtime_error {
public:
    explicit SQLException(const std::string& message) : std::runtime_error(message) {}
};

class BookManagementDB {
private:
    struct DatabaseHandle {
        sqlite3* db;
        DatabaseHandle(const std::string& dbName) {
            int rc = sqlite3_open(dbName.c_str(), &db);
            if (rc != SQLITE_OK) {
                throw SQLException("Cannot open database: " + std::string(sqlite3_errmsg(db)));
            }
        }
        ~DatabaseHandle() {
            if (db) sqlite3_close(db);
        }
        operator sqlite3*() { return db; }
    };

    struct Statement {
        sqlite3_stmt* stmt;
        DatabaseHandle& db;
        Statement(sqlite3_stmt* stmt, DatabaseHandle& db) : stmt(stmt), db(db) {}
        ~Statement() {
            if (stmt) sqlite3_finalize(stmt);
        }
        operator sqlite3_stmt*() { return stmt; }
    };

    DatabaseHandle db;

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "title TEXT, "
                         "author TEXT, "
                         "available INTEGER)";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            throw SQLException(errMsg ? std::string(errMsg) : "Failed to create table");
            sqlite3_free(errMsg);
        }
    }

    Statement prepare(const std::string& sql) {
        Statement stmt(sqlite3_prepare_v2(db, sql.c_str(), -1, nullptr, nullptr), db);
        if (stmt.stmt == nullptr) {
            throw SQLException(sqlite3_errmsg(db));
        }
        return stmt;
    }

public:
    BookManagementDB(const std::string& dbName) : db(dbName) {
        createTable();
    }

    ~BookManagementDB() = default;

    void addBook(const std::string& title, const std::string& author) {
        auto stmt = prepare("INSERT INTO books (title, author, available) VALUES (?, ?, 1)");
        sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db));
        }
    }

    void removeBook(int bookId) {
        auto stmt = prepare("DELETE FROM books WHERE id = ?");
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db));
        }
    }

    void borrowBook(int bookId) {
        auto stmt = prepare("UPDATE books SET available = 0 WHERE id = ?");
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db));
        }
    }

    void returnBook(int bookId) {
        auto stmt = prepare("UPDATE books SET available = 1 WHERE id = ?");
        sqlite3_bind_int(stmt, 1, bookId);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw SQLException(sqlite3_errmsg(db));
        }
    }

    struct Book {
        int id;
        std::string title;
        std::string author;
        int available;

        Book(int id, const std::string& title, const std::string& author, int available)
            : id(id), title(title), author(author), available(available) {}

        friend std::ostream& operator<<(std::ostream& os, const Book& book) {
            return os << "Book{ id=" << book.id
                      << ", title='" << book.title << "', "
                      << "author='" << book.author << "', "
                      << "available=" << book.available << " }";
        }
    };

    std::vector<Book> searchBooks() {
        std::vector<Book> books;
        auto stmt = prepare("SELECT * FROM books");
        if (sqlite3_step(stmt) != SQLITE_ROW) return books;

        int colCount = sqlite3_column_count(stmt);
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            int id = sqlite3_column_int(stmt, 0);
            const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            int available = sqlite3_column_int(stmt, 3);
            books.emplace_back(id, title, author, available);
        }
        return books;
    }
};