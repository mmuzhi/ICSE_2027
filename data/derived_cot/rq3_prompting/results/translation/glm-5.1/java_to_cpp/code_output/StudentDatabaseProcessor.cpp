#include <sqlite3.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <any>
#include <memory>
#include <stdexcept>

class StudentDatabaseProcessor {
private:
    std::string databaseName;

    using ConnPtr = std::unique_ptr<sqlite3, decltype(&sqlite3_close)>;
    using StmtPtr = std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)>;

    ConnPtr getConnection() {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(databaseName.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::string err = db ? sqlite3_errmsg(db) : "Cannot open database";
            if (db) {
                sqlite3_close(db);
            }
            throw std::runtime_error(err);
        }
        return ConnPtr(db, &sqlite3_close);
    }

public:
    class StudentData {
    private:
        std::string name;
        int age;
        std::string gender;
        int grade;

    public:
        StudentData(std::string name, int age, std::string gender, int grade)
            : name(std::move(name)), age(age), gender(std::move(gender)), grade(grade) {}

        const std::string& getName() const { return name; }
        int getAge() const { return age; }
        const std::string& getGender() const { return gender; }
        int getGrade() const { return grade; }
    };

    StudentDatabaseProcessor(std::string dbName) : databaseName(std::move(dbName)) {}

    void createStudentTable() {
        const char* createTableQuery = "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER)";
        try {
            auto conn = getConnection();
            char* errMsg = nullptr;
            int rc = sqlite3_exec(conn.get(), createTableQuery, nullptr, nullptr, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void insertStudent(const StudentData& studentData) {
        const char* insertQuery = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        try {
            auto conn = getConnection();
            sqlite3_stmt* stmtPtr = nullptr;
            int rc = sqlite3_prepare_v2(conn.get(), insertQuery, -1, &stmtPtr, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << sqlite3_errmsg(conn.get()) << std::endl;
                return;
            }
            StmtPtr stmt(stmtPtr, &sqlite3_finalize);

            sqlite3_bind_text(stmt.get(), 1, studentData.getName().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt.get(), 2, studentData.getAge());
            sqlite3_bind_text(stmt.get(), 3, studentData.getGender().c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt.get(), 4, studentData.getGrade());

            rc = sqlite3_step(stmt.get());
            if (rc != SQLITE_DONE) {
                std::cerr << "SQL error: " << sqlite3_errmsg(conn.get()) << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    std::vector<std::map<std::string, std::any>> searchStudentByName(const std::string& name) {
        const char* selectQuery = "SELECT * FROM students WHERE name = ?";
        std::vector<std::map<std::string, std::any>> result;
        try {
            auto conn = getConnection();
            sqlite3_stmt* stmtPtr = nullptr;
            int rc = sqlite3_prepare_v2(conn.get(), selectQuery, -1, &stmtPtr, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << sqlite3_errmsg(conn.get()) << std::endl;
                return result;
            }
            StmtPtr stmt(stmtPtr, &sqlite3_finalize);

            sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);

            while (sqlite3_step(stmt.get()) == SQLITE_ROW) {
                std::map<std::string, std::any> student;
                student["id"] = sqlite3_column_int(stmt.get(), 0);
                
                const char* namePtr = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
                student["name"] = namePtr ? std::string(namePtr) : std::string();
                
                student["age"] = sqlite3_column_int(stmt.get(), 2);
                
                const char* genderPtr = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 3));
                student["gender"] = genderPtr ? std::string(genderPtr) : std::string();
                
                student["grade"] = sqlite3_column_int(stmt.get(), 4);
                result.push_back(student);
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
        return result;
    }

    void deleteStudentByName(const std::string& name) {
        const char* deleteQuery = "DELETE FROM students WHERE name = ?";
        try {
            auto conn = getConnection();
            sqlite3_stmt* stmtPtr = nullptr;
            int rc = sqlite3_prepare_v2(conn.get(), deleteQuery, -1, &stmtPtr, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << sqlite3_errmsg(conn.get()) << std::endl;
                return;
            }
            StmtPtr stmt(stmtPtr, &sqlite3_finalize);

            sqlite3_bind_text(stmt.get(), 1, name.c_str(), -1, SQLITE_TRANSIENT);

            rc = sqlite3_step(stmt.get());
            if (rc != SQLITE_DONE) {
                std::cerr << "SQL error: " << sqlite3_errmsg(conn.get()) << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
};