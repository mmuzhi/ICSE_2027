import sqlite3
import traceback


class DatabaseProcessor:

    def __init__(self, database_name):
        self.database_name = database_name

    def create_table(self, table_name, key1, key2):
        try:
            conn = sqlite3.connect(self.database_name)
            try:
                cursor = conn.cursor()
                create_table_query = (
                    f"CREATE TABLE IF NOT EXISTS {table_name} "
                    f"(id INTEGER PRIMARY KEY, {key1} TEXT, {key2} INTEGER)"
                )
                cursor.execute(create_table_query)
                conn.commit()
            finally:
                conn.close()
        except sqlite3.Error:
            traceback.print_exc()

    def insert_into_database(self, table_name, data):
        try:
            conn = sqlite3.connect(self.database_name)
            try:
                cursor = conn.cursor()
                for item in data:
                    insert_query = (
                        f"INSERT INTO {table_name} (name, age) "
                        f"VALUES ('{item['name']}', {int(item['age'])})"
                    )
                    cursor.execute(insert_query)
                conn.commit()
            finally:
                conn.close()
        except sqlite3.Error:
            traceback.print_exc()

    def search_database(self, table_name, name):
        result = []
        try:
            conn = sqlite3.connect(self.database_name)
            try:
                cursor = conn.cursor()
                select_query = f"SELECT * FROM {table_name} WHERE name = '{name}'"
                cursor.execute(select_query)
                columns = [desc[0] for desc in cursor.description]
                for row in cursor.fetchall():
                    row_map = {}
                    for i, col in enumerate(columns):
                        row_map[col] = row[i]
                    result.append(row_map)
            finally:
                conn.close()
        except sqlite3.Error:
            traceback.print_exc()
        return None if not result else result

    def delete_from_database(self, table_name, name):
        try:
            conn = sqlite3.connect(self.database_name)
            try:
                cursor = conn.cursor()
                delete_query = f"DELETE FROM {table_name} WHERE name = '{name}'"
                cursor.execute(delete_query)
                conn.commit()
            finally:
                conn.close()
        except sqlite3.Error:
            traceback.print_exc()