import sqlite3
from typing import List, Dict, Optional

class StudentDatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def create_student_table(self) -> None:
        create_table_query = """
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT,
                age INTEGER,
                gender TEXT,
                grade INTEGER
            )
        """
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                cursor.execute(create_table_query)
                conn.commit()
        except sqlite3.Error as e:
            print(f"Database error: {e}")

    def insert_student(self, student_data) -> None:
        insert_query = """INSERT INTO students 
                        (name, age, gender, grade) VALUES (?, ?, ?, ?)"""
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                cursor.execute(insert_query, (
                    student_data.name,
                    student_data.age,
                    student_data.gender,
                    student_data.grade
                ))
                conn.commit()
        except sqlite3.Error as e:
            print(f"Database error: {e}")

    def search_student_by_name(self, name: str) -> List[Dict[str, int]]:
        select_query = "SELECT * FROM students WHERE name = ?"
        result = []
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                cursor.execute(select_query, (name,))
                for row in cursor.fetchall():
                    student = {
                        "id": row[0],
                        "name": row[1],
                        "age": row[2],
                        "gender": row[3],
                        "grade": row[4]
                    }
                    result.append(student)
        except sqlite3.Error as e:
            print(f"Database error: {e}")
        return result

    def delete_student_by_name(self, name: str) -> None:
        delete_query = "DELETE FROM students WHERE name = ?"
        try:
            with sqlite3.connect(self.database_name) as conn:
                cursor = conn.cursor()
                cursor.execute(delete_query, (name,))
                conn.commit()
        except sqlite3.Error as e:
            print(f"Database error: {e}")

    class StudentData:
        def __init__(self, name: str, age: int, gender: str, grade: int) -> None:
            self.name = name
            self.age = age
            self.gender = gender
            self.grade = grade

        def __repr__(self) -> str:
            return (f"StudentData(name={self.name!r}, age={self.age}, "
                    f"gender={self.gender!r}, grade={self.grade})")