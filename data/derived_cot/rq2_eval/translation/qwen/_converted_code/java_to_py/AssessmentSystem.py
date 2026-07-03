class AssessmentSystem:

    def __init__(self):
        self.students = {}

    def add_student(self, name, grade, major):
        self.students[name] = Student(name, grade, major)

    def add_course_score(self, name, course, score):
        if name in self.students:
            self.students[name].addCourseScore(course, score)

    def get_gpa(self, name):
        return self.students[name].calculateGPA() if name in self.students else None

    def get_all_students_with_fail_course(self):
        return [student.name for student in self.students.values() if student.hasFailingCourse()]

    def get_course_average(self, course):
        total_score = sum((score for student in self.students.values() if (score := student.getCourseScore(course)) is not None))
        count = sum((1 for student in self.students.values() if student.getCourseScore(course) is not None))
        return total_score / count if count > 0 else None

    def get_top_student(self):
        top_gpa = -1
        top_student = None
        for student in self.students.values():
            gpa = student.calculateGPA()
            if gpa is not None and gpa > top_gpa:
                top_gpa = gpa
                top_student = student.name
        return top_student

class Student:

    def __init__(self, name, grade, major):
        self.name = name
        self.grade = grade
        self.major = major
        self.courses = {}

    def addCourseScore(self, course, score):
        self.courses[course] = score

    def calculateGPA(self):
        if not self.courses:
            return None
        return sum(self.courses.values()) / len(self.courses)

    def hasFailingCourse(self):
        return any((score < 60 for score in self.courses.values()))

    def getCourseScore(self, course):
        return self.courses.get(course)
if __name__ == '__main__':
    system = AssessmentSystem()
    system.addStudent('student 1', 3, 'SE')
    system.addStudent('student 2', 2, 'SE')
    system.addCourseScore('student 1', 'course 1', 86)
    system.addCourseScore('student 2', 'course 1', 59)
    system.addCourseScore('student 1', 'course 2', 78)
    system.addCourseScore('student 2', 'course 2', 90)
    print(system.getAllStudentsWithFailCourse())
    print(system.getCourseAverage('course 1'))
    print(system.getCourseAverage('course 2'))
    print(system.getGPA('student 1'))
    print(system.getGPA('student 2'))
    print(system.getTopStudent())