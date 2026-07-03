import sqlite3

class StudentDatabaseProcessor:
    def __init__(self, database_name):
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
        self._execute_query(query, ())

    def insert_student(self, student_data):
        query = """
            INSERT INTO students (name, age, gender, grade)
            VALUES (?, ?, ?, ?)
        """
        params = (
            student_data["name"],
            student_data["age"],
            student_data["gender"],
            student_data["grade"]
        )
        self._execute_query(query, params)

    def search_student_by_name(self, name):
        query = "SELECT * FROM students WHERE name = ?"
        params = (name,)
        result_rows = self._query_result(query, params)
        
        students = []
        for row in result_rows:
            student = {
                "id": row[0],
                "name": row[1],
                "age": row[2],
                "gender": row[3],
                "grade": row[4]
            }
            students.append(student)
        return students

    def delete_student_by_name(self, name):
        query = "DELETE FROM students WHERE name = ?"
        params = (name,)
        self._execute_query(query, params)

    def _execute_query(self, query, params):
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            cursor.execute(query, params)
            conn.commit()

    def _query_result(self, query, params):
        with sqlite3.connect(self.database_name) as conn:
            cursor = conn.cursor()
            cursor.execute(query, params)
            rows = cursor.fetchall()
            return rows