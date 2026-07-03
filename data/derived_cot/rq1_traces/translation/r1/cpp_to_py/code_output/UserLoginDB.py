import sqlite3

class UserLoginDB:
    def __init__(self, db_name):
        self.conn = None
        try:
            self.conn = sqlite3.connect(db_name, isolation_level=None)
            self.create_table()
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot open database: {str(e)}")
    
    def __del__(self):
        self.close_connection()
    
    def close_connection(self):
        if self.conn:
            try:
                self.conn.close()
            except sqlite3.Error:
                pass
            self.conn = None
    
    def create_table(self):
        query = """
            CREATE TABLE IF NOT EXISTS users (
                username TEXT,
                password TEXT
            )
        """
        cursor = self.conn.cursor()
        try:
            cursor.execute(query)
        except sqlite3.Error as e:
            raise RuntimeError(f"Cannot create table: {str(e)}")
        finally:
            cursor.close()
    
    def insert_user(self, username, password):
        cursor = self.conn.cursor()
        try:
            cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, password))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to insert user: {str(e)}")
        finally:
            cursor.close()
    
    def search_user_by_username(self, username):
        cursor = self.conn.cursor()
        try:
            cursor.execute("SELECT username, password FROM users WHERE username = ?", (username,))
            row = cursor.fetchone()
            if row:
                return (row[0], row[1])
            return None
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to search user: {str(e)}")
        finally:
            cursor.close()
    
    def delete_user_by_username(self, username):
        cursor = self.conn.cursor()
        try:
            cursor.execute("DELETE FROM users WHERE username = ?", (username,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to delete user: {str(e)}")
        finally:
            cursor.close()
    
    def validate_user_login(self, username, password):
        user = self.search_user_by_username(username)
        if user and user[1] == password:
            return True
        return False