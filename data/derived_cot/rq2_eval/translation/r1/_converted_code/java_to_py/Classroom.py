from datetime import time

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

    def is_free_at(self, checkTime):
        t = time.fromisoformat(checkTime)
        for course in self.courses:
            if course.startTime <= t <= course.endTime:
                return False
        return True

    def check_course_conflict(self, newCourse):
        newStartTime = newCourse.startTime
        newEndTime = newCourse.endTime
        for course in self.courses:
            if newStartTime <= course.endTime and newEndTime >= course.startTime:
                return False
        return True