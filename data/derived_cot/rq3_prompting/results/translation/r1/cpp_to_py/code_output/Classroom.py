import sys
import time_

# ----------------------------------------------------------------------
# Course class (equivalent to C++ struct)
# ----------------------------------------------------------------------
class Course:
    def __init__(self, name: str, start_time: str, end_time: str):
        self.name = name
        self.start_time = start_time
        self.end_time = end_time

    def __eq__(self, other):
        if not isinstance(other, Course):
            return NotImplemented
        return (self.name == other.name and
                self.start_time == other.start_time and
                self.end_time == other.end_time)

    # __hash__ is not used in the C++ code, but we define it for completeness
    def __hash__(self):
        return hash((self.name, self.start_time, self.end_time))


# ----------------------------------------------------------------------
# Classroom class
# ----------------------------------------------------------------------
class Classroom:
    def __init__(self, id_: int):
        self._id = id_
        self._courses = []            # list of Course objects

    # ---- public helpers (mirror C++ private helpers) ----
    @staticmethod
    def _string_to_tm(time_str: str):
        """
        Parse "HH:MM" and return a time.struct_time with fixed date (2020-01-01).
        Raises ValueError on invalid input (same as C++ std::invalid_argument).
        """
        parts = time_str.split(':')
        if len(parts) != 2:
            raise ValueError("Invalid time format: " + time_str)
        try:
            hour = int(parts[0])
            minute = int(parts[1])
        except ValueError:
            raise ValueError("Invalid time format: " + time_str)

        # Fixed date: year=2020, month=1, day=1, weekday=0, yearday=1, isdst=-1
        return time.struct_time((2020, 1, 1, hour, minute, 0, 0, 1, -1))

    @staticmethod
    def _tm_to_time_t(tm):
        """Convert time.struct_time to a timestamp (floating seconds)."""
        try:
            return time.mktime(tm)
        except (OverflowError, ValueError) as e:
            # C++ std::mktime returns (time_t)-1 on error; Python raises.
            # We mimic the C++ behaviour by raising std::runtime_error.
            raise RuntimeError("Failed to convert std::tm to std::time_t")

    @staticmethod
    def _is_time_conflict(start1, end1, start2, end2):
        """Return True if the two intervals (inclusive) overlap."""
        t1_start = Classroom._tm_to_time_t(start1)
        t1_end   = Classroom._tm_to_time_t(end1)
        t2_start = Classroom._tm_to_time_t(start2)
        t2_end   = Classroom._tm_to_time_t(end2)
        return (t1_start <= t2_end and t1_end >= t2_start)

    # ---- public interface (mirrors C++ methods exactly) ----
    def add_course(self, course: Course):
        if course not in self._courses:
            self._courses.append(course)

    def remove_course(self, course: Course):
        # remove first occurrence (same as C++ find + erase)
        try:
            idx = self._courses.index(course)
            del self._courses[idx]
        except ValueError:
            pass

    def is_free_at(self, check_time: str) -> bool:
        check_tm = self._string_to_tm(check_time)
        for course in self._courses:
            start_tm = self._string_to_tm(course.start_time)
            end_tm   = self._string_to_tm(course.end_time)

            # The C++ code had dead code checking for -1 after _tm_to_time_t,
            # but _tm_to_time_t raises on failure, so we omit that dead path.
            check_tt = self._tm_to_time_t(check_tm)
            start_tt = self._tm_to_time_t(start_tm)
            end_tt   = self._tm_to_time_t(end_tm)

            if check_tt >= start_tt and check_tt <= end_tt:
                return False
        return True

    def check_course_conflict(self, new_course: Course) -> bool:
        # The C++ code had a dead check for tm_hour==-1 after _string_to_tm;
        # _string_to_tm raises on failure, so we omit it.
        new_start_tm = self._string_to_tm(new_course.start_time)
        new_end_tm   = self._string_to_tm(new_course.end_time)

        for course in self._courses:
            start_tm = self._string_to_tm(course.start_time)
            end_tm   = self._string_to_tm(course.end_time)

            # C++ dead tm_hour == -1 check omitted for the same reason.
            if self._is_time_conflict(start_tm, end_tm, new_start_tm, new_end_tm):
                return False
        return True

    def has_course(self, course: Course) -> bool:
        return course in self._courses