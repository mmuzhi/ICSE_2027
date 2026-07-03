from datetime import datetime, time

class Course:
    def __init__(self, start_time, end_time):
        self.start_time = start_time
        self.end_time = end_time

class Classroom:
    def __init__(self, id):
        self.id = id
        self.courses = []

    def add_course(self, course):
        if course not in self.courses:
            self.courses.append(course)

    def remove_course(self, course):
        if course in self.courses:
            self.courses.remove(course)

    def is_free_at(self, check_time_str):
        try:
            check_time = datetime.strptime(check_time_str, "%H:%M").time()
        except ValueError:
            raise ValueError("Invalid time format. Expected format: HH:MM")
        
        for course in self.courses:
            if not (check_time < course.start_time or check_time > course.end_time):
                return False
        return True

    def check_course_conflict(self, new_course):
        new_start = new_course.start_time
        new_end = new_course.end_time
        
        for course in self.courses:
            if not (new_end < course.start_time or new_start > course.end_time):
                return False
        return True