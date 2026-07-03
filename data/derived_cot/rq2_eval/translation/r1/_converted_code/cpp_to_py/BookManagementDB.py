import sqlite3

class BookManagementDB:
    def __init__(self, db_name):
        try:
            self.connection = sqlite3.connect(db_name)
        except sqlite3.Error as e:
            raise RuntimeError("Failed to open database") from e

    def __del__(self):
        if hasattr(self, 'connection'):
            self.connection.close()

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
            cursor = self.connection.cursor()
            cursor.execute(create_table_sql)
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()

    def add_book(self, title, author):
        insert_sql = "INSERT INTO books (title, author, available) VALUES (?, ?, 1)"
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_sql, (title, author))
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()

    def remove_book(self, id):
        delete_sql = "DELETE FROM books WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()

    def borrow_book(self, id):
        update_sql = "UPDATE books SET available = 0 WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()

    def return_book(self, id):
        update_sql = "UPDATE books SET available = 1 WHERE id = ?"
        try:
            cursor = self.connection.cursor()
            cursor.execute(update_sql, (id,))
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()

    def search_books(self):
        select_sql = "SELECT * FROM books"
        books = []
        try:
            cursor = self.connection.cursor()
            cursor.execute(select_sql)
            rows = cursor.fetchall()
            for row in rows:
                books.append(row)
        except sqlite3.Error as e:
            raise RuntimeError(str(e)) from e
        finally:
            cursor.close()
        return books

    def get_connection(self):
        return self.connection