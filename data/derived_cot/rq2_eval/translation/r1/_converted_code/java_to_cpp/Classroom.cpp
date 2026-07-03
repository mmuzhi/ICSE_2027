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

    int is_time_conflict(const std::string& timeStr) const {
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

    void add_course(Course* course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void remove_course(Course* course) {
        auto it = std::find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool is_free_at(const std::string& checkTime) {
        int checkSeconds = is_time_conflict(checkTime);
        for (Course* course : courses) {
            int startSec = is_time_conflict(course->startTime);
            int endSec = is_time_conflict(course->endTime);
            if (checkSeconds >= startSec && checkSeconds <= endSec) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(Course* newCourse) {
        int newStart = is_time_conflict(newCourse->startTime);
        int newEnd = is_time_conflict(newCourse->endTime);
        for (Course* course : courses) {
            int startSec = is_time_conflict(course->startTime);
            int endSec = is_time_conflict(course->endTime);
            if (newEnd >= startSec && newStart <= endSec) {
                return false;
            }
        }
        return true;
    }
};