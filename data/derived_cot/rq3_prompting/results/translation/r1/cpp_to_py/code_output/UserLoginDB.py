import sqlite3
from typing import Optional, Tuple

class UserLoginDB:
    def __init__(self, db_name: str):
        self.connection = None
        self.stmt = None  # not used in Python, but kept for interface parity
        try:
            self.connection = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            raise RuntimeError("Cannot open database: " + str(e))
        self.create_table()

    def __del__(self):
        self.finalize_statement()
        if self.connection is not None:
            self.connection.close()
            self.connection = None

    def finalize_statement(self):
        # Not needed in Python, but kept for interface parity
        pass

    def create_table(self):
        query = """CREATE TABLE IF NOT EXISTS users (
            username TEXT,
            password TEXT
        )"""
        try:
            self.connection.execute(query)
        except sqlite3.Error as e:
            raise RuntimeError("Cannot create table: " + str(e))

    def insert_user(self, username: str, password: str):
        try:
            self.connection.execute(
                "INSERT INTO users (username, password) VALUES (?, ?)",
                (username, password)
            )
            self.connection.commit()
        except sqlite3.Error as e:
            raise RuntimeError("Failed to insert user: " + str(e))

    def search_user_by_username(self, username: str) -> Optional[Tuple[str, str]]:
        try:
            cursor = self.connection.execute(
                "SELECT username, password FROM users WHERE username = ?",
                (username,)
            )
            row = cursor.fetchone()
            if row is not None:
                return (str(row[0]), str(row[1]))
            return None
        except sqlite3.Error as e:
            raise RuntimeError("Failed to search user: " + str(e))

    def delete_user_by_username(self, username: str):
        try:
            self.connection.execute(
                "DELETE FROM users WHERE username = ?",
                (username,)
            )
            self.connection.commit()
        except sqlite3.Error as e:
            raise RuntimeError("Failed to delete user: " + str(e))

    def validate_user_login(self, username: str, password: str) -> bool:
        user = self.search_user_by_username(username)
        if user is not None and user[1] == password:
            return True
        return False

    def close_connection(self):
        if self.connection is not None:
            self.connection.close()
            self.connection = None