#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class UserLoginDB {
private:
    unique_ptr<SQLite::Database> db;

public:
    UserLoginDB(const string& db_name) : db(new SQLite::Database(db_name, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)) {}

    ~UserLoginDB() = default;

    void create_table() {
        string create_table_query = "CREATE TABLE IF NOT EXISTS users (" 
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT NOT NULL UNIQUE, "
            "password TEXT NOT NULL "
            ")";
        db->exec(create_table_query);
    }

    void insert_user(const string& username, const string& password) {
        string insert_query = "INSERT INTO users (username, password) VALUES (?, ?)";
        SQLite::Statement query(db.get(), insert_query);
        query.bind(1, username);
        query.bind(2, password);
        query.exec();
        db->commit(); // Ensure changes are saved
    }

    vector<tuple<int, string, string>> search_user_by_username(const string& username) {
        string select_query = "SELECT id, username, password FROM users WHERE username = ?";
        SQLite::Statement query(db.get(), select_query);
        query.bind(1, username);
        vector<tuple<int, string, string>> result;
        if (query.executeStep()) {
            result.push_back(make_tuple(query.getColumnInt(0), query.getColumnString(1), query.getColumnString(2)));
        }
        return result;
    }

    void delete_user_by_username(const string& username) {
        string delete_query = "DELETE FROM users WHERE username = ?";
        SQLite::Statement query(db.get(), delete_query);
        query.bind(1, username);
        query.exec();
        db->commit(); // Ensure changes are saved
    }

    bool validate_user_login(const string& username, const string& password) {
        auto users = search_user_by_username(username);
        if (users.empty()) {
            return false;
        }
        string stored_password = get<2>(users[0]);
        return stored_password == password;
    }
};