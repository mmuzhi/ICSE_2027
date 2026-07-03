import sys
from datetime import datetime, time

class Course:
    def __init__(self, name="", start_time="", end_time=""):
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
        self.fixed_date = datetime(2020, 1, 1)

    def string_to_tm(self, time_str):
        parts = time_str.split(':')
        if len(parts) != 2:
            raise ValueError(f"Invalid time format: {time_str}")
        try:
            hour = int(parts[0])
            minute = int(parts[1])
        except ValueError:
            raise ValueError(f"Invalid time format: {time_str}")
        
        if hour < 0 or hour >= 24 or minute < 0 or minute >= 60:
            raise ValueError(f"Invalid time format: {time_str}")
        
        return time(hour, minute)

    def tm_to_time_t(self, tm):
        dt = self.fixed_date.replace(hour=tm.hour, minute=tm.minute, second=0, microsecond=0)
        return dt.timestamp()

    def is_time_conflict(self, start1, end1, start2, end2):
        t1_start = self.tm_to_time_t(start1)
        t1_end = self.tm_to_time_t(end1)
        t2_start = self.tm_to_time_t(start2)
        t2_end = self.tm_to_time_t(end2)
        return (t1_start <= t2_end and t1_end >= t2_start)

    def add_course(self, course):
        if not self.has_course(course):
            self.courses.append(course)

    def remove_course(self, course):
        for i, c in enumerate(self.courses):
            if c == course:
                del self.courses[i]
                break

    def is_free_at(self, check_time_str):
        try:
            check_time_obj = self.string_to_tm(check_time_str)
            check_time_t = self.tm_to_time_t(check_time_obj)
        except ValueError as e:
            print(e, file=sys.stderr)
            return False

        for course in self.courses:
            try:
                start_time_obj = self.string_to_tm(course.start_time)
                end_time_obj = self.string_to_tm(course.end_time)
                start_time_t = self.tm_to_time_t(start_time_obj)
                end_time_t = self.tm_to_time_t(end_time_obj)

                if check_time_t >= start_time_t and check_time_t <= end_time_t:
                    return False
            except ValueError as e:
                print(e, file=sys.stderr)
                return False

        return True

    def check_course_conflict(self, new_course):
        try:
            new_start_time_obj = self.string_to_tm(new_course.start_time)
            new_end_time_obj = self.string_to_tm(new_course.end_time)
            new_start_time_t = self.tm_to_time_t(new_start_time_obj)
            new_end_time_t = self.tm_to_time_t(new_end_time_obj)
        except ValueError as e:
            print(e, file=sys.stderr)
            return True

        for course in self.courses:
            try:
                start_time_obj = self.string_to_tm(course.start_time)
                end_time_obj = self.string_to_tm(course.end_time)
                start_time_t = self.tm_to_time_t(start_time_obj)
                end_time_t = self.tm_to_time_t(end_time_obj)

                if self.is_time_conflict(start_time_obj, end_time_obj, new_start_time_obj, new_end_time_obj):
                    return False
            except ValueError as e:
                print(e, file=sys.stderr)
                return True

        return True

    def has_course(self, course):
        for c in self.courses:
            if c == course:
                return True
        return False