import sqlite3

class DatabaseProcessor:
    def __init__(self, database_name):
        self.database_name = database_name

    def create_table(self, table_name, key1, key2):
        conn = sqlite3.connect(self.database_name)
        try:
            cursor = conn.cursor()
            query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            cursor.execute(query)
            conn.commit()
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {e}")
        finally:
            conn.close()

    def insert_into_database(self, table_name, data):
        conn = sqlite3.connect(self.database_name)
        try:
            cursor = conn.cursor()
            query = f"INSERT INTO {table_name} (name, age) VALUES (?, ?)"
            for item in data:
                name_val = item["name"]
                age_val = item["age"]
                cursor.execute(query, (name_val, int(age_val)))
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Failed to insert: {e}")
        except KeyError as e:
            conn.rollback()
            raise RuntimeError(f"Missing key in data: {e}")
        finally:
            conn.close()

    def search_database(self, table_name, name):
        result = []
        try:
            conn = sqlite3.connect(self.database_name)
            cursor = conn.cursor()
            query = f"SELECT * FROM {table_name} WHERE name = ?"
            cursor.execute(query, (name,))
            try:
                for row in cursor:
                    str_row = [str(item) for item in row]
                    result.append(str_row)
            except sqlite3.Error:
                pass
        except sqlite3.Error:
            return []
        finally:
            if conn:
                conn.close()
        return result

    def delete_from_database(self, table_name, name):
        conn = sqlite3.connect(self.database_name)
        try:
            cursor = conn.cursor()
            query = f"DELETE FROM {table_name} WHERE name = ?"
            cursor.execute(query, (name,))
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Failed to delete: {e}")
        finally:
            conn.close()