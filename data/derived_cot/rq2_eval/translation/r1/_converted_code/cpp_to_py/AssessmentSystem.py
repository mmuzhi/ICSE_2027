class Student:
    __slots__ = ('grade', 'major', 'courses')
    def __init__(self, grade, major):
        self.grade = grade
        self.major = major
        self.courses = {}

class AssessmentSystem:
    def __init__(self):
        self.students = {}
    
    def add_student(self, name, grade, major):
        self.students[name] = Student(grade, major)
    
    def add_course_score(self, name, course, score):
        if name in self.students:
            self.students[name].courses[course] = score
    
    def get_gpa(self, name):
        if name in self.students:
            student = self.students[name]
            if not student.courses:
                return None
            total_score = sum(student.courses.values())
            return total_score / len(student.courses)
        return None
    
    def get_all_students_with_fail_course(self):
        students_with_fail = []
        for name, student in self.students.items():
            if any(score < 60 for score in student.courses.values()):
                students_with_fail.append(name)
        return students_with_fail
    
    def get_course_average(self, course):
        total = 0
        count = 0
        for student in self.students.values():
            if course in student.courses:
                total += student.courses[course]
                count += 1
        if count == 0:
            return None
        return total / count
    
    def get_top_student(self):
        top_student = None
        highest_gpa = None
        for name in self.students:
            gpa = self.get_gpa(name)
            if gpa is not None:
                if highest_gpa is None or gpa > highest_gpa:
                    highest_gpa = gpa
                    top_student = name
        return top_student