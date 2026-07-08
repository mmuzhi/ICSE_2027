import sqlite3
import traceback

class UserLoginDB:
    def __init__(self, db_name):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self._create_table()
        except sqlite3.Error as e:
            traceback.print_exc()

    def _create_table(self):
        create_table_query = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT)"
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute(create_table_query)
            self.connection.commit()
        except sqlite3.Error as e:
            traceback.print_exc()
        finally:
            if cursor:
                cursor.close()

    def insert_user(self, username, password):
        insert_query = "INSERT INTO users (username, password) VALUES (?, ?)"
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute(insert_query, (username, password))
            self.connection.commit()
        except sqlite3.Error as e:
            traceback.print_exc()
        finally:
            if cursor:
                cursor.close()

    def search_user_by_username(self, username):
        search_query = "SELECT * FROM users WHERE username = ?"
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute(search_query, (username,))
            row = cursor.fetchone()
            if row:
                return f"{row[0]},{row[1]}"
        except sqlite3.Error as e:
            traceback.print_exc()
        finally:
            if cursor:
                cursor.close()
        return None

    def delete_user_by_username(self, username):
        delete_query = "DELETE FROM users WHERE username = ?"
        cursor = None
        try:
            cursor = self.connection.cursor()
            cursor.execute(delete_query, (username,))
            self.connection.commit()
        except sqlite3.Error as e:
            traceback.print_exc()
        finally:
            if cursor:
                cursor.close()

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user is not None:
            parts = user.split(",")
            # Identical behavior: If there is no comma in the string, 
            # this will throw an IndexError (equivalent to Java's ArrayIndexOutOfBoundsException)
            return parts[1] == password
        return False

    def close(self):
        try:
            if self.connection is not None:
                self.connection.close()
        except sqlite3.Error as e:
            traceback.print_exc()