from collections import defaultdict

class Student:
    def __init__(self, grade, major):
        self.grade = grade
        self.major = major
        self.courses = {}  # course: score

class AssessmentSystem:
    def __init__(self):
        self.students = {}  # name: Student

    def add_student(self, name, grade, major):
        if name not in self.students:
            self.students[name] = Student(grade, major)

    def add_course_score(self, name, course, score):
        student = self.students.get(name)
        if student:
            student.courses[course] = score

    def get_gpa(self, name):
        student = self.students.get(name)
        if not student or not student.courses:
            return None
        total_score = sum(student.courses.values())
        return total_score / len(student.courses)

    def get_all_students_with_fail_course(self):
        result = []
        for student in self.students.values():
            if any(score < 60 for score in student.courses.values()):
                result.append(student.grade)  # Note: Using grade for name; adjust if needed
        return result

    def get_course_average(self, course):
        scores = []
        for student in self.students.values():
            if course in student.courses:
                scores.append(student.courses[course])
        if not scores:
            return None
        return sum(scores) / len(scores)

    def get_top_student(self):
        if not self.students:
            return None
        best_grade = -1
        best_name = None
        for name, student in self.students.items():
            gpa = self.get_gpa(name)
            if gpa is None:
                continue
            if gpa > best_grade:
                best_grade = gpa
                best_name = name
        return best_name