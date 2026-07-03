from typing import List, Dict, Set, Optional, Tuple

class ClassRegistrationSystem:
    def __init__(self):
        self.students: List['Student'] = []
        self.students_registration_classes: Dict[str, List[str]] = {}

    def register_student(self, student: 'Student') -> int:
        existing = [s for s in self.students if s == student]
        if existing:
            return 0
        self.students.append(student)
        return 1

    def register_class(self, student_name: str, class_name: str) -> List[str]:
        if student_name not in self.students_registration_classes:
            self.students_registration_classes[student_name] = []
        self.students_registration_classes[student_name].append(class_name)
        return self.students_registration_classes[student_name]

    def get_students_by_major(self, major: str) -> List[str]:
        return [s.name for s in self.students if s.major == major]

    def get_all_majors(self) -> List[str]:
        return list({s.major for s in self.students})

    def get_most_popular_class_in_major(self, major: str) -> str:
        class_count: Dict[str, int] = {}
        for student in self.students:
            if student.major == major:
                classes = self.students_registration_classes.get(student.name, [])
                for cls in classes:
                    class_count[cls] = class_count.get(cls, 0) + 1
        if not class_count:
            raise ValueError(f"No students found in major '{major}'")
        most_popular = max(class_count.items(), key=lambda x: x[1])
        return most_popular[0]

    class Student:
        def __init__(self, name: str, major: str):
            self.name = name
            self.major = major

        def __eq__(self, other: object) -> bool:
            if not isinstance(other, ClassRegistrationSystem.Student):
                return False
            return self.name == other.name and self.major == other.major

        def __hash__(self) -> int:
            return hash((self.name, self.major))

        def __repr__(self) -> str:
            return f"Student(name='{self.name}', major='{self.major}')"

# Example usage:
if __name__ == "__main__":
    system = ClassRegistrationSystem()
    student1 = ClassRegistrationSystem.Student("Alice", "CS")
    system.register_student(student1)
    system.register_class("Alice", "CS101")
    system.register_class("Alice", "CS201")
    
    student2 = ClassRegistrationSystem.Student("Bob", "CS")
    system.register_student(student2)
    system.register_class("Bob", "CS101")
    
    print(system.get_students_by_major("CS"))  # Output: ['Alice', 'Bob']
    print(system.get_all_majors())             # Output: ['CS']
    print(system.get_most_popular_class_in_major("CS"))  # Output: 'CS101'