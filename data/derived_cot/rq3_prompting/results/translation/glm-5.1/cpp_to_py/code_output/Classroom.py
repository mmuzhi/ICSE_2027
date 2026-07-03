import sys
from datetime import datetime


class Course:
    def __init__(self, name="", start_time="", end_time=""):
        self.name = name
        self.start_time = start_time
        self.end_time = end_time

    def __eq__(self, other):
        if not isinstance(other, Course):
            return NotImplemented
        return (self.name == other.name
                and self.start_time == other.start_time
                and self.end_time == other.end_time)

    def __hash__(self):
        return hash((self.name, self.start_time, self.end_time))


class Classroom:
    def __init__(self, id):
        self.id = id
        self.courses = []

    def _string_to_datetime(self, time_str):
        try:
            dt = datetime.strptime(time_str, "%H:%M")
        except ValueError:
            raise ValueError("Invalid time format: " + time_str)
        return dt.replace(year=2020, month=1, day=1)

    def _is_time_conflict(self, start1, end1, start2, end2):
        return start1 <= end2 and end1 >= start2

    def add_course(self, course):
        if course not in self.courses:
            self.courses.append(course)

    def remove_course(self, course):
        if course in self.courses:
            self.courses.remove(course)

    def is_free_at(self, check_time):
        try:
            check_dt = self._string_to_datetime(check_time)
        except ValueError:
            print("Time conversion failed", file=sys.stderr)
            return False

        for course in self.courses:
            try:
                start_dt = self._string_to_datetime(course.start_time)
                end_dt = self._string_to_datetime(course.end_time)
            except ValueError:
                print("Time conversion failed", file=sys.stderr)
                return False

            if check_dt >= start_dt and check_dt <= end_dt:
                return False
        return True

    def check_course_conflict(self, new_course):
        try:
            new_start_dt = self._string_to_datetime(new_course.start_time)
            new_end_dt = self._string_to_datetime(new_course.end_time)
        except ValueError:
            print("Time conversion failed", file=sys.stderr)
            return True

        for course in self.courses:
            try:
                start_dt = self._string_to_datetime(course.start_time)
                end_dt = self._string_to_datetime(course.end_time)
            except ValueError:
                print("Time conversion failed", file=sys.stderr)
                return True

            if self._is_time_conflict(start_dt, end_dt, new_start_dt, new_end_dt):
                return False
        return True

    def has_course(self, course):
        return course in self.courses