import sqlite3
from typing import List


class BookManagementDB:
    """Translation of the Java BookManagementDB class using SQLite."""

    class Book:
        """Equivalent of the Java static inner class Book."""
        def __init__(self, id_: int, title: str, author: str, available: int):
            self._id = id_
            self._title = title
            self._author = author
            self._available = available

        def get_id(self) -> int:
            return self._id

        def get_title(self) -> str:
            return self._title

        def get_author(self) -> str:
            return self._author

        def get_available(self) -> int:
            return self._available

        def __str__(self) -> str:
            return (f"Book{{id={self._id}, title='{self._title}', "
                    f"author='{self._author}', available={self._available}}}")

        # Keep alias for toString-like behaviour
        __repr__ = __str__

    def __init__(self, db_name: str) -> None:
        # Enable auto-commit to match Java's default behaviour
        self.connection = sqlite3.connect(db_name, isolation_level=None)
        self.create_table()

    def create_table(self) -> None:
        """Create the books table if it does not exist."""
        create_sql = (
            "CREATE TABLE IF NOT EXISTS books ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "title TEXT, "
            "author TEXT, "
            "available INTEGER"
            ")"
        )
        with self.connection.cursor() as cursor:
            cursor.execute(create_sql)

    def add_book(self, title: str, author: str) -> None:
        """Add a new book with available = 1."""
        insert_sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        with self.connection.cursor() as cursor:
            cursor.execute(insert_sql, (title, author))

    def remove_book(self, book_id: int) -> None:
        """Delete a book by its id."""
        delete_sql = "DELETE FROM books WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(delete_sql, (book_id,))

    def borrow_book(self, book_id: int) -> None:
        """Mark a book as borrowed (available = 0)."""
        update_sql = "UPDATE books SET available = 0 WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(update_sql, (book_id,))

    def return_book(self, book_id: int) -> None:
        """Mark a book as returned (available = 1)."""
        update_sql = "UPDATE books SET available = 1 WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(update_sql, (book_id,))

    def search_books(self) -> List[Book]:
        """Return all books as a list of Book objects."""
        select_sql = "SELECT id, title, author, available FROM books"
        books = []
        # Use row factory to access columns by name (like ResultSet)
        self.connection.row_factory = sqlite3.Row
        with self.connection.cursor() as cursor:
            cursor.execute(select_sql)
            for row in cursor:
                book = BookManagementDB.Book(
                    id_=row["id"],
                    title=row["title"],
                    author=row["author"],
                    available=row["available"]
                )
                books.append(book)
        return books