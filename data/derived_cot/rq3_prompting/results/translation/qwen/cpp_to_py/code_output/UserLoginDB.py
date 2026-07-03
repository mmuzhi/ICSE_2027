import sqlite3
from typing import Tuple, Optional

class UserLoginDB:
    def __init__(self, db_name: str):
        self.connection = None
        self.cursor = None
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot open database: {str(e)}")
    
    def __del__(self):
        self.close_connection()
    
    def insert_user(self, username: str, password: str) -> None:
        try:
            self.cursor.execute(
                "INSERT INTO users (username, password) VALUES (?, ?)",
                (username, password)
            )
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert user: {str(e)}")
    
    def search_user_by_username(self, username: str) -> Optional[Tuple[str, str]]:
        cursor = self.connection.execute(
            "SELECT username, password FROM users WHERE username = ?",
            (username,)
        )
        row = cursor.fetchone()
        if row is None:
            return None
        return (row[0], row[1])
    
    def delete_user_by_username(self, username: str) -> None:
        try:
            self.cursor.execute(
                "DELETE FROM users WHERE username = ?",
                (username,)
            )
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete user: {str(e)}")
    
    def validate_user_login(self, username: str, password: str) -> bool:
        user = self.search_user_by_username(username)
        if user and user[1] == password:
            return True
        return False
    
    def close_connection(self) -> None:
        if self.connection:
            self.connection.close()
            self.connection = None
            self.cursor = None
    
    def create_table(self) -> None:
        try:
            self.cursor.execute(
                """CREATE TABLE IF NOT EXISTS users (
                    username TEXT,
                    password TEXT
                )"""
            )
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot create table: {str(e)}")