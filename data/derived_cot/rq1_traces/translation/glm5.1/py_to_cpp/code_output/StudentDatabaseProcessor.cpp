#include <string>
#include <map>
#include <variant>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <sqlite3.h>

class StudentDatabaseProcessor {
private:
    std::string database_name;

public:
    StudentDatabaseProcessor(const std::string& database_name)
        : database_name(database_name) {}

    void create_student_table() {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        const char* create_table_query =
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY,"
            "name TEXT,"
            "age INTEGER,"
            "gender TEXT,"
            "grade INTEGER"
            ")";

        char* err_msg = nullptr;
        rc = sqlite3_exec(db, create_table_query, nullptr, nullptr, &err_msg);
        if (rc != SQLITE_OK) {
            std::string err(err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        sqlite3_close(db);
    }

    void insert_student(const std::map<std::string, std::variant<int, std::string>>& student_data) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        const char* insert_query =
            "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, insert_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        sqlite3_bind_text(stmt, 1, std::get<std::string>(student_data.at("name")).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, std::get<int>(student_data.at("age")));
        sqlite3_bind_text(stmt, 3, std::get<std::string>(student_data.at("gender")).c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, std::get<int>(student_data.at("grade")));

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error(err);
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
            throw std::runtime_error(err);
        }

        const char* select_query = "SELECT * FROM students WHERE name = ?";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, select_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int, std::string, int>> result;

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name_text = sqlite3_column_text(stmt, 1);
            std::string name_val = name_text ? reinterpret_cast<const char*>(name_text) : "";
            int age = sqlite3_column_int(stmt, 2);
            const unsigned char* gender_text = sqlite3_column_text(stmt, 3);
            std::string gender = gender_text ? reinterpret_cast<const char*>(gender_text) : "";
            int grade = sqlite3_column_int(stmt, 4);
            result.emplace_back(id, name_val, age, gender, grade);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return result;
    }

    void delete_student_by_name(const std::string& name) {
        sqlite3* db;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        const char* delete_query = "DELETE FROM students WHERE name = ?";

        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, delete_query, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::string err = sqlite3_errmsg(db);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            throw std::runtime_error(err);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};