import sqlite3


class DatabaseProcessor:
    def __init__(self, database_name):
        self.database_name = database_name

    def open_database(self):
        try:
            db = sqlite3.connect(self.database_name, isolation_level=None)
            return db
        except sqlite3.Error:
            raise RuntimeError("Failed to open database")

    def create_table(self, table_name, key1, key2):
        db = self.open_database()
        try:
            create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            cursor = db.cursor()
            cursor.execute(create_table_query)
        except sqlite3.Error as e:
            db.close()
            raise RuntimeError(f"Failed to create table: {e}")
        db.close()

    def insert_into_database(self, table_name, data):
        db = self.open_database()
        cursor = db.cursor()
        insert_query = f"INSERT INTO {table_name} (name, age) VALUES (?, ?)"
        first = True
        try:
            for item in data:
                name_val = item["name"]
                age_val = int(item["age"])
                cursor.execute(insert_query, (name_val, age_val))
                first = False
        except sqlite3.Error as e:
            db.close()
            if first:
                raise RuntimeError(f"Failed to prepare statement: {e}")
            else:
                raise RuntimeError(f"Failed to execute statement: {e}")
        except (ValueError, KeyError):
            db.close()
            raise
        db.close()

    def search_database(self, table_name, name):
        result = []
        try:
            db = sqlite3.connect(self.database_name, isolation_level=None)
        except sqlite3.Error:
            return result
        try:
            query = f"SELECT * FROM {table_name} WHERE name = ?"
            cursor = db.cursor()
            cursor.execute(query, (name,))
            rows = cursor.fetchall()
            for row in rows:
                row_list = []
                for val in row:
                    row_list.append(str(val) if val is not None else "")
                result.append(row_list)
        except sqlite3.Error:
            db.close()
            return result
        db.close()
        return result

    def delete_from_database(self, table_name, name):
        db = self.open_database()
        cursor = db.cursor()
        delete_query = f"DELETE FROM {table_name} WHERE name = ?"
        try:
            cursor.execute(delete_query, (name,))
        except sqlite3.Error as e:
            db.close()
            raise RuntimeError(f"Failed to prepare statement: {e}")
        db.close()