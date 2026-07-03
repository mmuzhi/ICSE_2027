class Student:
    def __init__(self, grade, major):
        self.grade = grade
        self.major = major
        self.courses = {}  # Maps course names to scores

class AssessmentSystem:
    def __init__(self):
        self.students = {}  # Maps student names to Student objects

    def add_student(self, name, grade, major):
        self.students[name] = Student(grade, major)

    def add_course_score(self, name, course, score):
        if name in self.students:
            self.students[name].courses[course] = score

    def get_gpa(self, name):
        student = self.students.get(name)
        if student is None or not student.courses:
            return None
        return sum(student.courses.values()) / len(student.courses)

    def get_all_students_with_fail_course(self):
        result = []
        for name, student in self.students.items():
            if any(score < 60 for score in student.courses.values()):
                result.append(name)
        return result

    def get_course_average(self, course):
        total = 0
        count = 0
        for student in self.students.values():
            if course in student.courses:
                total += student.courses[course]
                count += 1
        return total / count if count > 0 else None

    def get_top_student(self):
        top_name = None
        highest_gpa = None
        for name, student in self.students.items():
            gpa = self.get_gpa(name)
            if gpa is None:
                continue
            if highest_gpa is None or gpa > highest_gpa:
                highest_gpa = gpa
                top_name = name
        return top_name