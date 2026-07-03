import sqlite3
from typing import List, Dict, Optional, Any

class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                create_table_query = (
                    f"CREATE TABLE IF NOT EXISTS {table_name} "
                    f"(id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
                )
                cursor.execute(create_table_query)
                conn.commit()
        except sqlite3.Error as e:
            print(f"SQLite error: {e}")

    def insert_into_database(self, table_name: str, data: List[Dict[str, Any]]) -> None:
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                for item in data:
                    name_val = item.get('name', 'NULL')
                    age_val = item.get('age', 0)
                    insert_query = (
                        f"INSERT INTO {table_name} (name, age) "
                        f"VALUES ('{name_val}', {age_val})"
                    )
                    cursor.execute(insert_query)
                conn.commit()
        except sqlite3.Error as e:
            print(f"SQLite error during insert: {e}")

    def search_database(self, table_name: str, name: str) -> Optional[List[Dict[str, Any]]]:
        result: List[Dict[str, Any]] = []
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                select_query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
                cursor.execute(select_query)
                for row in cursor.fetchall():
                    row_dict = {'id': row[0], 'name': row[1], 'age': row[2]}
                    result.append(row_dict)
        except sqlite3.Error as e:
            print(f"SQLite error during search: {e}")
        return None if not result else result

    def delete_from_database(self, table_name: str, name: str) -> None:
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                delete_query = f"DELETE FROM {table_name} WHERE name = '{name}'"
                cursor.execute(delete_query)
                conn.commit()
        except sqlite3.Error as e:
            print(f"SQLite error during delete: {e}")