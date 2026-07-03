import sqlite3

class BookManagementDB:

    class Book:

        def __init__(self, id, title, author, available):
            self.id = id
            self.title = title
            self.author = author
            self.available = available

        def getId(self):
            return self.id

        def getTitle(self):
            return self.title

        def getAuthor(self):
            return self.author

        def getAvailable(self):
            return self.available

        def __str__(self):
            return f"Book{{id={self.id}, title='{self.title}', author='{self.author}', available={self.available}}}"

    def __init__(self, db_name):
        self.connection = sqlite3.connect(db_name, isolation_level=None)
        self.connection.row_factory = sqlite3.Row
        self.create_table()

    def create_table(self):
        sql = 'CREATE TABLE IF NOT EXISTS books (\n            id INTEGER PRIMARY KEY AUTOINCREMENT,\n            title TEXT,\n            author TEXT,\n            available INTEGER\n        )'
        with self.connection.cursor() as cursor:
            cursor.execute(sql)

    def add_book(self, title, author):
        sql = 'INSERT INTO books (title, author, available) VALUES (?, ?, 1)'
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (title, author))

    def remove_book(self, bookId):
        sql = 'DELETE FROM books WHERE id = ?'
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def borrow_book(self, bookId):
        sql = 'UPDATE books SET available = 0 WHERE id = ?'
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def return_book(self, bookId):
        sql = 'UPDATE books SET available = 1 WHERE id = ?'
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def search_books(self):
        sql = 'SELECT * FROM books'
        books = []
        with self.connection.cursor() as cursor:
            cursor.execute(sql)
            for row in cursor:
                books.append(self.Book(row['id'], row['title'], row['author'], row['available']))
        return books