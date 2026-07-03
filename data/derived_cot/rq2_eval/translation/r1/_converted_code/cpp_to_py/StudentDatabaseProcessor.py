import sqlite3

class StudentDatabaseProcessor:
    def __init__(self, database_name):
        self.database_name = database_name

    def create_student_table(self):
        create_table_query = """
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY,
                name TEXT,
                age INTEGER,
                gender TEXT,
                grade INTEGER
            )
        """
        self.execute_query(create_table_query, [])

    def insert_student(self, student_data):
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
        self.execute_query(insert_query, params)

    def search_student_by_name(self, name):
        select_query = """
            SELECT * FROM students WHERE name = ?
        """
        params = [name]
        results = self.query_result(select_query, params)
        
        students = []
        column_names = ["id", "name", "age", "gender", "grade"]
        for row in results:
            student = {}
            for idx, col_name in enumerate(column_names):
                student[col_name] = str(row[idx])
            students.append(student)
        return students

    def delete_student_by_name(self, name):
        delete_query = """
            DELETE FROM students WHERE name = ?
        """
        params = [name]
        self.execute_query(delete_query, params)

    def execute_query(self, query, params):
        conn = sqlite3.connect(self.database_name)
        try:
            cursor = conn.cursor()
            cursor.execute(query, params)
            conn.commit()
        finally:
            conn.close()

    def query_result(self, query, params):
        conn = sqlite3.connect(self.database_name)
        try:
            cursor = conn.cursor()
            cursor.execute(query, params)
            rows = cursor.fetchall()
            return rows
        finally:
            conn.close()