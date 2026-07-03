import json


class AssessmentSystem:
    def __init__(self):
        self.students = {}

    def addStudent(self, name, grade, major):
        self.students[name] = self.Student(name, grade, major)

    def addCourseScore(self, name, course, score):
        if name in self.students:
            self.students[name].addCourseScore(course, score)

    def getGPA(self, name):
        if name in self.students:
            return self.students[name].calculateGPA()
        return None

    def getAllStudentsWithFailCourse(self):
        failingStudents = []
        for student in self.students.values():
            if student.hasFailingCourse():
                failingStudents.append(student.getName())
        return failingStudents

    def getCourseAverage(self, course):
        totalScore = 0
        count = 0
        for student in self.students.values():
            score = student.getCourseScore(course)
            if score is not None:
                totalScore += score
                count += 1
        return totalScore / count if count > 0 else None

    def getTopStudent(self):
        topStudent = None
        topGPA = 0.0
        for student in self.students.values():
            gpa = student.calculateGPA()
            if gpa is not None and gpa > topGPA:
                topGPA = gpa
                topStudent = student.getName()
        return topStudent

    class Student:
        def __init__(self, name, grade, major):
            self.name = name
            self.grade = grade
            self.major = major
            self.courses = {}

        def getName(self):
            return self.name

        def addCourseScore(self, course, score):
            self.courses[course] = score

        def calculateGPA(self):
            if not self.courses:
                return None
            totalScore = sum(self.courses.values())
            return totalScore / len(self.courses)

        def hasFailingCourse(self):
            for score in self.courses.values():
                if score < 60:
                    return True
            return False

        def getCourseScore(self, course):
            return self.courses.get(course)

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(self) != type(other):
                return False
            return (self.grade == other.grade and
                    self.name == other.name and
                    self.major == other.major and
                    self.courses == other.courses)

        def __hash__(self):
            return hash((self.name, self.grade, self.major, json.dumps(self.courses, sort_keys=True)))


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