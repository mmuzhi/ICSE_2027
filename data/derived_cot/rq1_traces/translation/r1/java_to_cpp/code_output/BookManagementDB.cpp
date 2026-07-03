#include <sqlite3.h>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class BookManagementDB {
private:
    sqlite3* db;

    using StmtPtr = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;

    StmtPtr prepareStmt(const std::string& sql) {
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        return StmtPtr(stmt, sqlite3_finalize);
    }

public:
    BookManagementDB(const std::string& dbName) : db(nullptr) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        createTable();
    }

    ~BookManagementDB() {
        if (db) {
            sqlite3_close(db);
        }
    }

    void createTable() {
        const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "title TEXT, "
                          "author TEXT, "
                          "available INTEGER"
                          ")";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::string errorMsg = errMsg;
            sqlite3_free(errMsg);
            throw std::runtime_error(errorMsg);
        }
    }

    void addBook(const std::string& title, const std::string& author) {
        std::string sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)";
        StmtPtr stmt = prepareStmt(sql);
        sqlite3_stmt* stmtPtr = stmt.get();

        if (sqlite3_bind_text(stmtPtr, 1, title.c_str(), title.size(), SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_text(stmtPtr, 2, author.c_str(), author.size(), SQLITE_TRANSIENT) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        if (sqlite3_step(stmtPtr) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void removeBook(int bookId) {
        std::string sql = "DELETE FROM books WHERE id = ?";
        StmtPtr stmt = prepareStmt(sql);
        sqlite3_stmt* stmtPtr = stmt.get();

        if (sqlite3_bind_int(stmtPtr, 1, bookId) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        if (sqlite3_step(stmtPtr) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void borrowBook(int bookId) {
        std::string sql = "UPDATE books SET available = 0 WHERE id = ?";
        StmtPtr stmt = prepareStmt(sql);
        sqlite3_stmt* stmtPtr = stmt.get();

        if (sqlite3_bind_int(stmtPtr, 1, bookId) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        if (sqlite3_step(stmtPtr) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void returnBook(int bookId) {
        std::string sql = "UPDATE books SET available = 1 WHERE id = ?";
        StmtPtr stmt = prepareStmt(sql);
        sqlite3_stmt* stmtPtr = stmt.get();

        if (sqlite3_bind_int(stmtPtr, 1, bookId) != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        if (sqlite3_step(stmtPtr) != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

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
        std::string getTitle() const { return title; }
        std::string getAuthor() const { return author; }
        int getAvailable() const { return available; }
    };

    std::vector<Book> searchBooks() {
        std::string sql = "SELECT * FROM books";
        StmtPtr stmt = prepareStmt(sql);
        sqlite3_stmt* stmtPtr = stmt.get();

        std::vector<Book> books;
        int rc;
        while ((rc = sqlite3_step(stmtPtr)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmtPtr, 0);
            const unsigned char* titleRaw = sqlite3_column_text(stmtPtr, 1);
            const unsigned char* authorRaw = sqlite3_column_text(stmtPtr, 2);
            int available = sqlite3_column_int(stmtPtr, 3);

            std::string title(reinterpret_cast<const char*>(titleRaw));
            std::string author(reinterpret_cast<const char*>(authorRaw));

            books.push_back(Book(id, title, author, available));
        }

        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        return books;
    }
};