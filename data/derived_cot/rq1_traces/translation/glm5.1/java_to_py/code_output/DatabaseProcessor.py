import sqlite3
import traceback
from typing import List, Dict, Optional, Any


class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            create_table_query = (
                f"CREATE TABLE IF NOT EXISTS {table_name} "
                f"(id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            )
            cursor.execute(create_table_query)
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()

    def insert_into_database(self, table_name: str, data: List[Dict[str, Any]]) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            for item in data:
                insert_query = (
                    f"INSERT INTO {table_name} (name, age) VALUES ('{item['name']}', {int(item['age'])})"
                )
                cursor.execute(insert_query)
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()

    def search_database(self, table_name: str, name: str) -> Optional[List[Dict[str, Any]]]:
        result = []
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            select_query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
            cursor.execute(select_query)
            rows = cursor.fetchall()
            for row in rows:
                row_dict = {
                    "id": row[0],
                    "name": row[1],
                    "age": row[2],
                }
                result.append(row_dict)
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()
        return result if result else None

    def delete_from_database(self, table_name: str, name: str) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name, isolation_level=None)
            cursor = conn.cursor()
            delete_query = f"DELETE FROM {table_name} WHERE name = '{name}'"
            cursor.execute(delete_query)
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()