class Student:
    def __init__(self, name: str, grade: int, major: str):
        self.name = name
        self.grade = grade
        self.major = major
        self.courses = {}

    def getName(self) -> str:
        return self.name

    def addCourseScore(self, course: str, score: int):
        self.courses[course] = score

    def calculateGPA(self):
        if not self.courses:
            return None
        total = sum(self.courses.values())
        return total / len(self.courses)

    def hasFailingCourse(self) -> bool:
        return any(score < 60 for score in self.courses.values())

    def getCourseScore(self, course: str):
        return self.courses.get(course)


class AssessmentSystem:
    def __init__(self):
        self.students = {}

    def addStudent(self, name: str, grade: int, major: str):
        self.students[name] = Student(name, grade, major)

    def addCourseScore(self, name: str, course: str, score: int):
        if name in self.students:
            self.students[name].addCourseScore(course, score)

    def getGPA(self, name: str):
        if name in self.students:
            return self.students[name].calculateGPA()
        return None

    def getAllStudentsWithFailCourse(self):
        failing = []
        for student in self.students.values():
            if student.hasFailingCourse():
                failing.append(student.getName())
        return failing

    def getCourseAverage(self, course: str):
        total = 0
        count = 0
        for student in self.students.values():
            score = student.getCourseScore(course)
            if score is not None:
                total += score
                count += 1
        return total / count if count > 0 else None

    def getTopStudent(self):
        top_student = None
        top_gpa = 0.0
        for student in self.students.values():
            gpa = student.calculateGPA()
            if gpa is not None and gpa > top_gpa:
                top_gpa = gpa
                top_student = student.getName()
        return top_student


if __name__ == "__main__":
    system = AssessmentSystem()
    system.addStudent("student 1", 3, "SE")
    system.addStudent("student 2", 2, "SE")
    system.addCourseScore("student 1", "course 1", 86)
    system.addCourseScore("student 2", "course 1", 59)
    system.addCourseScore("student 1", "course 2", 78)
    system.addCourseScore("student 2", "course 2", 90)

    print(system.getAllStudentsWithFailCourse())
    print(system.getCourseAverage("course 1"))
    print(system.getCourseAverage("course 2"))
    print(system.getGPA("student 1"))
    print(system.getGPA("student 2"))
    print(system.getTopStudent())