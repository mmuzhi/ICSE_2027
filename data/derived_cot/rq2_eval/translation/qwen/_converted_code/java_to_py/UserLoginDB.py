import sqlite3
import sys

class UserLoginDB:
    def __init__(self, db_name):
        self.connection = None
        try:
            self.connection = sqlite3.connect(db_name)
            self.create_table()
        except sqlite3.Error as e:
            print(e, file=sys.stderr)

    def create_table(self):
        create_table_query = """
        CREATE TABLE IF NOT EXISTS users (
            username TEXT,
            password TEXT
        )
        """
        cursor = self.connection.cursor()
        try:
            cursor.execute(create_table_query)
            self.connection.commit()
        except sqlite3.Error as e:
            print(e, file=sys.stderr)

    def insert_user(self, username, password):
        insert_query = """
        INSERT INTO users (username, password)
        VALUES (?, ?)
        """
        cursor = self.connection.cursor()
        try:
            cursor.execute(insert_query, (username, password))
            self.connection.commit()
        except sqlite3.Error as e:
            print(e, file=sys.stderr)

    def search_user_by_username(self, username):
        search_query = """
        SELECT * FROM users 
        WHERE username = ?
        """
        cursor = self.connection.cursor()
        try:
            cursor.execute(search_query, (username,))
            user_data = cursor.fetchone()
            if user_data:
                return f"{user_data[0]},{user_data[1]}"
            return None
        except sqlite3.Error as e:
            print(e, file=sys.stderr)
            return None

    def delete_user_by_username(self, username):
        delete_query = """
        DELETE FROM users 
        WHERE username = ?
        """
        cursor = self.connection.cursor()
        try:
            cursor.execute(delete_query, (username,))
            self.connection.commit()
        except sqlite3.Error as e:
            print(e, file=sys.stderr)

    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user is not None:
            stored_parts = user.split(',')
            if len(stored_parts) == 2:
                return stored_parts[1] == password
        return False

    def close(self):
        if self.connection:
            try:
                self.connection.close()
            except sqlite3.Error as e:
                print(e, file=sys.stderr)