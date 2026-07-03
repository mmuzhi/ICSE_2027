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
        self.createTable()

    def createTable(self):
        cursor = self.connection.cursor()
        try:
            cursor.execute("""
                CREATE TABLE IF NOT EXISTS books (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    title TEXT,
                    author TEXT,
                    available INTEGER
                )
            """)
        finally:
            cursor.close()

    def addBook(self, title, author):
        cursor = self.connection.cursor()
        try:
            cursor.execute("INSERT INTO books (title, author, available) VALUES (?, ?, 1)", (title, author))
        finally:
            cursor.close()

    def removeBook(self, bookId):
        cursor = self.connection.cursor()
        try:
            cursor.execute("DELETE FROM books WHERE id = ?", (bookId,))
        finally:
            cursor.close()

    def borrowBook(self, bookId):
        cursor = self.connection.cursor()
        try:
            cursor.execute("UPDATE books SET available = 0 WHERE id = ?", (bookId,))
        finally:
            cursor.close()

    def returnBook(self, bookId):
        cursor = self.connection.cursor()
        try:
            cursor.execute("UPDATE books SET available = 1 WHERE id = ?", (bookId,))
        finally:
            cursor.close()

    def searchBooks(self):
        cursor = self.connection.cursor()
        try:
            cursor.execute("SELECT * FROM books")
            books = []
            for row in cursor:
                id, title, author, available = row
                books.append(self.Book(id, title, author, available))
            return books
        finally:
            cursor.close()