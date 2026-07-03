#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <any>
#include <sqlite3.h>

class StudentDatabaseProcessor {
private:
    std::string databaseName;

    sqlite3* getConnection() {
        sqlite3* db;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return nullptr;
        }
        return db;
    }

public:
    StudentDatabaseProcessor(const std::string& dbName) : databaseName(dbName) {}

    void createStudentTable() {
        const char* createQuery = "CREATE TABLE IF NOT EXISTS students ("
                                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                  "name TEXT, "
                                  "age INTEGER, "
                                  "gender TEXT, "
                                  "grade INTEGER"
                                  ")";
        sqlite3* db = getConnection();
        if (!db) return;

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, createQuery, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        sqlite3_close(db);
    }

    struct StudentData {
        std::string name;
        int age;
        std::string gender;
        int grade;

        StudentData(const std::string& name, int age, const std::string& gender, int grade)
            : name(name), age(age), gender(gender), grade(grade) {}

        std::string getName() const { return name; }
        int getAge() const { return age; }
        std::string getGender() const { return gender; }
        int getGrade() const { return grade; }
    };

    void insertStudent(const StudentData& studentData) {
        const char* insertQuery = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        sqlite3* db = getConnection();
        if (!db) return;

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, studentData.getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, studentData.getAge());
        sqlite3_bind_text(stmt, 3, studentData.getGender().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, studentData.getGrade());

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    std::vector<std::map<std::string, std::any>> searchStudentByName(const std::string& name) {
        std::vector<std::map<std::string, std::any>> result;
        const char* selectQuery = "SELECT * FROM students WHERE name = ?";
        sqlite3* db = getConnection();
        if (!db) return result;

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return result;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::map<std::string, std::any> student;
            student["id"] = sqlite3_column_int(stmt, 0);
            student["name"] = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            student["age"] = sqlite3_column_int(stmt, 2);
            student["gender"] = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            student["grade"] = sqlite3_column_int(stmt, 4);
            result.push_back(std::move(student));
        }

        if (rc != SQLITE_DONE) {
            std::cerr << "Error during query: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    void deleteStudentByName(const std::string& name) {
        const char* deleteQuery = "DELETE FROM students WHERE name = ?";
        sqlite3* db = getConnection();
        if (!db) return;

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, deleteQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
};