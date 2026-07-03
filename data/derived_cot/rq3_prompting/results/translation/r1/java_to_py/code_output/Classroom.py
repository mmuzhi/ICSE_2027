import datetime

class Classroom:
    def __init__(self, id):
        self.id = id
        self.courses = []

    def addCourse(self, course):
        if course not in self.courses:
            self.courses.append(course)

    def removeCourse(self, course):
        self.courses.remove(course)

    def isFreeAt(self, checkTime):
        time = datetime.datetime.strptime(checkTime, "%H:%M").time()
        for course in self.courses:
            if course.start_time <= time <= course.end_time:
                return False
        return True

    def checkCourseConflict(self, newCourse):
        new_start = newCourse.start_time
        new_end = newCourse.end_time
        for course in self.courses:
            if not (new_end < course.start_time or new_start > course.end_time):
                return False
        return True