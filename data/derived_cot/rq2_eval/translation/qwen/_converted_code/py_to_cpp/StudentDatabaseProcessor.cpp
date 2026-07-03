#include <SQLiteCpp/SQLiteCpp.h>
#include <stdexcept>
#include <string>
#include <vector>

// Define a struct to hold student data
struct Student {
    std::string name;
    int age;
    std::string gender;
    int grade;
};

class StudentDatabaseProcessor {
public:
    StudentDatabaseProcessor(const std::string& database_name)
        : database_name_(database_name) {}

    void create_student_table() {
        try {
            SQLite::Database db(database_name_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            std::string create_table_query = R"(
                CREATE TABLE IF NOT EXISTS students (
                    id INTEGER PRIMARY KEY,
                    name TEXT,
                    age INTEGER,
                    gender TEXT,
                    grade INTEGER
                )
            )";
            db.exec(create_table_query);
        } catch (const std::exception& e) {
            throw std::runtime_error("Database error: " + std::string(e.what()));
        }
    }

    void insert_student(const Student& student) {
        try {
            SQLite::Database db(database_name_, SQLite::OPEN_READWRITE);
            std::string insert_query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
            SQLite::Statement stmt(db, insert_query);
            stmt.bind(1, student.name)
               .bind(2, student.age)
               .bind(3, student.gender)
               .bind(4, student.grade);
            stmt.exec();
        } catch (const std::exception& e) {
            throw std::runtime_error("Database error: " + std::string(e.what()));
        }
    }

    std::vector<std::tuple<std::string, int, std::string, int>> search_student_by_name(const std::string& name) {
        try {
            SQLite::Database db(database_name_, SQLite::OPEN_READWRITE);
            std::string select_query = "SELECT * FROM students WHERE name = ?";
            SQLite::Statement stmt(db, select_query);
            stmt.bind(1, name);
            std::vector<std::tuple<std::string, int, std::string, int>> result;
            while (stmt.next()) {
                result.push_back(std::make_tuple(
                    stmt.getColumnText(0),
                    stmt.getColumnInt(1),
                    stmt.getColumnText(2),
                    stmt.getColumnInt(3)
                ));
            }
            return result;
        } catch (const std::exception& e) {
            throw std::runtime_error("Database error: " + std::string(e.what()));
        }
    }

    void delete_student_by_name(const std::string& name) {
        try {
            SQLite::Database db(database_name_, SQLite::OPEN_READWRITE);
            std::string delete_query = "DELETE FROM students WHERE name = ?";
            SQLite::Statement stmt(db, delete_query);
            stmt.bind(1, name);
            stmt.exec();
        } catch (const std::exception& e) {
            throw std::runtime_error("Database error: " + std::string(e.what()));
        }
    }

private:
    std::string database_name_;
};