#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

struct Course {
    int startMinutes;  // minutes from midnight
    int endMinutes;
};

class Classroom {
private:
    int id;
    std::vector<Course*> courses;

    static int parseTimeToMinutes(const std::string& timeStr) {
        int hours, minutes;
        char colon;
        std::istringstream iss(timeStr);
        iss >> hours >> colon >> minutes;
        return hours * 60 + minutes;
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

    bool isFreeAt(const std::string& checkTime) const {
        int time = parseTimeToMinutes(checkTime);
        for (const auto* course : courses) {
            if (!(time < course->startMinutes) && !(time > course->endMinutes)) {
                return false;
            }
        }
        return true;
    }

    bool checkCourseConflict(const Course* newCourse) const {
        int newStart = newCourse->startMinutes;
        int newEnd = newCourse->endMinutes;
        for (const auto* course : courses) {
            if (!(newEnd < course->startMinutes || newStart > course->endMinutes)) {
                return false;
            }
        }
        return true;
    }
};