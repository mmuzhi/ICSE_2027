import sqlite3
from typing import List, Tuple

class BookManagementDB:
    def __init__(self, db_name: str):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to open database: {e}")

    def __del__(self):
        self.close()

    def close(self):
        if self.connection is not None:
            self.connection.close()
            self.connection = None

    def create_table(self):
        create_table_sql = """
            CREATE TABLE IF NOT EXISTS books (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                author TEXT NOT NULL,
                available INTEGER NOT NULL
            )
        """
        try:
            self.connection.execute(create_table_sql)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {e}")

    def add_book(self, title: str, author: str):
        insert_sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_sql, (title, author))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to add book: {e}")
        finally:
            if 'cursor' in locals():
                cursor.close()

    def remove_book(self, id: int):
        delete_sql = "DELETE FROM books WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to remove book: {e}")
        finally:
            if 'cursor' in locals():
                cursor.close()

    def borrow_book(self, id: int):
        update_sql = "UPDATE books SET available = 0 WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to borrow book: {e}")
        finally:
            if 'cursor' in locals():
                cursor.close()

    def return_book(self, id: int):
        update_sql = "UPDATE books SET available = 1 WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to return book: {e}")
        finally:
            if 'cursor' in locals():
                cursor.close()

    def search_books(self) -> List[Tuple[int, str, str, int]]:
        select_sql = "SELECT * FROM books"
        try:
            cursor = self.connection.cursor()
            cursor.execute(select_sql)
            books = []
            for row in cursor:
                id_val = row[0]
                title = row[1]
                author = row[2]
                available = row[3]
                books.append((id_val, title, author, available))
            return books
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search books: {e}")
        finally:
            if 'cursor' in locals():
                cursor.close()

    def get_connection(self):
        return self.connection