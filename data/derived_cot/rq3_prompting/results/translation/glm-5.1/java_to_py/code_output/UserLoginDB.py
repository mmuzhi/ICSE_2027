import sqlite3
import traceback

class UserLoginDB:
    def __init__(self, db_name):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self._create_table()
        except sqlite3.Error:
            traceback.print_exc()

    def _create_table(self):
        create_table_query = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_query)
        except sqlite3.Error:
            traceback.print_exc()

    def insert_user(self, username, password):
        insert_query = "INSERT INTO users (username, password) VALUES (?, ?)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_query, (username, password))
            self.connection.commit()
        except sqlite3.Error:
            traceback.print_exc()

    def search_user_by_username(self, username):
        search_query = "SELECT * FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(search_query, (username,))
            row = cursor.fetchone()
            if row is not None:
                u = "null" if row[0] is None else row[0]
                p = "null" if row[1] is None else row[1]
                return f"{u},{p}"
        except sqlite3.Error:
            traceback.print_exc()
        return None

    def delete_user_by_username(self, username):
        delete_query = "DELETE FROM users WHERE username = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_query, (username,))
            self.connection.commit()
        except sqlite3.Error:
            traceback.print_exc()

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user is not None:
            parts = user.split(",")
            # Mimic Java's String.split() which discards trailing empty strings
            while parts and parts[-1] == '':
                parts.pop()
            return parts[1] == password
        return False

    def close(self):
        try:
            if self.connection is not None:
                self.connection.close()
        except sqlite3.Error:
            traceback.print_exc()