import sqlite3
from typing import Dict, List, Optional, Tuple

class StudentDatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_student_table(self) -> None:
        create_table_query = """
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY,
                name TEXT,
                age INTEGER,
                gender TEXT,
                grade INTEGER
            )
        """
        self._execute_query(create_table_query, {})

    def insert_student(self, student_data: Dict[str, str]) -> None:
        insert_query = """
            INSERT INTO students (name, age, gender, grade)
            VALUES (?, ?, ?, ?)
        """
        params = [
            student_data["name"],
            student_data["age"],
            student_data["gender"],
            student_data["grade"]
        ]
        self._execute_query(insert_query, params)

    def search_student_by_name(self, name: str) -> List[Dict[str, str]]:
        select_query = """
            SELECT * FROM students WHERE name = ?
        """
        params = [name]
        results = self._query_result(select_query, params)
        return self._convert_results_to_dicts(results)

    def delete_student_by_name(self, name: str) -> None:
        delete_query = """
            DELETE FROM students WHERE name = ?
        """
        params = [name]
        self._execute_query(delete_query, params)

    def _execute_query(self, query: str, params: List[str]) -> None:
        conn = sqlite3.connect(self.database_name)
        cur = conn.cursor()
        try:
            cur.execute(query, params)
            conn.commit()
        except sqlite3.Error as e:
            conn.rollback()
            raise e
        finally:
            cur.close()
            conn.close()

    def _query_result(self, query: str, params: List[str]) -> List[List[str]]:
        conn = sqlite3.connect(self.database_name)
        cur = conn.cursor()
        try:
            cur.execute(query, params)
            columns = [col[0] for col in cur.description]
            results = []
            for row in cur.fetchall():
                results.append(row)
            return results
        except sqlite3.Error as e:
            conn.rollback()
            raise e
        finally:
            cur.close()
            conn.close()

    def _convert_results_to_dicts(self, results: List[List[str]]) -> List[Dict[str, str]]:
        if not results:
            return []
        columns = ["id", "name", "age", "gender", "grade"]
        return [
            {col: str(row[i]) for i, col in enumerate(columns)}
            for row in results
        ]