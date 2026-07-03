import sqlite3

class UserLoginDB:
    def __init__(self, db_name):
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            print(e)

    def create_table(self):
        create_table_query = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_query)
            self.connection.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            cursor.close()

    def insert_user(self, username, password):
        insert_query = "INSERT INTO users (username, password) VALUES (?, ?)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_query, (username, password))
            self.connection.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            cursor.close()

    def search_user_by_username(self, username):
        search_query = "SELECT * FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(search_query, (username,))
            row = cursor.fetchone()
            if row:
                return f"{row[0]},{row[1]}"
        except sqlite3.Error as e:
            print(e)
        finally:
            cursor.close()
        return None

    def delete_user_by_username(self, username):
        delete_query = "DELETE FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_query, (username,))
            self.connection.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            cursor.close()

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user:
            parts = user.split(',')
            if len(parts) == 2:
                return parts[1] == password
        return False

    def close(self):
        try:
            if self.connection:
                self.connection.close()
        except sqlite3.Error as e:
            print(e)