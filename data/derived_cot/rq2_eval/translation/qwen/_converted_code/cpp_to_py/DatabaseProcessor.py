import sqlite3
from typing import List, Dict, Any

class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        conn = sqlite3.connect(self.database_name)
        query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
        try:
            conn.execute(query)
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Failed to create table: {e}") from e
        finally:
            conn.close()

    def insert_into_database(self, table_name: str, data: List[Dict[str, Any]]) -> None:
        conn = sqlite3.connect(self.database_name)
        query = "INSERT INTO {} (name, age) VALUES (?, ?)".format(table_name)
        try:
            cur = conn.cursor()
            cur.execute(query)
            for item in data:
                name_val = item.get('name', '')
                age_val = item.get('age', 0)
                try:
                    age_val = int(age_val)
                except (ValueError, TypeError):
                    raise RuntimeError("Invalid age value") from None
                cur.execute("SELECT 1 FROM {} WHERE name = ? LIMIT 1".format(table_name), (name_val,))
                if not cur.fetchone():
                    cur.execute("INSERT INTO {} (name, age) VALUES (?, ?)".format(table_name), (name_val, age_val))
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Database error: {e}") from e
        finally:
            conn.close()

    def search_database(self, table_name: str, name: str) -> List[List[str]]:
        conn = sqlite3.connect(self.database_name)
        query = "SELECT * FROM {} WHERE name = ?".format(table_name)
        try:
            cur = conn.cursor()
            cur.execute(query, (name,))
            result = [list(row) for row in cur.fetchall()]
            return result
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Database error: {e}") from e
        finally:
            conn.close()

    def delete_from_database(self, table_name: str, name: str) -> None:
        conn = sqlite3.connect(self.database_name)
        query = "DELETE FROM {} WHERE name = ?".format(table_name)
        try:
            cur = conn.cursor()
            cur.execute(query, (name,))
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise RuntimeError(f"Database error: {e}") from e
        finally:
            conn.close()