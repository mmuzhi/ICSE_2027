#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Time {
    int hours;
    int minutes;

    Time() : hours(0), minutes(0) {}
    Time(int h, int m) : hours(h), minutes(m) {}

    Time(const std::string& time_str) {
        char colon;
        int hours, minutes;
        std::istringstream iss(time_str);
        iss >> hours >> colon >> minutes;
        this->hours = hours;
        this->minutes = minutes;
    }

    bool operator<=(const Time& other) const {
        if (hours < other.hours) return true;
        if (hours == other.hours && minutes <= other.minutes) return true;
        return false;
    }

    bool operator>=(const Time& other) const {
        if (hours > other.hours) return true;
        if (hours == other.hours && minutes >= other.minutes) return true;
        return false;
    }

    bool operator==(const Time& other) const {
        return hours == other.hours && minutes == other.minutes;
    }
};

struct Course {
    std::string name;
    Time start_time;
    Time end_time;
};

class Classroom {
private:
    int id;
    std::vector<Course> courses;

public:
    Classroom(int id) : id(id) {}

    void add_course(const Course& course) {
        auto it = std::find_if(courses.begin(), courses.end(), [&course](const Course& c) {
            return c == course;
        });
        if (it == courses.end()) {
            courses.push_back(course);
        }
    }

    void remove_course(const Course& course) {
        auto it = std::find_if(courses.begin(), courses.end(), [&course](const Course& c) {
            return c == course;
        });
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool is_free_at(const Time& check_time) {
        for (const auto& course : courses) {
            if (course.start_time <= check_time && check_time <= course.end_time) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(const Course& new_course) {
        Time new_start = new_course.start_time;
        Time new_end = new_course.end_time;

        for (const auto& course : courses) {
            if ((course.start_time <= new_start && course.end_time >= new_start) ||
                (course.start_time <= new_end && course.end_time >= new_end)) {
                return false;
            }
        }
        return true;
    }
};