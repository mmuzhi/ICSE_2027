import sqlite3
from typing import List, Dict, Union

class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name)
            create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            conn.execute(create_table_query)
            conn.commit()
        except sqlite3.Error as e:
            if conn:
                conn.rollback()
            raise RuntimeError(f"Failed to create table: {str(e)}")
        finally:
            if conn:
                conn.close()

    def insert_into_database(self, table_name: str, data: List[Dict[str, str]]) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name)
            insert_query = "INSERT INTO {} (name, age) VALUES (?, ?)".format(table_name)
            conn.execute(insert_query)
            conn.commit()
            cur = conn.cursor()
            for item in data:
                try:
                    name_val = item['name']
                    age_val = int(item['age'])
                    cur.execute("INSERT INTO {} (name, age) VALUES (?, ?)".format(table_name), (name_val, age_val))
                except (KeyError, ValueError) as e:
                    raise RuntimeError(f"Invalid data format: {str(e)}") from e
            conn.commit()
        except sqlite3.Error as e:
            if conn:
                conn.rollback()
            raise RuntimeError(f"Database error during insert: {str(e)}") from e
        finally:
            if conn:
                conn.close()

    def search_database(self, table_name: str, name: str) -> List[List[str]]:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name)
            query = "SELECT * FROM {} WHERE name = ?".format(table_name)
            cur = conn.cursor()
            cur.execute(query, (name,))
            rows = cur.fetchall()
            return [list(row) for row in rows]
        except sqlite3.Error as e:
            if conn:
                conn.rollback()
            return []
        finally:
            if conn:
                conn.close()

    def delete_from_database(self, table_name: str, name: str) -> None:
        conn = None
        try:
            conn = sqlite3.connect(self.database_name)
            delete_query = "DELETE FROM {} WHERE name = ?".format(table_name)
            conn.execute(delete_query, (name,))
            conn.commit()
        except sqlite3.Error as e:
            if conn:
                conn.rollback()
            raise RuntimeError(f"Failed to delete records: {str(e)}") from e
        finally:
            if conn:
                conn.close()