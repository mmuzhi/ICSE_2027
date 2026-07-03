import sqlite3
from typing import List, Dict, Optional

class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            cursor.execute(query)
            conn.commit()

    def insert_into_database(self, table_name: str, data: List[Dict[str, object]]) -> None:
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            for item in data:
                name = item["name"]
                age = int(item["age"])  # Cast to int as in Java
                query = f"INSERT INTO {table_name} (name, age) VALUES ('{name}', {age})"
                cursor.execute(query)
            conn.commit()

    def search_database(self, table_name: str, name: str) -> Optional[List[Dict[str, object]]]:
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
            cursor.execute(query)
            columns = [col[0] for col in cursor.description]
            results = cursor.fetchall()
            if not results:
                return None
            rows = []
            for row in results:
                row_dict = dict(zip(columns, row))
                rows.append(row_dict)
            return rows

    def delete_from_database(self, table_name: str, name: str) -> None:
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            query = f"DELETE FROM {table_name} WHERE name = '{name}'"
            cursor.execute(query)
            conn.commit()