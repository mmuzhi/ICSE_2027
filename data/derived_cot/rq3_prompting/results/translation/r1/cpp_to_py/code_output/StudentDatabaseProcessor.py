import sqlite3
from typing import List, Dict

class StudentDatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_student_table(self):
        query = """
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY,
            name TEXT,
            age INTEGER,
            gender TEXT,
            grade INTEGER
        )
        """
        self._execute_query(query, [])

    def insert_student(self, student_data: Dict[str, str]):
        query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)"
        params = [
            student_data["name"],
            student_data["age"],
            student_data["gender"],
            student_data["grade"]
        ]
        self._execute_query(query, params)

    def search_student_by_name(self, name: str) -> List[Dict[str, str]]:
        query = "SELECT * FROM students WHERE name = ?"
        params = [name]
        results = self._query_result(query, params)
        students = []
        for row in results:
            student = {
                "id": row[0],
                "name": row[1],
                "age": row[2],
                "gender": row[3],
                "grade": row[4]
            }
            students.append(student)
        return students

    def delete_student_by_name(self, name: str):
        query = "DELETE FROM students WHERE name = ?"
        params = [name]
        self._execute_query(query, params)

    def _execute_query(self, query: str, params: List[str]):
        conn = sqlite3.connect(self.database_name)
        conn.isolation_level = None  # autocommit mode to match C++ behavior
        conn.execute(query, params)
        conn.close()

    def _query_result(self, query: str, params: List[str]) -> List[List[str]]:
        conn = sqlite3.connect(self.database_name)
        conn.isolation_level = None
        cursor = conn.execute(query, params)
        rows = cursor.fetchall()
        # Convert all values to strings (C++ column_text returns strings)
        result = [[str(val) for val in row] for row in rows]
        conn.close()
        return result