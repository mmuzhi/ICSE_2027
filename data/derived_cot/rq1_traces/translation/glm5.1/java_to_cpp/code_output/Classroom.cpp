#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

// Mimics java.time.LocalTime
class LocalTime {
private:
    int secondsSinceMidnight;

    static int parseToSeconds(const std::string& timeStr) {
        int hour = 0, minute = 0, second = 0;
        char colon;
        std::istringstream iss(timeStr);
        iss >> hour >> colon >> minute;
        if (iss >> colon >> second) {
            // seconds were present and parsed
        }
        return hour * 3600 + minute * 60 + second;
    }

    explicit LocalTime(int seconds) : secondsSinceMidnight(seconds) {}

public:
    LocalTime() : secondsSinceMidnight(0) {}

    static LocalTime parse(const std::string& timeStr) {
        return LocalTime(parseToSeconds(timeStr));
    }

    bool isBefore(const LocalTime& other) const {
        return secondsSinceMidnight < other.secondsSinceMidnight;
    }

    bool isAfter(const LocalTime& other) const {
        return secondsSinceMidnight > other.secondsSinceMidnight;
    }

    bool operator==(const LocalTime& other) const {
        return secondsSinceMidnight == other.secondsSinceMidnight;
    }
};

namespace ClassroomManagementTest {
    struct Course {
        LocalTime startTime;
        LocalTime endTime;

        bool operator==(const Course& other) const {
            return startTime == other.startTime && endTime == other.endTime;
        }
    };
}

class Classroom {
private:
    int id;
    std::vector<ClassroomManagementTest::Course> courses;

public:
    Classroom(int id) : id(id) {}

    void addCourse(const ClassroomManagementTest::Course& course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void removeCourse(const ClassroomManagementTest::Course& course) {
        auto it = std::find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool isFreeAt(const std::string& checkTime) {
        LocalTime time = LocalTime::parse(checkTime);
        for (const auto& course : courses) {
            if (!time.isBefore(course.startTime) && !time.isAfter(course.endTime)) {
                return false;
            }
        }
        return true;
    }

    bool checkCourseConflict(const ClassroomManagementTest::Course& newCourse) {
        LocalTime newStartTime = newCourse.startTime;
        LocalTime newEndTime = newCourse.endTime;

        for (const auto& course : courses) {
            if (!(newEndTime.isBefore(course.startTime) || newStartTime.isAfter(course.endTime))) {
                return false;
            }
        }
        return true;
    }
};

#endif