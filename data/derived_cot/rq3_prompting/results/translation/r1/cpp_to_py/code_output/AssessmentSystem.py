from typing import Dict, List, Optional


class Student:
    def __init__(self, grade: int, major: str):
        self.grade = grade
        self.major = major
        self.courses: Dict[str, int] = {}


class AssessmentSystem:
    def __init__(self):
        self.students: Dict[str, Student] = {}

    def add_student(self, name: str, grade: int, major: str) -> None:
        self.students[name] = Student(grade, major)

    def add_course_score(self, name: str, course: str, score: int) -> None:
        if name in self.students:
            self.students[name].courses[course] = score

    def get_gpa(self, name: str) -> Optional[float]:
        student = self.students.get(name)
        if student is None:
            return None
        courses = student.courses
        if not courses:
            return None
        total = sum(courses.values())
        return total / len(courses)

    def get_all_students_with_fail_course(self) -> List[str]:
        result = []
        for name, student in self.students.items():
            if any(score < 60 for score in student.courses.values()):
                result.append(name)
        return result

    def get_course_average(self, course: str) -> Optional[float]:
        total = 0.0
        count = 0
        for student in self.students.values():
            score = student.courses.get(course)
            if score is not None:
                total += score
                count += 1
        return total / count if count > 0 else None

    def get_top_student(self) -> Optional[str]:
        top_name = None
        top_gpa = -1.0  # sentinel
        for name in self.students:
            gpa = self.get_gpa(name)
            if gpa is not None and gpa > top_gpa:
                top_gpa = gpa
                top_name = name
        return top_name