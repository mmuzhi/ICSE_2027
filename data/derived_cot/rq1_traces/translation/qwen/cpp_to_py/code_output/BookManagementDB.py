import sqlite3
import sys

class BookManagementDB:
    def __init__(self, db_name):
        self.conn = None
        try:
            self.conn = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to open database: {e}")

    def __del__(self):
        if self.conn is not None:
            self.conn.close()

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
            cursor = self.conn.cursor()
            cursor.execute(create_table_sql)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {e}")

    def add_book(self, title, author):
        insert_sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        try:
            cursor = self.conn.cursor()
            cursor.execute(insert_sql, (title, author))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to add book: {e}")

    def remove_book(self, id):
        delete_sql = "DELETE FROM books WHERE id = ?"
        try:
            cursor = self.conn.cursor()
            cursor.execute(delete_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to remove book: {e}")

    def borrow_book(self, id):
        update_sql = "UPDATE books SET available = 0 WHERE id = ?"
        try:
            cursor = self.conn.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to borrow book: {e}")

    def return_book(self, id):
        update_sql = "UPDATE books SET available = 1 WHERE id = ?"
        try:
            cursor = self.conn.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to return book: {e}")

    def search_books(self):
        select_sql = "SELECT * FROM books"
        try:
            cursor = self.conn.cursor()
            cursor.execute(select_sql)
            books = []
            for row in cursor.fetchall():
                book_id = row[0]
                title = row[1]
                author = row[2]
                available = row[3]
                books.append((book_id, title, author, available))
            return books
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search books: {e}")

    def get_connection(self):
        return self.conn