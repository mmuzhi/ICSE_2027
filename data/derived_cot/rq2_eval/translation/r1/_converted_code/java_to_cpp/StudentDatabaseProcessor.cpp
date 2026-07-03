#include <sqlite3.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <variant>

class StudentDatabaseProcessor {
public:
    struct StudentData {
        std::string name;
        int age;
        std::string gender;
        int grade;

        StudentData(std::string name, int age, std::string gender, int grade)
            : name(std::move(name)), age(age), gender(std::move(gender)), grade(grade) {}
    };

    explicit StudentDatabaseProcessor(const std::string& databaseName)
        : databaseName(databaseName) {}

    void create_student_table() {
        const char* createTableQuery = 
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER"
            ")";

        sqlite3* db = getConnection();
        if (!db) {
            return;
        }

        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }

        sqlite3_close(db);
    }

    void insert_student(const StudentData& studentData) {
        const char* insertQuery = 
            "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";

        sqlite3* db = getConnection();
        if (!db) {
            return;
        }

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_bind_text(stmt, 1, studentData.name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding name failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_bind_int(stmt, 2, studentData.age);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding age failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_bind_text(stmt, 3, studentData.gender.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding gender failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_bind_int(stmt, 4, studentData.grade);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding grade failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

    using Row = std::map<std::string, std::variant<std::monostate, int, std::string>>;
    std::vector<Row> searchStudentByName(const std::string& name) {
        const char* selectQuery = "SELECT * FROM students WHERE name = ?";
        std::vector<Row> result;

        sqlite3* db = getConnection();
        if (!db) {
            return result;
        }

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return result;
        }

        rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding name failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return result;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            Row row;

            int id = sqlite3_column_int(stmt, 0);
            row["id"] = id;

            if (sqlite3_column_type(stmt, 1) == SQLITE_NULL) {
                row["name"] = std::monostate{};
            } else {
                const unsigned char* text = sqlite3_column_text(stmt, 1);
                row["name"] = std::string(reinterpret_cast<const char*>(text));
            }

            int age = sqlite3_column_int(stmt, 2);
            row["age"] = age;

            if (sqlite3_column_type(stmt, 3) == SQLITE_NULL) {
                row["gender"] = std::monostate{};
            } else {
                const unsigned char* text = sqlite3_column_text(stmt, 3);
                row["gender"] = std::string(reinterpret_cast<const char*>(text));
            }

            int grade = sqlite3_column_int(stmt, 4);
            row["grade"] = grade;

            result.push_back(row);
        }

        if (rc != SQLITE_DONE) {
            std::cerr << "Error during step: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return result;
    }

    void delete_student_by_name(const std::string& name) {
        const char* deleteQuery = "DELETE FROM students WHERE name = ?";

        sqlite3* db = getConnection();
        if (!db) {
            return;
        }

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, deleteQuery, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            std::cerr << "Binding name failed: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Delete failed: " << sqlite3_errmsg(db) << std::endl;
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

private:
    std::string databaseName;

    sqlite3* getConnection() {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return nullptr;
        }
        return db;
    }
};