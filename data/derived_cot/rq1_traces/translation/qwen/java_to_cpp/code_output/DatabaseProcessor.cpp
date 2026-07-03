#include <sqlite3.h>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cxxabi.h>
#include <execinfo.h>
#include <variant>

using namespace std;

// RAII wrapper for SQLite statement
class Statement {
public:
    Statement(sqlite3* db, const string& sql) {
        int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw runtime_error(sqlite3_errmsg(db));
        }
        this->db = db;
    }

    ~Statement() {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
    }

    bool execute() {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE || rc == SQLITE_ROW) {
            return true;
        }
        throw runtime_error(sqlite3_errmsg(db));
    }

    int getInt(int col) {
        return sqlite3_column_int(stmt, col);
    }

    string getString(int col) {
        const char* text = (const char*)sqlite3_column_text(stmt, col);
        return text ? string(text) : "";
    }

private:
    sqlite3* db;
    sqlite3_stmt* stmt;
};

// RAII wrapper for database connection
class Database {
public:
    Database(const string& dbName) {
        int rc = sqlite3_open(dbName.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw runtime_error(sqlite3_errmsg(db));
        }
    }

    ~Database() {
        if (db) {
            sqlite3_close(db);
        }
    }

    Statement createStatement(const string& sql) {
        return Statement(db, sql);
    }

private:
    sqlite3* db;
};

// Exception handler to print stack trace
void printStackTrace() {
    void* addr[16];
    int num = backtrace(addr, 16);
    char** symbols = backtrace_symbols(addr, num);
    if (symbols != nullptr) {
        for (int i = 0; i < num; ++i) {
            cout << "  #" << i << ": " << symbols[i] << endl;
        }
        free(symbols);
    }
}

class DatabaseProcessor {
private:
    string databaseName;

public:
    DatabaseProcessor(const string& dbName) : databaseName(dbName) {}

    void createTable(const string& tableName, const string& key1, const string& key2) {
        string sql = "CREATE TABLE IF NOT EXISTS " + tableName + " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        Database db(databaseName);
        Statement stmt(db, sql);
        stmt.execute();
    }

    void insertIntoDatabase(const string& tableName, const vector<map<string, variant<int, string>>>& data) {
        for (const auto& row : data) {
            string name = get<string>(row.at("name"));
            int age = get<int>(row.at("age"));

            string sql = "INSERT INTO " + tableName + " (name, age) VALUES ('" + name + "', " + to_string(age) + ")";
            Database db(databaseName);
            Statement stmt(db, sql);
            stmt.execute();
        }
    }

    vector<map<string, variant<int, string>>> searchDatabase(const string& tableName, const string& name) {
        string sql = "SELECT * FROM " + tableName + " WHERE name = '" + name + "'";
        Database db(databaseName);
        Statement stmt(db, sql);
        stmt.execute();

        vector<map<string, variant<int, string>>> result;
        int colCount = sqlite3_column_count(stmt.stmt);
        while (sqlite3_step(stmt.stmt) == SQLITE_ROW) {
            map<string, variant<int, string>> row;
            for (int i = 0; i < colCount; ++i) {
                const char* colName = sqlite3_column_name(stmt.stmt, i);
                int type = sqlite3_column_type(stmt.stmt, i);

                switch (type) {
                    case SQLITE_INTEGER:
                        row[colName] = sqlite3_column_int(stmt.stmt, i);
                        break;
                    case SQLITE_TEXT:
                        row[colName] = string(sqlite3_column_text(stmt.stmt, i), sqlite3_column_bytes(stmt.stmt, i));
                        break;
                    case SQLITE_FLOAT:
                        // Convert to integer by truncating
                        row[colName] = (int)sqlite3_column_int64(stmt.stmt, i);
                        break;
                    case SQLITE_NULL:
                        row[colName] = "";
                        break;
                }
            }
            result.push_back(row);
        }
        return result;
    }

    void deleteFromDatabase(const string& tableName, const string& name) {
        string sql = "DELETE FROM " + tableName + " WHERE name = '" + name + "'";
        Database db(databaseName);
        Statement stmt(db, sql);
        stmt.execute();
    }
};