class Student:
    def __init__(self, name, major):
        self.name = name
        self.major = major

    def __eq__(self, other):
        if self is other:
            return True
        if not isinstance(other, Student):
            return False
        return self.name == other.name and self.major == other.major

    def __hash__(self):
        return hash((self.name, self.major))

class ClassRegistrationSystem:
    def __init__(self):
        self.students = []
        self.students_registration_classes = {}

    def register_student(self, student):
        if student in self.students:
            return 0
        else:
            self.students.append(student)
            return 1

    def register_class(self, student_name, class_name):
        if student_name in self.students_registration_classes:
            self.students_registration_classes[student_name].append(class_name)
        else:
            self.students_registration_classes[student_name] = [class_name]
        return self.students_registration_classes[student_name]

    def get_students_by_major(self, major):
        student_list = []
        for student in self.students:
            if student.major == major:
                student_list.append(student.name)
        return student_list

    def get_all_major(self):
        major_set = set()
        for student in self.students:
            major_set.add(student.major)
        return list(major_set)

    def get_most_popular_class_in_major(self, major):
        class_count = {}
        for student in self.students:
            if student.major == major:
                classes = self.students_registration_classes.get(student.name, [])
                for class_name in classes:
                    class_count[class_name] = class_count.get(class_name, 0) + 1
        if not class_count:
            raise ValueError("No classes found for the major")
        return max(class_count.items(), key=lambda x: x[1])[0]

    def set_students(self, students):
        self.students = students

    def set_student_classes(self, student_classes):
        self.students_registration_classes = student_classes