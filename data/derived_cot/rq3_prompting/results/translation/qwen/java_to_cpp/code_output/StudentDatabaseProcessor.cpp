#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sqlite3.h>

class StudentDatabaseProcessor {
private:
    std::string databaseName;

    struct SQLiteConnection {
        sqlite3* db;
        SQLiteConnection(const std::string& dbPath) {
            int rc = sqlite3_open(dbPath.c_str(), &db);
            if (rc != SQLITE_OK) {
                throw std::runtime_error("Cannot open database: " + dbPath);
            }
        }
        ~SQLiteConnection() {
            if (db) {
                sqlite3_close(db);
            }
        }
        operator sqlite3*() { return db; }
        SQLiteConnection(const SQLiteConnection&) = delete;
        SQLiteConnection& operator=(const SQLiteConnection&) = delete;
    };

    struct SQLiteStatement {
        sqlite3_stmt* stmt;
        SQLiteConnection& conn;
        SQLiteStatement(SQLiteConnection& conn, const std::string& query) : conn(conn) {
            int rc = sqlite3_prepare_v2(conn, query.c_str(), -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                throw std::runtime_error("Failed to prepare statement: " + query);
            }
        }
        ~SQLiteStatement() {
            if (stmt) {
                sqlite3_finalize(stmt);
            }
        }
        operator sqlite3_stmt*() { return stmt; }
        SQLiteStatement(const SQLiteStatement&) = delete;
        SQLiteStatement& operator=(const SQLiteStatement&) = delete;
    };

    void executeStatement(SQLiteStatement& stmt) {
        int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("Statement execution error");
        }
    }

    int executeUpdate(SQLiteStatement& stmt) {
        int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error("Update failed");
        }
        return rc;
    }

    bool executeQuery(SQLiteStatement& stmt) {
        int rc = sqlite3_step(stmt);
        return rc == SQLITE_ROW || rc == SQLITE_DONE;
    }

    std::map<std::string, std::vector<int>> getColumnIndices(SQLiteStatement& stmt, const std::vector<std::string>& columns) {
        std::map<std::string, std::vector<int>> indices;
        for (const auto& column : columns) {
            int index = sqlite3_column_index(stmt, column.c_str());
            if (index == -1) {
                throw std::runtime_error("Column not found: " + column);
            }
            indices[column].push_back(index);
        }
        return indices;
    }

public:
    struct StudentData {
        std::string name;
        int age;
        std::string gender;
        int grade;

        StudentData(const std::string& name, int age, const std::string& gender, int grade)
            : name(name), age(age), gender(gender), grade(grade) {}
    };

    StudentDatabaseProcessor(const std::string& databaseName) : databaseName(databaseName) {}

    void createStudentTable() {
        std::string createTableQuery = "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER"
            ")";
        try (SQLiteConnection conn(databaseName)) {
            SQLiteStatement stmt(conn, createTableQuery);
            executeStatement(stmt);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    void insertStudent(const StudentData& studentData) {
        std::string insertQuery = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        try (SQLiteConnection conn(databaseName)) {
            SQLiteStatement stmt(conn, insertQuery);
            sqlite3_bind_text(stmt, 1, studentData.name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 2, studentData.age);
            sqlite3_bind_text(stmt, 3, studentData.gender.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(stmt, 4, studentData.grade);
            executeUpdate(stmt);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    std::vector<std::map<std::string, int>> searchStudentByName(const std::string& name) {
        std::string selectQuery = "SELECT * FROM students WHERE name = ?";
        std::vector<std::map<std::string, int>> result;
        try (SQLiteConnection conn(databaseName)) {
            SQLiteStatement stmt(conn, selectQuery);
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            if (!executeQuery(stmt)) {
                return result;
            }
            const std::vector<std::string> columns = {"id", "name", "age", "gender", "grade"};
            auto indices = getColumnIndices(stmt, columns);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::map<std::string, int> student;
                for (const auto& column : columns) {
                    int index = indices[column][0];
                    student[column] = sqlite3_column_int(stmt, index);
                }
                result.push_back(student);
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        return result;
    }

    void deleteStudentByName(const std::string& name) {
        std::string deleteQuery = "DELETE FROM students WHERE name = ?";
        try (SQLiteConnection conn(databaseName)) {
            SQLiteStatement stmt(conn, deleteQuery);
            sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
            executeUpdate(stmt);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};

int main() {
    StudentDatabaseProcessor processor("students.db");
    processor.createStudentTable();
    processor.insertStudent(StudentDatabaseProcessor::StudentData("Alice", 20, "F", 90));
    processor.insertStudent(StudentDatabaseProcessor::StudentData("Bob", 22, "M", 85));
    auto students = processor.searchStudentByName("Alice");
    for (const auto& student : students) {
        std::cout << "ID: " << student["id"] << std::endl;
        std::cout << "Name: " << student["name"] << std::endl;
        std::cout << "Age: " << student["age"] << std::endl;
        std::cout << "Gender: " << student["gender"] << std::endl;
        std::cout << "Grade: " << student["grade"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    processor.deleteStudentByName("Alice");
    return 0;
}