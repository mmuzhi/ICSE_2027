class Student:
    def __init__(self, name, major):
        self.name = name
        self.major = major

    def get_name(self):
        return self.name

    def get_major(self):
        return self.major

    def set_name(self, name):
        self.name = name

    def set_major(self, major):
        self.major = major

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self.name == other.name and self.major == other.major


class ClassRegistrationSystem:
    def __init__(self):
        self.students = []
        self.students_registration_classes = {}  # Maps student name to list of classes

    def register_student(self, new_student):
        name = new_student.get_name()
        for student in self.students:
            if student.get_name() == name:
                return 0
        self.students.append(new_student)
        return 1

    def register_class(self, student_name, class_name):
        if student_name not in self.students_registration_classes:
            self.students_registration_classes[student_name] = []
        classes_list = self.students_registration_classes[student_name]
        if class_name not in classes_list:
            classes_list.append(class_name)
        return classes_list

    def get_students_by_major(self, major):
        return [student.get_name() for student in self.students if student.get_major() == major]

    def get_all_major(self):
        majors = set()
        for student in self.students:
            majors.add(student.get_major())
        return list(majors)

    def get_most_popular_class_in_major(self, major):
        class_count = {}
        for student in self.students:
            if student.get_major() == major:
                classes_list = self.students_registration_classes.get(student.get_name(), [])
                for class_name in classes_list:
                    class_count[class_name] = class_count.get(class_name, 0) + 1
        
        if not class_count:
            return ""
        
        most_popular_class = None
        max_count = 0
        for class_name, count in class_count.items():
            if count > max_count:
                most_popular_class = class_name
                max_count = count
        
        return most_popular_class