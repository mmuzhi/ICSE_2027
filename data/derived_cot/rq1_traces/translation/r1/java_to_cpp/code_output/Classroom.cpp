#include <vector>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <algorithm>

struct Course {
    std::string startTime;
    std::string endTime;
};

class Classroom {
private:
    int id;
    std::vector<Course*> courses;

    int parseTimeToSeconds(const std::string& timeStr) const {
        int hours = 0;
        int minutes = 0;
        int seconds = 0;
        int count = std::sscanf(timeStr.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
        if (count == 2) {
            if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
                throw std::invalid_argument("Invalid time: hours or minutes out of range");
            }
            return hours * 3600 + minutes * 60;
        } else if (count == 3) {
            if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59) {
                throw std::invalid_argument("Invalid time: hours, minutes, or seconds out of range");
            }
            return hours * 3600 + minutes * 60 + seconds;
        } else {
            throw std::invalid_argument("Invalid time format: " + timeStr);
        }
    }

public:
    Classroom(int id) : id(id) {}

    void addCourse(Course* course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void removeCourse(Course* course) {
        auto it = std::find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool isFreeAt(const std::string& checkTime) {
        int checkSeconds = parseTimeToSeconds(checkTime);
        for (Course* course : courses) {
            int startSec = parseTimeToSeconds(course->startTime);
            int endSec = parseTimeToSeconds(course->endTime);
            if (checkSeconds >= startSec && checkSeconds <= endSec) {
                return false;
            }
        }
        return true;
    }

    bool checkCourseConflict(Course* newCourse) {
        int newStart = parseTimeToSeconds(newCourse->startTime);
        int newEnd = parseTimeToSeconds(newCourse->endTime);
        for (Course* course : courses) {
            int startSec = parseTimeToSeconds(course->startTime);
            int endSec = parseTimeToSeconds(course->endTime);
            if (newEnd >= startSec && newStart <= endSec) {
                return false;
            }
        }
        return true;
    }
};