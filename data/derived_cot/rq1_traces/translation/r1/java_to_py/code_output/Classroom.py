from datetime import time

class Classroom:
    def __init__(self, id):
        self.id = id
        self.courses = []

    def addCourse(self, course):
        if course not in self.courses:
            self.courses.append(course)

    def removeCourse(self, course):
        if course in self.courses:
            self.courses.remove(course)

    def isFreeAt(self, checkTime):
        t = time.fromisoformat(checkTime)
        for course in self.courses:
            if course.startTime <= t <= course.endTime:
                return False
        return True

    def checkCourseConflict(self, newCourse):
        newStartTime = newCourse.startTime
        newEndTime = newCourse.endTime
        for course in self.courses:
            if newStartTime <= course.endTime and newEndTime >= course.startTime:
                return False
        return True