import sqlite3
from typing import List

class BookManagementDB:
    def __init__(self, db_name: str):
        self.connection = sqlite3.connect(db_name)
        self.create_table()

    def create_table(self):
        create_table_sql = """
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            author TEXT,
            available INTEGER
        )
        """
        with self.connection:
            self.connection.execute(create_table_sql)

    def add_book(self, title: str, author: str) -> None:
        insert_sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        with self.connection:
            self.connection.execute(insert_sql, (title, author))

    def remove_book(self, book_id: int) -> None:
        delete_sql = "DELETE FROM books WHERE id = ?"
        with self.connection:
            self.connection.execute(delete_sql, (book_id,))

    def borrow_book(self, book_id: int) -> None:
        update_sql = "UPDATE books SET available = 0 WHERE id = ?"
        with self.connection:
            self.connection.execute(update_sql, (book_id,))

    def return_book(self, book_id: int) -> None:
        update_sql = "UPDATE books SET available = 1 WHERE id = ?"
        with self.connection:
            self.connection.execute(update_sql, (book_id,))

    def search_books(self) -> List['Book']:
        select_sql = "SELECT * FROM books"
        books = []
        with self.connection:
            cursor = self.connection.execute(select_sql)
            for row in cursor.fetchall():
                books.append(Book(*row))
        return books

    class Book:
        __slots__ = ('id', 'title', 'author', 'available')

        def __init__(self, id: int, title: str, author: str, available: int):
            self.id = id
            self.title = title
            self.author = author
            self.available = available

        def __repr__(self):
            return f"Book(id={self.id}, title='{self.title}', author='{self.author}', available={self.available})"

# Example usage
if __name__ == "__main__":
    db = BookManagementDB("library.db")
    db.add_book("Python Programming", "Eric Matthes")
    print(db.search_books())