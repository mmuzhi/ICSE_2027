import sqlite3


class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def _open_database(self) -> sqlite3.Connection:
        try:
            conn = sqlite3.connect(self.database_name)
            conn.isolation_level = None  # autocommit mode, matches C++ default behavior
            return conn
        except sqlite3.Error:
            raise RuntimeError("Failed to open database")

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        conn = self._open_database()
        try:
            query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
            conn.execute(query)
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to create table: {e}")
        finally:
            conn.close()

    def insert_into_database(self, table_name: str, data: list[dict[str, str]]) -> None:
        conn = self._open_database()
        try:
            insert_query = f"INSERT INTO {table_name} (name, age) VALUES (?, ?)"
            cursor = conn.cursor()
            for item in data:
                name = item["name"]          # raises KeyError if missing (matches std::out_of_range)
                age = int(item["age"])       # raises ValueError if invalid (matches std::invalid_argument)
                cursor.execute(insert_query, (name, age))
        except (sqlite3.Error, KeyError, ValueError):
            # exceptions propagate after closing (like C++ throws after finalize+close)
            raise
        finally:
            conn.close()

    def search_database(self, table_name: str, name: str) -> list[list[str]]:
        try:
            conn = self._open_database()
        except RuntimeError:
            return []

        try:
            query = f"SELECT * FROM {table_name} WHERE name = ?"
            cursor = conn.cursor()
            cursor.execute(query, (name,))
            rows = cursor.fetchall()
            result = []
            for row in rows:
                result.append([str(val) if val is not None else "" for val in row])
            return result
        except sqlite3.Error:
            return []
        finally:
            conn.close()

    def delete_from_database(self, table_name: str, name: str) -> None:
        conn = self._open_database()
        try:
            query = f"DELETE FROM {table_name} WHERE name = ?"
            cursor = conn.cursor()
            cursor.execute(query, (name,))
        except sqlite3.Error as e:
            raise RuntimeError(f"Failed to execute statement: {e}")
        finally:
            conn.close()