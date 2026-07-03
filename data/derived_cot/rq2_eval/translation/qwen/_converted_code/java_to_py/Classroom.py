from datetime import time
from datetime import datetime as dt
from typing import Set

def parse_time_str(s: str) -> time:
    try:
        return dt.strptime(s, '%H:%M:%S').time()
    except ValueError:
        try:
            return dt.strptime(s, '%H:%M').time()
        except ValueError:
            raise ValueError(f'Invalid time format: {s}')

class Course:

    def __init__(self, start_time: time, end_time: time):
        self.start_time = start_time
        self.end_time = end_time

    def __eq__(self, other):
        if not isinstance(other, Course):
            return False
        return self.start_time == other.start_time and self.end_time == other.end_time

    def __hash__(self):
        return hash((self.start_time, self.end_time))

class Classroom:

    def __init__(self, id: int):
        self.id = id
        self.courses: Set[Course] = set()

    def add_course(self, course: Course):
        self.courses.add(course)

    def remove_course(self, course: Course):
        self.courses.discard(course)

    def is_free_at(self, check_time_str: str) -> bool:
        check_time = parse_time_str(check_time_str)
        for course in self.courses:
            if not (check_time < course.start_time or check_time > course.end_time):
                return False
        return True

    def check_course_conflict(self, new_course: Course) -> bool:
        new_start = new_course.start_time
        new_end = new_course.end_time
        for course in self.courses:
            if not (new_end <= course.start_time or new_start >= course.end_time):
                return False
        return True