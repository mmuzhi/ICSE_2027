#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

namespace ClassroomManagementTest {
    struct Course {
        std::string startTime;
        std::string endTime;
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
        courses.erase(std::remove(courses.begin(), courses.end(), course), courses.end());
    }

    bool isFreeAt(const std::string& checkTime) {
        auto currentTime = parseTime(checkTime);
        for (const auto& course : courses) {
            auto startTime = parseTime(course.startTime);
            auto endTime = parseTime(course.endTime);
            if (!(currentTime < startTime) && !(currentTime > endTime)) {
                return false;
            }
        }
        return true;
    }

    bool checkCourseConflict(const ClassroomManagementTest::Course& newCourse) {
        auto newStartTime = parseTime(newCourse.startTime);
        auto newEndTime = parseTime(newCourse.endTime);
        for (const auto& course : courses) {
            auto startTime = parseTime(course.startTime);
            auto endTime = parseTime(course.endTime);
            if (!(newEndTime < startTime) && !(newStartTime > endTime)) {
                return false;
            }
        }
        return true;
    }

private:
    static Time parseTime(const std::string& timeStr) {
        size_t pos = timeStr.find(':');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid time format");
        }
        int hours = std::stoi(timeStr.substr(0, pos));
        int minutes = std::stoi(timeStr.substr(pos + 1));
        return {hours, minutes};
    }
};

struct Time {
    int hours;
    int minutes;
};