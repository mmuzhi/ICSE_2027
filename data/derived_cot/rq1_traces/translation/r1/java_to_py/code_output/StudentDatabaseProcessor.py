import sqlite3
import traceback

class StudentData:
    def __init__(self, name, age, gender, grade):
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

class StudentDatabaseProcessor:
    def __init__(self, database_name):
        self.database_name = database_name
    
    def create_student_table(self):
        create_table_query = """CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            age INTEGER,
            gender TEXT,
            grade INTEGER
        )"""
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(create_table_query)
            conn.commit()
        except Exception as e:
            traceback.print_exc()
        finally:
            conn.close()
    
    def insert_student(self, student_data):
        insert_query = "INSERT INTO students (name, age, gender, grade) VALUES (?, ?, ?, ?)"
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(insert_query, (
                student_data.get_name(),
                student_data.get_age(),
                student_data.get_gender(),
                student_data.get_grade()
            ))
            conn.commit()
        except Exception as e:
            traceback.print_exc()
        finally:
            conn.close()
    
    def search_student_by_name(self, name):
        select_query = "SELECT * FROM students WHERE name = ?"
        result = []
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(select_query, (name,))
            rows = cursor.fetchall()
            column_names = [desc[0] for desc in cursor.description]
            for row in rows:
                student = {}
                for idx, col_name in enumerate(column_names):
                    student[col_name] = row[idx]
                result.append(student)
        except Exception as e:
            traceback.print_exc()
        finally:
            conn.close()
        return result
    
    def delete_student_by_name(self, name):
        delete_query = "DELETE FROM students WHERE name = ?"
        try:
            conn = self._get_connection()
            cursor = conn.cursor()
            cursor.execute(delete_query, (name,))
            conn.commit()
        except Exception as e:
            traceback.print_exc()
        finally:
            conn.close()
    
    def _get_connection(self):
        return sqlite3.connect(self.database_name)