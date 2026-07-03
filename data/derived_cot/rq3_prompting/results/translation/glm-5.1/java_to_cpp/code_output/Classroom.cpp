#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

namespace ClassroomManagementTest {
    struct LocalTime {
        int hour = 0;
        int minute = 0;
        int second = 0;

        static LocalTime parse(const std::string& s) {
            LocalTime t;
            char colon;
            std::istringstream iss(s);
            iss >> t.hour >> colon >> t.minute;
            if (iss >> colon >> t.second) {
                // seconds parsed successfully
            } else {
                t.second = 0;
                iss.clear();
            }
            return t;
        }

        bool isBefore(const LocalTime& other) const {
            if (hour != other.hour) return hour < other.hour;
            if (minute != other.minute) return minute < other.minute;
            return second < other.second;
        }

        bool isAfter(const LocalTime& other) const {
            if (hour != other.hour) return hour > other.hour;
            if (minute != other.minute) return minute > other.minute;
            return second > other.second;
        }
    };

    struct Course {
        LocalTime startTime;
        LocalTime endTime;

        bool operator==(const Course& other) const {
            return !startTime.isBefore(other.startTime) && !startTime.isAfter(other.startTime) &&
                   !endTime.isBefore(other.endTime) && !endTime.isAfter(other.endTime);
        }
    };
}

class Classroom {
private:
    int id;
    std::vector<ClassroomManagementTest::Course> courses;

public:
    Classroom(int id) : id(id) {}

    void addCourse(ClassroomManagementTest::Course course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void removeCourse(ClassroomManagementTest::Course course) {
        courses.erase(std::remove(courses.begin(), courses.end(), course), courses.end());
    }

    bool isFreeAt(const std::string& checkTime) {
        ClassroomManagementTest::LocalTime time = ClassroomManagementTest::LocalTime::parse(checkTime);
        for (const auto& course : courses) {
            if (!time.isBefore(course.startTime) && !time.isAfter(course.endTime)) {
                return false;
            }
        }
        return true;
    }

    bool checkCourseConflict(ClassroomManagementTest::Course newCourse) {
        ClassroomManagementTest::LocalTime newStartTime = newCourse.startTime;
        ClassroomManagementTest::LocalTime newEndTime = newCourse.endTime;

        for (const auto& course : courses) {
            if (!(newEndTime.isBefore(course.startTime) || newStartTime.isAfter(course.endTime))) {
                return false;
            }
        }
        return true;
    }
};