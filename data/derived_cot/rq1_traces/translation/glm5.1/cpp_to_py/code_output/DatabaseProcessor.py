import sqlite3
from typing import List, Dict

class DatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def open_database(self) -> sqlite3.Connection:
        try:
            # isolation_level=None enables autocommit, matching the C++ sqlite3 default behavior
            return sqlite3.connect(self.database_name, isolation_level=None)
        except sqlite3.OperationalError:
            raise RuntimeError("Failed to open database")

    def create_table(self, table_name: str, key1: str, key2: str) -> None:
        db = self.open_database()
        create_table_query = f"CREATE TABLE IF NOT EXISTS {table_name} (id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
        try:
            cursor = db.cursor()
            cursor.execute(create_table_query)
        except sqlite3.DatabaseError as e:
            raise RuntimeError(f"Failed to create table: {e}")
        finally:
            db.close()

    def insert_into_database(self, table_name: str, data: List[Dict[str, str]]) -> None:
        db = self.open_database()
        insert_query = f"INSERT INTO {table_name} (name, age) VALUES (?, ?)"
        cursor = db.cursor()
        
        try:
            for item in data:
                # item.at() throws std::out_of_range if missing; Python dict[] throws KeyError
                name = item["name"]
                # std::stoi throws std::invalid_argument; Python int() throws ValueError
                age = int(item["age"])
                
                try:
                    cursor.execute(insert_query, (name, age))
                except sqlite3.OperationalError as e:
                    # OperationalError typically maps to preparation failures in SQLite
                    raise RuntimeError(f"Failed to prepare statement: {e}")
                except sqlite3.DatabaseError as e:
                    # Other DatabaseErrors (like IntegrityError) map to execution failures
                    raise RuntimeError(f"Failed to execute statement: {e}")
        finally:
            db.close()

    def search_database(self, table_name: str, name: str) -> List[List[str]]:
        result = []
        
        try:
            db = sqlite3.connect(self.database_name, isolation_level=None)
        except sqlite3.OperationalError:
            # Matches C++ behavior of returning empty list on open failure
            return result

        query = f"SELECT * FROM {table_name} WHERE name = ?"
        try:
            cursor = db.cursor()
            cursor.execute(query, (name,))
            rows = cursor.fetchall()
            
            for row in rows:
                str_row = []
                for col in row:
                    # sqlite3_column_text returns "" for NULL, and stringifies integers
                    if col is None:
                        str_row.append("")
                    else:
                        str_row.append(str(col))
                result.append(str_row)
        except sqlite3.DatabaseError:
            # Matches C++ behavior of returning empty list on prepare failure
            db.close()
            return result

        db.close()
        return result

    def delete_from_database(self, table_name: str, name: str) -> None:
        db = self.open_database()
        delete_query = f"DELETE FROM {table_name} WHERE name = ?"
        cursor = db.cursor()
        
        try:
            cursor.execute(delete_query, (name,))
        except sqlite3.OperationalError as e:
            raise RuntimeError(f"Failed to prepare statement: {e}")
        except sqlite3.DatabaseError as e:
            raise RuntimeError(f"Failed to execute statement: {e}")
        finally:
            db.close()