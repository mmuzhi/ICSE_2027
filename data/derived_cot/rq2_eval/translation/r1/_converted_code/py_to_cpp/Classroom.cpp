#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

struct Course {
    std::string name;
    std::string start_time;
    std::string end_time;

    bool operator==(const Course& other) const {
        return name == other.name && 
               start_time == other.start_time && 
               end_time == other.end_time;
    }
};

class Classroom {
private:
    int id;
    std::vector<Course> courses;

    int tm_to_time_t(const std::string& time_str) {
        std::istringstream ss(time_str);
        int hours, minutes;
        char colon;
        ss >> hours >> colon >> minutes;
        return hours * 60 + minutes;
    }

public:
    Classroom(int id) : id(id) {}

    void add_course(const Course& course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void remove_course(const Course& course) {
        auto it = std::find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    bool is_free_at(const std::string& check_time_str) {
        int check_time = tm_to_time_t(check_time_str);
        for (const Course& course : courses) {
            int start_time = tm_to_time_t(course.start_time);
            int end_time = tm_to_time_t(course.end_time);
            if (start_time <= check_time && check_time <= end_time) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(const Course& new_course) {
        int new_start_time = tm_to_time_t(new_course.start_time);
        int new_end_time = tm_to_time_t(new_course.end_time);
        for (const Course& course : courses) {
            int start_time = tm_to_time_t(course.start_time);
            int end_time = tm_to_time_t(course.end_time);
            if (start_time <= new_start_time && new_start_time <= end_time) {
                return false;
            }
            if (start_time <= new_end_time && new_end_time <= end_time) {
                return false;
            }
        }
        return true;
    }
};