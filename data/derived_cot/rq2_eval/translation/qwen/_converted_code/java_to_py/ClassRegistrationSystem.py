class Student:
    def __init__(self, name, major):
        self.name = name
        self.major = major

    def __eq__(self, other):
        if isinstance(other, Student):
            return self.name == other.name and self.major == other.major
        return False

    def __hash__(self):
        return hash((self.name, self.major))

class ClassRegistrationSystem:
    def __init__(self):
        self.students = []
        self.students_registration_classes = {}  # Maps student name to list of classes

    def register_student(self, student):
        if any(s == student for s in self.students):
            return 0
        self.students.append(student)
        return 1

    def register_class(self, student_name, class_name):
        if student_name in self.students_registration_classes:
            self.students_registration_classes[student_name].append(class_name)
        else:
            self.students_registration_classes[student_name] = [class_name]
        return self.students_registration_classes[student_name]

    def get_students_by_major(self, major):
        return [student.name for student in self.students if student.major == major]

    def get_all_major(self):
        return list({student.major for student in self.students})

    def get_most_popular_class_in_major(self, major):
        class_count = {}
        for student in self.students:
            if student.major == major:
                classes = self.students_registration_classes.get(student.name, [])
                for cls_name in classes:
                    class_count[cls_name] = class_count.get(cls_name, 0) + 1
        if not class_count:
            raise ValueError("No classes found for the given major")
        return max(class_count.items(), key=lambda x: x[1])[0]