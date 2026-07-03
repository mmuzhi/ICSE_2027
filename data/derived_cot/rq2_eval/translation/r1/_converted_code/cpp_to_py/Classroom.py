from datetime import datetime

class Course:
    def __init__(self, name, start_time, end_time):
        self.name = name
        self.start_time = start_time
        self.end_time = end_time

    def __eq__(self, other):
        if not isinstance(other, Course):
            return False
        return (self.name == other.name and 
                self.start_time == other.start_time and 
                self.end_time == other.end_time)

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

    def has_course(self, course):
        return course in self.courses

    def _string_to_dt(self, time_str):
        try:
            dt = datetime.strptime(time_str, "%H:%M")
            return dt.replace(year=2020, month=1, day=1)
        except ValueError:
            raise ValueError(f"Invalid time format: {time_str}")

    def is_free_at(self, check_time):
        check_dt = self._string_to_dt(check_time)
        for course in self.courses:
            start_dt = self._string_to_dt(course.start_time)
            end_dt = self._string_to_dt(course.end_time)
            if start_dt <= check_dt <= end_dt:
                return False
        return True

    def check_course_conflict(self, new_course):
        new_start_dt = self._string_to_dt(new_course.start_time)
        new_end_dt = self._string_to_dt(new_course.end_time)
        for course in self.courses:
            start_dt = self._string_to_dt(course.start_time)
            end_dt = self._string_to_dt(course.end_time)
            if start_dt <= new_end_dt and end_dt >= new_start_dt:
                return False
        return True