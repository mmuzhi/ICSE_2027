#include <sqlite3.h>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

struct Student {
    std::string name;
    int age;
    std::string gender;
    int grade;
};

class StudentDatabaseProcessor {
public:
    StudentDatabaseProcessor(const std::string& database_name) : db_name(database_name) {}

    void create_student_table() {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            // No error handling, as per original behavior
            return;
        }

        const char* create_table_query = "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER)";
        sqlite3_exec(db, create_table_query, nullptr, nullptr, nullptr);

        sqlite3_close(db);
    }

    void insert_student(const Student& student) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            // No error handling
            return;
        }

        const char* insert_query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, insert_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, student.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, student.age);
        sqlite3_bind_text(stmt, 3, student.gender.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, student.grade);

        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::vector<std::vector<std::string>> search_student_by_name(const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            // No error handling
            return {};
        }

        const char* select_query = "SELECT * FROM students WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, select_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return {};
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        std::vector<std::vector<std::string>> result;
        while (SQLITE_ROW == sqlite3_step(stmt)) {
            int columns = sqlite3_column_count(stmt);
            std::vector<std::string> row;
            for (int i = 0; i < columns; i++) {
                const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
                row.push_back(text ? std::string(text) : "");
            }
            result.push_back(row);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    void delete_student_by_name(const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(db_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            // No error handling
            return;
        }

        const char* delete_query = "DELETE FROM students WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, delete_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

private:
    std::string db_name;
};