import sqlite3
import traceback

# Simulate the static initializer from Java: attempt to import the module, print stack trace on failure
try:
    sqlite3  # just reference to ensure it's imported
except Exception:
    traceback.print_exc()


class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        try:
            conn = sqlite3.connect(self.database_name)
            with conn:
                stmt = conn.cursor()
                create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
                stmt.execute(create_table_query)
        except sqlite3.Error:
            traceback.print_exc()

    def insert_into_database(self, table_name: str, data: list) -> None:
        try:
            conn = sqlite3.connect(self.database_name)
            with conn:
                stmt = conn.cursor()
                for item in data:
                    insert_query = (
                        f"INSERT INTO {table_name} (name, age) VALUES ('{item['name']}', {int(item['age'])})"
                    )
                    stmt.execute(insert_query)
        except sqlite3.Error:
            traceback.print_exc()

    def search_database(self, table_name: str, name: str):
        result = []
        try:
            conn = sqlite3.connect(self.database_name)
            with conn:
                stmt = conn.cursor()
                select_query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
                stmt.execute(select_query)
                rows = stmt.fetchall()
                for row in rows:
                    row_dict = {
                        "id": row[0],
                        "name": row[1],
                        "age": row[2]
                    }
                    result.append(row_dict)
        except sqlite3.Error:
            traceback.print_exc()
        return None if not result else result

    def delete_from_database(self, table_name: str, name: str) -> None:
        try:
            conn = sqlite3.connect(self.database_name)
            with conn:
                stmt = conn.cursor()
                delete_query = f"DELETE FROM {table_name} WHERE name = '{name}'"
                stmt.execute(delete_query)
        except sqlite3.Error:
            traceback.print_exc()