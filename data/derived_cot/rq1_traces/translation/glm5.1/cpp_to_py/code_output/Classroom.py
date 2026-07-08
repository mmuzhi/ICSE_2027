from dataclasses import dataclass
from datetime import datetime


@dataclass
class Course:
    name: str
    start_time: str
    end_time: str


class Classroom:
    def __init__(self, id: int):
        self.id = id
        self.courses = []

    def add_course(self, course: Course):
        if course not in self.courses:
            self.courses.append(course)

    def remove_course(self, course: Course):
        if course in self.courses:
            self.courses.remove(course)

    def is_free_at(self, check_time: str) -> bool:
        check_dt = self._string_to_dt(check_time)

        for course in self.courses:
            start_dt = self._string_to_dt(course.start_time)
            end_dt = self._string_to_dt(course.end_time)

            if start_dt <= check_dt <= end_dt:
                return False

        return True

    def check_course_conflict(self, new_course: Course) -> bool:
        new_start_dt = self._string_to_dt(new_course.start_time)
        new_end_dt = self._string_to_dt(new_course.end_time)

        for course in self.courses:
            start_dt = self._string_to_dt(course.start_time)
            end_dt = self._string_to_dt(course.end_time)

            if self._is_time_conflict(start_dt, end_dt, new_start_dt, new_end_dt):
                return False

        return True

    def has_course(self, course: Course) -> bool:
        return course in self.courses

    def _string_to_dt(self, time_str: str) -> datetime:
        try:
            # Parse the time (defaults to year 1900, month 1, day 1)
            dt = datetime.strptime(time_str, "%H:%M")
            # Match C++ behavior: force date to 2020-01-01 for valid chronological comparison
            return dt.replace(year=2020, month=1, day=1)
        except ValueError:
            raise ValueError(f"Invalid time format: {time_str}")

    @staticmethod
    def _is_time_conflict(start1: datetime, end1: datetime, start2: datetime, end2: datetime) -> bool:
        # Identical logic to C: (t1_start <= t2_end && t1_end >= t2_start)
        return start1 <= end2 and end1 >= start2