import datetime
from typing import List

# Note: Assuming Course is defined elsewhere (e.g., in ClassroomManagementTest) 
# with `start_time` and `end_time` attributes of type `datetime.time`, 
# and an `__eq__` method implemented so that `in` and `list.remove()` work identically 
# to Java's `List.contains()` and `List.remove()`.

class Classroom:
    def __init__(self, id: int):
        # Using _id to represent the Java private modifier convention
        self._id = id  
        # Package-private equivalent in Python is typically just a regular attribute
        self.courses: List = []  

    def add_course(self, course) -> None:
        if course not in self.courses:
            self.courses.append(course)

    def remove_course(self, course) -> None:
        try:
            self.courses.remove(course)
        except ValueError:
            # Java's ArrayList.remove(Object) silently returns false if the item isn't found.
            # Python's list.remove() raises a ValueError. We catch it to match Java's behavior.
            pass

    def is_free_at(self, check_time: str) -> bool:
        # LocalTime.parse() equivalent in Python is datetime.time.fromisoformat()
        time = datetime.time.fromisoformat(check_time)
        for course in self.courses:
            # !time.isBefore(course.startTime) && !time.isAfter(course.endTime)
            if time >= course.start_time and time <= course.end_time:
                return False
        return True

    def check_course_conflict(self, new_course) -> bool:
        new_start_time = new_course.start_time
        new_end_time = new_course.end_time

        for course in self.courses:
            # !(newEndTime.isBefore(course.startTime) || newStartTime.isAfter(course.endTime))
            if not (new_end_time < course.start_time or new_start_time > course.end_time):
                return False
        return True