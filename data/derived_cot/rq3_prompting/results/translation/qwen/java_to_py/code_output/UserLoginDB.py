import sqlite3

class UserLoginDB:
    def __init__(self, db_name):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            print(f"An error occurred: {e}")

    def create_table(self):
        create_table_query = """CREATE TABLE IF NOT EXISTS users (
            username TEXT,
            password TEXT
        )"""
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_query)
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"An error occurred during table creation: {e}")

    def insert_user(self, username, password):
        insert_query = "INSERT INTO users (username, password) VALUES (?, ?)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_query, (username, password))
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"An error occurred during insert: {e}")

    def search_user_by_username(self, username):
        search_query = "SELECT * FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(search_query, (username,))
            user_data = cursor.fetchone()
            if user_data:
                return f"{user_data[0]},{user_data[1]}"
            return None
        except sqlite3.Error as e:
            print(f"An error occurred during search: {e}")
            return None

    def delete_user_by_username(self, username):
        delete_query = "DELETE FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_query, (username,))
            self.connection.commit()
        except sqlite3.Error as e:
            print(f"An error occurred during delete: {e}")

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user is not None:
            parts = user.split(',')
            if len(parts) >= 2 and parts[1] == password:
                return True
        return False

    def close(self):
        if self.connection:
            try:
                self.connection.close()
            except sqlite3.Error as e:
                print(f"An error occurred during close: {e}")