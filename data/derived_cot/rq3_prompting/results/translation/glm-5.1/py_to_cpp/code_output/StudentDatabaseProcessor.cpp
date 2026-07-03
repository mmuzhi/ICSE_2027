#include <string>
#include <vector>
#include <tuple>
#include <sqlite3.h>
#include <stdexcept>

struct StudentData {
    std::string name;
    int age;
    std::string gender;
    int grade;
};

class StudentDatabaseProcessor {
private:
    std::string database_name;

    sqlite3* open_database() {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Cannot open database: " + err);
        }
        return db;
    }

    void close_database(sqlite3* db) {
        sqlite3_close(db);
    }

public:
    StudentDatabaseProcessor(const std::string& database_name)
        : database_name(database_name) {}

    void create_student_table() {
        sqlite3* db = open_database();

        const char* create_table_query = R"(
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY,
            name TEXT,
            age INTEGER,
            gender TEXT,
            grade INTEGER
        )
        )";

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, create_table_query, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::string error = errMsg;
            sqlite3_free(errMsg);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + error);
        }

        close_database(db);
    }

    void insert_student(const StudentData& student_data) {
        sqlite3* db = open_database();

        const char* insert_query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, insert_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + err);
        }

        sqlite3_bind_text(stmt, 1, student_data.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, student_data.age);
        sqlite3_bind_text(stmt, 3, student_data.gender.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, student_data.grade);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + err);
        }

        sqlite3_finalize(stmt);
        close_database(db);
    }

    std::vector<std::tuple<int, std::string, int, std::string, int>> search_student_by_name(const std::string& name) {
        sqlite3* db = open_database();

        const char* select_query = "SELECT * FROM students WHERE name = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, select_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int, std::string, int>> result;

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string name_val = name_ptr ? name_ptr : "";
            int age = sqlite3_column_int(stmt, 2);
            const char* gender_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            std::string gender = gender_ptr ? gender_ptr : "";
            int grade = sqlite3_column_int(stmt, 4);
            result.emplace_back(id, name_val, age, gender, grade);
        }

        sqlite3_finalize(stmt);
        close_database(db);

        return result;
    }

    void delete_student_by_name(const std::string& name) {
        sqlite3* db = open_database();

        const char* delete_query = "DELETE FROM students WHERE name = ?";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, delete_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("SQL error: " + err);
        }

        sqlite3_finalize(stmt);
        close_database(db);
    }
};