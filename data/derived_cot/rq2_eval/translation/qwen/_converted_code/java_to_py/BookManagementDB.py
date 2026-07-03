import sqlite3
from typing import List

class Book:

    def __init__(self, id: int, title: str, author: str, available: int):
        self.id = id
        self.title = title
        self.author = author
        self.available = available

    def __repr__(self):
        return f"Book(id={self.id}, title='{self.title}', author='{self.author}', available={self.available})"

class BookManagementDB:

    def __init__(self, db_name: str):
        self.connection = sqlite3.connect(db_name)
        self.create_table()

    def create_table(self):
        create_table_sql = '\n        CREATE TABLE IF NOT EXISTS books (\n            id INTEGER PRIMARY KEY AUTOINCREMENT,\n            title TEXT,\n            author TEXT,\n            available INTEGER\n        )\n        '
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_sql)
            self.connection.commit()
        except sqlite3.Error as e:
            self.connection.rollback()
            raise e

    def add_book(self, title: str, author: str):
        insert_sql = 'INSERT INTO books (title, author, available) VALUES (?, ?, 1)'
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_sql, (title, author))
            self.connection.commit()
        except sqlite3.Error as e:
            self.connection.rollback()
            raise e

    def remove_book(self, book_id: int):
        delete_sql = 'DELETE FROM books WHERE id = ?'
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_sql, (book_id,))
            self.connection.commit()
        except sqlite3.Error as e:
            self.connection.rollback()
            raise e

    def borrow_book(self, book_id: int):
        update_sql = 'UPDATE books SET available = 0 WHERE id = ?'
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (book_id,))
            self.connection.commit()
        except sqlite3.Error as e:
            self.connection.rollback()
            raise e

    def return_book(self, book_id: int):
        update_sql = 'UPDATE books SET available = 1 WHERE id = ?'
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (book_id,))
            self.connection.commit()
        except sqlite3.Error as e:
            self.connection.rollback()
            raise e

    def search_books(self) -> List[Book]:
        select_sql = 'SELECT * FROM books'
        books = []
        try:
            cursor = self.connection.cursor()
            cursor.execute(select_sql)
            for row in cursor.fetchall():
                books.append(Book(*row))
        except sqlite3.Error as e:
            raise e
        return books