import sqlite3
from typing import Optional, Tuple

class UserLoginDB:
    def __init__(self, db_name: str):
        self.connection: Optional[sqlite3.Connection] = None
        
        try:
            # Connect to the SQLite database
            self.connection = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            # Match C++ exception behavior
            raise RuntimeError(f"Cannot open database: {e}") from e
            
        self.create_table()

    def __del__(self):
        # Matches C++ destructor behavior
        self.close_connection()

    def insert_user(self, username: str, password: str) -> None:
        try:
            # Using parameterized queries to match sqlite3_bind_text behavior
            self.connection.execute(
                "INSERT INTO users (username, password) VALUES (?, ?)",
                (username, password)
            )
            # Commit to ensure data is saved immediately (matching C++ autocommit behavior)
            self.connection.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert user: {e}") from e

    def search_user_by_username(self, username: str) -> Optional[Tuple[str, str]]:
        try:
            cursor = self.connection.execute(
                "SELECT username, password FROM users WHERE username = ?",
                (username,)
            )
            row = cursor.fetchone()
            if row:
                # Returns a tuple of (username, password) if found, None otherwise
                # This perfectly matches the unique_ptr<tuple<string, string>> behavior
                return (row[0], row[1])
            return None
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search user: {e}") from e

    def delete_user_by_username(self, username: str) -> None:
        try:
            self.connection.execute(
                "DELETE FROM users WHERE username = ?",
                (username,)
            )
            self.connection.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete user: {e}") from e

    def validate_user_login(self, username: str, password: str) -> bool:
        user = self.search_user_by_username(username)
        if user is not None and user[1] == password:
            return True
        return False

    def close_connection(self) -> None:
        if self.connection:
            self.connection.close()
            self.connection = None

    def create_table(self) -> None:
        create_table_query = """
            CREATE TABLE IF NOT EXISTS users (
                username TEXT,
                password TEXT
            )
        """
        try:
            self.connection.execute(create_table_query)
            self.connection.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot create table: {e}") from e