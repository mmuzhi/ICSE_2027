#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <cstring>

struct Student {
    int id;
    std::string name;
    int age;
    std::string gender;
    int grade;
};

class StudentDatabaseProcessor {
private:
    std::string database_name;

public:
    StudentDatabaseProcessor(const std::string& db_name) : database_name(db_name) {}

    void create_student_table() {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        const char* sql = "CREATE TABLE IF NOT EXISTS students ("
                          "id INTEGER PRIMARY KEY, "
                          "name TEXT, "
                          "age INTEGER, "
                          "gender TEXT, "
                          "grade INTEGER)";

        char* err_msg = nullptr;
        rc = sqlite3_exec(db, sql, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string err(err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error("Failed to create table: " + err);
        }

        sqlite3_close(db);
    }

    void insert_student(const Student& student_data) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        const char* sql = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare statement: " + err);
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
            throw std::runtime_error("Failed to insert student: " + err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::vector<std::tuple<int, std::string, int, std::string, int>> search_student_by_name(const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        const char* sql = "SELECT * FROM students WHERE name = ?";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare statement: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int, std::string, int>> results;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);
            const char* gender_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            int grade = sqlite3_column_int(stmt, 4);
            results.emplace_back(id, name_ptr ? name_ptr : "", age, gender_ptr ? gender_ptr : "", grade);
        }

        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Error fetching results: " + err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return results;
    }

    void delete_student_by_name(const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to open database: " + err);
        }

        const char* sql = "DELETE FROM students WHERE name = ?";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error("Failed to prepare statement: " + err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error("Failed to delete student: " + err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};