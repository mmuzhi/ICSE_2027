from typing import List, Dict, Optional

class Student:
    def __init__(self, name: str, major: str):
        self.name = name
        self.major = major

    def getName(self) -> str:
        return self.name

    def getMajor(self) -> str:
        return self.major

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Student):
            return False
        return self.name == other.name and self.major == other.major

    def __hash__(self) -> int:
        return hash((self.name, self.major))


class ClassRegistrationSystem:
    def __init__(self):
        self.students: List[Student] = []
        self.studentsRegistrationClasses: Dict[str, List[str]] = {}

    def registerStudent(self, student: Student) -> int:
        if student in self.students:
            return 0
        else:
            self.students.append(student)
            return 1

    def registerClass(self, studentName: str, className: str) -> List[str]:
        if studentName in self.studentsRegistrationClasses:
            self.studentsRegistrationClasses[studentName].append(className)
        else:
            self.studentsRegistrationClasses[studentName] = [className]
        return self.studentsRegistrationClasses[studentName]

    def getStudentsByMajor(self, major: str) -> List[str]:
        student_list: List[str] = []
        for student in self.students:
            if student.getMajor() == major:
                student_list.append(student.getName())
        return student_list

    def getAllMajor(self) -> List[str]:
        major_set: set = set()
        for student in self.students:
            major_set.add(student.getMajor())
        return list(major_set)

    def getMostPopularClassInMajor(self, major: str) -> str:
        class_count: Dict[str, int] = {}
        for student in self.students:
            if student.getMajor() == major:
                classes = self.studentsRegistrationClasses.get(student.getName(), [])
                for c in classes:
                    class_count[c] = class_count.get(c, 0) + 1
        # If class_count is empty this will raise ValueError, matching Java's NoSuchElementException
        return max(class_count, key=class_count.get)

    # Setter methods for tests
    def setStudents(self, students: List[Student]) -> None:
        self.students = students

    def setStudentClasses(self, studentClasses: Dict[str, List[str]]) -> None:
        self.studentsRegistrationClasses = studentClasses