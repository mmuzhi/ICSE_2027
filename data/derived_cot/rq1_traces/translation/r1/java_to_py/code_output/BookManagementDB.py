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
        self.createTable()

    def createTable(self):
        sql = """CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT,
            author TEXT,
            available INTEGER
        )"""
        with self.connection.cursor() as cursor:
            cursor.execute(sql)

    def addBook(self, title, author):
        sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (title, author))

    def removeBook(self, bookId):
        sql = "DELETE FROM books WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def borrowBook(self, bookId):
        sql = "UPDATE books SET available = 0 WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def returnBook(self, bookId):
        sql = "UPDATE books SET available = 1 WHERE id = ?"
        with self.connection.cursor() as cursor:
            cursor.execute(sql, (bookId,))

    def searchBooks(self):
        sql = "SELECT * FROM books"
        books = []
        with self.connection.cursor() as cursor:
            cursor.execute(sql)
            for row in cursor:
                books.append(self.Book(row['id'], row['title'], row['author'], row['available']))
        return books