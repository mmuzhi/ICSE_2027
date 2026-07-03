import sqlite3
import traceback


class StudentDatabaseProcessor:
    def __init__(self, database_name: str):
        self.database_name = database_name

    def _get_connection(self) -> sqlite3.Connection:
        conn = sqlite3.connect(self.database_name)
        conn.isolation_level = None  # auto-commit, matches Java's default behavior
        return conn

    def create_student_table(self) -> None:
        query = (
            "CREATE TABLE IF NOT EXISTS students ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name TEXT, "
            "age INTEGER, "
            "gender TEXT, "
            "grade INTEGER"
            ")"
        )
        try:
            conn = self._get_connection()
            with conn:
                cursor = conn.cursor()
                cursor.execute(query)
        except sqlite3.Error:
            traceback.print_exc()

    def insert_student(self, student_data: "StudentDatabaseProcessor.StudentData") -> None:
        query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)"
        try:
            conn = self._get_connection()
            with conn:
                cursor = conn.cursor()
                cursor.execute(
                    query,
                    (
                        student_data.get_name(),
                        student_data.get_age(),
                        student_data.get_gender(),
                        student_data.get_grade(),
                    ),
                )
        except sqlite3.Error:
            traceback.print_exc()

    def search_student_by_name(self, name: str) -> list[dict[str, object]]:
        query = "SELECT * FROM students WHERE name = ?"
        result = []
        try:
            conn = self._get_connection()
            with conn:
                cursor = conn.cursor()
                cursor.execute(query, (name,))
                rows = cursor.fetchall()
                column_names = [desc[0] for desc in cursor.description]
                for row in rows:
                    student = {}
                    for i, col in enumerate(column_names):
                        student[col] = row[i]
                    result.append(student)
        except sqlite3.Error:
            traceback.print_exc()
        return result

    def delete_student_by_name(self, name: str) -> None:
        query = "DELETE FROM students WHERE name = ?"
        try:
            conn = self._get_connection()
            with conn:
                cursor = conn.cursor()
                cursor.execute(query, (name,))
        except sqlite3.Error:
            traceback.print_exc()

    class StudentData:
        def __init__(self, name: str, age: int, gender: str, grade: int):
            self.name = name
            self.age = age
            self.gender = gender
            self.grade = grade

        def get_name(self) -> str:
            return self.name

        def get_age(self) -> int:
            return self.age

        def get_gender(self) -> str:
            return self.gender

        def get_grade(self) -> int:
            return self.grade