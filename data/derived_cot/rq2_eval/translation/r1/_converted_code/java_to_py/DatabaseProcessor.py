import sqlite3

class DatabaseProcessor:
    def __init__(self, database_name):
        self.database_name = database_name
    
    def create_table(self, table_name, key1, key2):
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            cursor.execute(create_table_query)
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()
    
    def insert_into_database(self, table_name, data):
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            for item in data:
                name = item['name']
                age = item['age']
                insert_query = f"INSERT INTO {table_name} (name, age) VALUES ('{name}', {age})"
                cursor.execute(insert_query)
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()
    
    def search_database(self, table_name, name):
        conn = None
        result = []
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            select_query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
            cursor.execute(select_query)
            rows = cursor.fetchall()
            for row in rows:
                row_map = {
                    'id': row[0],
                    'name': row[1],
                    'age': row[2]
                }
                result.append(row_map)
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()
        if not result:
            return None
        return result
    
    def delete_from_database(self, table_name, name):
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            delete_query = f"DELETE FROM {table_name} WHERE name = '{name}'"
            cursor.execute(delete_query)
        except sqlite3.Error as e:
            print(e)
        finally:
            if conn:
                conn.close()