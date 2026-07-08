class Student:
    def __init__(self, name: str, major: str):
        self.name = name
        self.major = major

    def get_name(self) -> str:
        return self.name

    def get_major(self) -> str:
        return self.major

    def set_name(self, name: str) -> None:
        self.name = name

    def set_major(self, major: str) -> None:
        self.major = major

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, Student):
            return NotImplemented
        return self.name == other.name and self.major == other.major


class ClassRegistrationSystem:
    def __init__(self):
        self.students = []
        self.students_registration_classes = {}

    def register_student(self, new_student: Student) -> int:
        name = new_student.get_name()
        major = new_student.get_major()
        for student in self.students:
            if student.get_name() == name:
                return 0
        self.students.append(Student(name, major))
        return 1

    def register_class(self, student_name: str, class_name: str) -> list:
        # defaultdict or setdefault mimics C++ unordered_map's default insertion of an empty vector
        classes = self.students_registration_classes.setdefault(student_name, [])
        if class_name not in classes:
            classes.append(class_name)
        return classes

    def get_students_by_major(self, major: str) -> list:
        student_list = []
        for student in self.students:
            if student.get_major() == major:
                student_list.append(student.get_name())
        return student_list

    def get_all_major(self) -> list:
        # std::set in C++ sorts elements, so we must return a sorted list to maintain identical behavior
        majors = set()
        for student in self.students:
            majors.add(student.get_major())
        return sorted(list(majors))

    def get_most_popular_class_in_major(self, major: str) -> str:
        class_count = {}

        for student in self.students:
            if student.get_major() == major:
                student_name = student.get_name()
                if student_name in self.students_registration_classes:
                    for class_name in self.students_registration_classes[student_name]:
                        class_count[class_name] = class_count.get(class_name, 0) + 1

        most_popular_class = ""
        max_count = 0
        for class_name, count in class_count.items():
            if count > max_count:
                most_popular_class = class_name
                max_count = count

        return most_popular_class