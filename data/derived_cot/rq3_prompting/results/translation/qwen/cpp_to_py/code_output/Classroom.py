from datetime import datetime, timedelta
from time import mktime, strptime
import time
from datetime import datetime as dt_class

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
        if not self.has_course(course):
            self.courses.append(course)

    def remove_course(self, course):
        for i, c in enumerate(self.courses):
            if c == course:
                del self.courses[i]
                break

    def is_free_at(self, check_time):
        try:
            check_time_struct = self._string_to_time_struct(check_time)
        except (ValueError, TypeError) as e:
            print(f"Time conversion failed: {e}")
            return False

        for course in self.courses:
            try:
                start_time_struct = self._string_to_time_struct(course.start_time)
                end_time_struct = self._string_to_time_struct(course.end_time)
                start_timestamp = mktime(start_time_struct)
                end_timestamp = mktime(end_time_struct)
                check_timestamp = mktime(check_time_struct)
                if check_timestamp == -1 or start_timestamp == -1 or end_timestamp == -1:
                    print("Time conversion failed")
                    return False
                if start_timestamp <= check_timestamp <= end_timestamp:
                    return False
            except Exception as e:
                print(f"Time conversion failed: {e}")
                return False
        return True

    def check_course_conflict(self, new_course):
        try:
            new_start_time_struct = self._string_to_time_struct(new_course.start_time)
            new_end_time_struct = self._string_to_time_struct(new_course.end_time)
            if new_start_time_struct.tm_hour == -1 or new_end_time_struct.tm_hour == -1:
                print("Time conversion failed")
                return True
        except Exception as e:
            print(f"Time conversion failed: {e}")
            return True

        for course in self.courses:
            try:
                start_time_struct = self._string_to_time_struct(course.start_time)
                end_time_struct = self._string_to_time_struct(course.end_time)
                if start_time_struct.tm_hour == -1 or end_time_struct.tm_hour == -1:
                    print("Time conversion failed")
                    return True
                if self._is_time_conflict(start_time_struct, end_time_struct, new_start_time_struct, new_end_time_struct):
                    return False
            except Exception as e:
                print(f"Time conversion failed: {e}")
                return True
        return True

    def has_course(self, course):
        for c in self.courses:
            if c == course:
                return True
        return False

    def _string_to_time_struct(self, time_str):
        try:
            base_date = dt_class(2020, 1, 1)
            time_obj = dt_class.strptime(time_str, "%H:%M").time()
            combined = dt_class.combine(base_date, time_obj)
            time_struct = combined.timetuple()
            return time_struct
        except (ValueError, TypeError):
            raise ValueError(f"Invalid time format: {time_str}")

    def _is_time_conflict(self, start1, end1, start2, end2):
        start1_timestamp = mktime(start1)
        end1_timestamp = mktime(end1)
        start2_timestamp = mktime(start2)
        end2_timestamp = mktime(end2)
        return (start1_timestamp <= end2_timestamp and end1_timestamp >= start2_timestamp)

# Example usage (for testing purposes)
if __name__ == "__main__":
    c1 = Course("Math", "10:00", "11:00")
    c2 = Course("Physics", "11:00", "12:00")

    room = Classroom(1)
    room.add_course(c1)
    room.add_course(c2)

    print(room.is_free_at("10:30"))  # Should be False
    print(room.is_free_at("09:00"))  # Should be True
    print(room.check_course_conflict(Course("Chemistry", "11:30", "12:30")))  # Should be False
    print(room.check_course_conflict(Course("English", "09:00", "10:00")))  # Should be True