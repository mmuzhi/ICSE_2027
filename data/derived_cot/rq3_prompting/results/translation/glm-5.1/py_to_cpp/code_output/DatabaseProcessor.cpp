#include <string>
#include <vector>
#include <map>
#include <variant>
#include <optional>
#include <tuple>
#include <sqlite3.h>

class DatabaseProcessor {
private:
    std::string database_name;

public:
    DatabaseProcessor(const std::string& database_name) : database_name(database_name) {}

    void create_table(const std::string& table_name, const std::string& key1, const std::string& key2) {
        sqlite3* conn;
        sqlite3_open(database_name.c_str(), &conn);

        std::string create_table_query = "CREATE TABLE IF NOT EXISTS " + table_name +
            " (id INTEGER PRIMARY KEY, " + key1 + " TEXT, " + key2 + " INTEGER)";
        sqlite3_exec(conn, create_table_query.c_str(), nullptr, nullptr, nullptr);

        sqlite3_close(conn);
    }

    void insert_into_database(const std::string& table_name,
                               const std::vector<std::map<std::string, std::variant<std::string, int>>>& data) {
        sqlite3* conn;
        sqlite3_open(database_name.c_str(), &conn);

        sqlite3_stmt* stmt;
        std::string insert_query = "INSERT INTO " + table_name + " (name, age) VALUES (?, ?)";
        sqlite3_prepare_v2(conn, insert_query.c_str(), -1, &stmt, nullptr);

        for (const auto& item : data) {
            sqlite3_reset(stmt);
            sqlite3_bind_text(stmt, 1, std::get<std::string>(item.at("name")).c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 2, std::get<int>(item.at("age")));
            sqlite3_step(stmt);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(conn);
    }

    std::optional<std::vector<std::tuple<int, std::string, int>>> search_database(const std::string& table_name, const std::string& name) {
        sqlite3* conn;
        sqlite3_open(database_name.c_str(), &conn);

        sqlite3_stmt* stmt;
        std::string select_query = "SELECT * FROM " + table_name + " WHERE name = ?";
        sqlite3_prepare_v2(conn, select_query.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

        std::vector<std::tuple<int, std::string, int>> result;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name_val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int age = sqlite3_column_int(stmt, 2);
            result.emplace_back(id, name_val, age);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(conn);

        if (!result.empty()) {
            return result;
        } else {
            return std::nullopt;
        }
    }

    void delete_from_database(const std::string& table_name, const std::string& name) {
        sqlite3* conn;
        sqlite3_open(database_name.c_str(), &conn);

        sqlite3_stmt* stmt;
        std::string delete_query = "DELETE FROM " + table_name + " WHERE name = ?";
        sqlite3_prepare_v2(conn, delete_query.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);

        sqlite3_finalize(stmt);
        sqlite3_close(conn);
    }
};