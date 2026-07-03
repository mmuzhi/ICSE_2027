#include <sqlite3.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <tuple>
#include <functional>

class ScopeGuard {
public:
    template <typename Func>
    ScopeGuard(Func func) : func_(func) {}
    ~ScopeGuard() { func_(); }
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
private:
    std::function<void()> func_;
};

struct StudentData {
    std::string name;
    int age;
    std::string gender;
    int grade;
};

class StudentDatabaseProcessor {
private:
    std::string database_name;

public:
    StudentDatabaseProcessor(const std::string& database_name) : database_name(database_name) {}

    void create_student_table() {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errstr(rc));
        }
        ScopeGuard db_guard([db] { sqlite3_close(db); });

        const char* sql = "CREATE TABLE IF NOT EXISTS students ("
                          "id INTEGER PRIMARY KEY,"
                          "name TEXT,"
                          "age INTEGER,"
                          "gender TEXT,"
                          "grade INTEGER)";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        ScopeGuard stmt_guard([stmt] { sqlite3_finalize(stmt); });

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    void insert_student(const StudentData& student_data) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errstr(rc));
        }
        ScopeGuard db_guard([db] { sqlite3_close(db); });

        const char* sql = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        ScopeGuard stmt_guard([stmt] { sqlite3_finalize(stmt); });

        rc = sqlite3_bind_text(stmt, 1, student_data.name.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        rc = sqlite3_bind_int(stmt, 2, student_data.age);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        rc = sqlite3_bind_text(stmt, 3, student_data.gender.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        rc = sqlite3_bind_int(stmt, 4, student_data.grade);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }

    std::vector<std::tuple<int, std::string, int, std::string, int>> search_student_by_name(const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errstr(rc));
        }
        ScopeGuard db_guard([db] { sqlite3_close(db); });

        const char* sql = "SELECT * FROM students WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        ScopeGuard stmt_guard([stmt] { sqlite3_finalize(stmt); });

        rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        std::vector<std::tuple<int, std::string, int, std::string, int>> results;

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);
            const char* gender = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            int grade = sqlite3_column_int(stmt, 4);

            results.emplace_back(id, std::string(name), age, std::string(gender), grade);
        }

        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        return results;
    }

    void delete_student_by_name(const std::string& name) {
        sqlite3* db = nullptr;
        int rc = sqlite3_open(database_name.c_str(), &db);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errstr(rc));
        }
        ScopeGuard db_guard([db] { sqlite3_close(db); });

        const char* sql = "DELETE FROM students WHERE name = ?";
        sqlite3_stmt* stmt = nullptr;
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
        ScopeGuard stmt_guard([stmt] { sqlite3_finalize(stmt); });

        rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }

        rc = sqlite3_exec(db, "COMMIT", nullptr, nullptr, nullptr);
        if (rc != SQLITE_OK) {
            throw std::runtime_error(sqlite3_errmsg(db));
        }
    }
};