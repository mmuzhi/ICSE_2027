import sqlite3
import sys

class UserLoginDB:
    def __init__(self, db_name):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot open database: {e}")

    def __del__(self):
        self.close()

    def close(self):
        if self.connection is not None:
            self.connection.close()
            self.connection = None

    def create_table(self):
        create_table_query = """
            CREATE TABLE IF NOT EXISTS users (
                username TEXT,
                password TEXT
            )
        """
        try:
            self.connection.execute(create_table_query)
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot create table: {e}")

    def insert_user(self, username, password):
        query = "INSERT INTO users (username, password) VALUES (?, ?)"
        try:
            self.connection.execute(query, (username, password))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert user: {e}")

    def search_user_by_username(self, username):
        query = "SELECT username, password FROM users WHERE username = ?"
        try:
            cursor = self.connection.execute(query, (username,))
            row = cursor.fetchone()
            if row is None:
                return None
            return (row[0], row[1])
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search user: {e}")

    def delete_user_by_username(self, username):
        query = "DELETE FROM users WHERE username = ?"
        try:
            self.connection.execute(query, (username,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete user: {e}")

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user is None:
            return False
        return user[1] == password