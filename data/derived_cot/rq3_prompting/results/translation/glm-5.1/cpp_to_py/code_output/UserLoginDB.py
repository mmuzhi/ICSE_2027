import sqlite3
from typing import Optional, Tuple


class UserLoginDB:
    def __init__(self, db_name: str):
        self.connection: Optional[sqlite3.Connection] = None
        try:
            self.connection = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot open database: {e}")
        self.create_table()

    def __del__(self):
        self.close_connection()

    def insert_user(self, username: str, password: str):
        try:
            cursor = self.connection.cursor()
            cursor.execute(
                "INSERT INTO users (username, password) VALUES (?, ?)",
                (username, password),
            )
            cursor.close()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert user: {e}")

    def search_user_by_username(self, username: str) -> Optional[Tuple[str, str]]:
        try:
            cursor = self.connection.cursor()
            cursor.execute(
                "SELECT username, password FROM users WHERE username = ?",
                (username,),
            )
            row = cursor.fetchone()
            cursor.close()
            if row is not None:
                return (row[0], row[1])
            return None
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search user: {e}")

    def delete_user_by_username(self, username: str):
        try:
            cursor = self.connection.cursor()
            cursor.execute(
                "DELETE FROM users WHERE username = ?", (username,)
            )
            cursor.close()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete user: {e}")

    def validate_user_login(self, username: str, password: str) -> bool:
        user = self.search_user_by_username(username)
        if user is not None and user[1] == password:
            return True
        return False

    def close_connection(self):
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
            cursor = self.connection.cursor()
            cursor.execute(create_table_query)
            cursor.close()
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot create table: {e}")