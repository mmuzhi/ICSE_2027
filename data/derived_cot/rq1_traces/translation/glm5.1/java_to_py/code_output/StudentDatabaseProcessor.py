import sqlite3
import traceback
from typing import List, Dict, Any


class StudentDatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_student_table(self):
        create_table_query = (
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER"
            ")"
        )
        conn = None
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(create_table_query)
            conn.commit()
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()

    def insert_student(self, student_data: 'StudentData'):
        insert_query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)"
        conn = None
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(insert_query, (
                student_data.name,
                student_data.age,
                student_data.gender,
                student_data.grade
            ))
            conn.commit()
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()

    def search_student_by_name(self, name: str) -> List[Dict[str, Any]]:
        select_query = "SELECT * FROM students WHERE name = ?"
        result: List[Dict[str, Any]] = []
        conn = None
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(select_query, (name,))
            for row in cursor.fetchall():
                student = {
                    "id": row[0] if row[0] is not None else 0,
                    "name": row[1],
                    "age": row[2] if row[2] is not None else 0,
                    "gender": row[3],
                    "grade": row[4] if row[4] is not None else 0,
                }
                result.append(student)
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()
        return result

    def delete_student_by_name(self, name: str):
        delete_query = "DELETE FROM students WHERE name = ?"
        conn = None
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(delete_query, (name,))
            conn.commit()
        except sqlite3.Error:
            traceback.print_exc()
        finally:
            if conn:
                conn.close()

    def _get_connection(self) -> sqlite3.Connection:
        return sqlite3.connect(self.database_name)

    class StudentData:
        def __init__(self, name: str, age: int, gender: str, grade: int):
            self.name = name
            self.age = age
            self.gender = gender
            self.grade = grade

        def get_name(self):
            return self.name

        def get_age(self):
            return self.age

        def get_gender(self):
            return self.gender

        def get_grade(self):
            return self.grade