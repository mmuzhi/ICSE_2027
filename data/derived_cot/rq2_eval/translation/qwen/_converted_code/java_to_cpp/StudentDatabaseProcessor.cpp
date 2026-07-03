#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <sqlite3.h>

class StudentDatabaseProcessor {
private:
    std::string databaseName;

    struct SQLiteConnection {
        sqlite3* db;
        SQLiteConnection(const std::string& dbName) {
            int rc = sqlite3_open(dbName.c_str(), &db);
            if (rc != SQLITE_OK) {
                throw std::runtime_error(sqlite3_errmsg(db));
            }
        }
        ~SQLiteConnection() {
            if (db) {
                sqlite3_close(db);
            }
        }
        operator sqlite3*&() { return db; }
    };

    void createTable(SQLiteConnection& conn) {
        const char* sql = "CREATE TABLE IF NOT EXISTS students ("
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                           "name TEXT, "
                           "age INTEGER, "
                           "gender TEXT, "
                           "grade INTEGER)";
        char* errMsg = nullptr;
        int rc = sqlite3_exec(conn, sql, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            if (errMsg) {
                sqlite3_free(errMsg);
            }
            throw std::runtime_error(sqlite3_errmsg(conn));
        }
    }

    void insert_student(SQLiteConnection& conn, const StudentData& studentData) {
        const char* sql = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(conn));
        }

        sqlite3_bind_text(stmt, 1, studentData.name.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, studentData.age);
        sqlite3_bind_text(stmt, 3, studentData.gender.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, studentData.grade);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(conn));
        }

        sqlite3_finalize(stmt);
    }

    std::vector<std::map<std::string, std::string>> searchStudentByName(SQLiteConnection& conn, const std::string& name) {
        std::vector<std::map<std::string, std::string>> result;
        const char* sql = "SELECT * FROM students WHERE name = ?";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(conn));
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::map<std::string, std::string> student;
            student["id"] = std::to_string(sqlite3_column_int(stmt, 0));
            student["name"] = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            student["age"] = std::to_string(sqlite3_column_int(stmt, 2));
            student["gender"] = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            student["grade"] = std::to_string(sqlite3_column_int(stmt, 4));
            result.push_back(student);
        }

        sqlite3_finalize(stmt);
        return result;
    }

    void delete_student_by_name(SQLiteConnection& conn, const std::string& name) {
        const char* sql = "DELETE FROM students WHERE name = ?";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(conn, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(conn));
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

        int step_rc = sqlite3_step(stmt);
        if (step_rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(conn));
        }

        sqlite3_finalize(stmt);
    }

public:
    StudentDatabaseProcessor(const std::string& databaseName) : databaseName(databaseName) {}

    void create_student_table() {
        try {
            SQLiteConnection conn(databaseName);
            createTable(conn);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void insert_student(const StudentData& studentData) {
        try {
            SQLiteConnection conn(databaseName);
            insert_student(conn, studentData);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::vector<std::map<std::string, std::string>> searchStudentByName(const std::string& name) {
        try {
            SQLiteConnection conn(databaseName);
            return searchStudentByName(conn, name);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return {};
        }
    }

    void delete_student_by_name(const std::string& name) {
        try {
            SQLiteConnection conn(databaseName);
            delete_student_by_name(conn, name);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    struct StudentData {
        std::string name;
        int age;
        std::string gender;
        int grade;

        StudentData(const std::string& name, int age, const std::string& gender, int grade)
            : name(name), age(age), gender(gender), grade(grade) {}
    };
};

int main() {
    StudentDatabaseProcessor processor("students.db");
    processor.create_student_table();

    StudentDatabaseProcessor::StudentData student("Alice", 20, "F", 90);
    processor.insert_student(student);

    auto results = processor.searchStudentByName("Alice");
    for (const auto& student : results) {
        std::cout << "ID: " << student["id"] << std::endl;
        std::cout << "Name: " << student["name"] << std::endl;
        std::cout << "Age: " << student["age"] << std::endl;
        std::cout << "Gender: " << student["gender"] << std::endl;
        std::cout << "Grade: " << student["grade"] << std::endl;
        std::cout << std::endl;
    }

    processor.delete_student_by_name("Alice");

    return 0;
}