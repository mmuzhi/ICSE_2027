#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

class Classroom {
public:
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

    explicit Classroom(int id) : id(id) {}

    void add_course(const Course& course) {
        // Add only if not already present (like Python 'in' list equality)
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

    bool is_free_at(const std::string& check_time) const {
        int check_minutes = time_to_minutes(check_time);
        for (const auto& course : courses) {
            int start = time_to_minutes(course.start_time);
            int end = time_to_minutes(course.end_time);
            if (start <= check_minutes && check_minutes <= end) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(const Course& new_course) const {
        int new_start = time_to_minutes(new_course.start_time);
        int new_end = time_to_minutes(new_course.end_time);
        bool flag = true;
        for (const auto& course : courses) {
            int start = time_to_minutes(course.start_time);
            int end = time_to_minutes(course.end_time);
            if ((start <= new_start && end >= new_start) ||
                (start <= new_end && end >= new_end)) {
                flag = false;
                break;  // early exit, consistent with behavior
            }
        }
        return flag;
    }

private:
    int id;
    std::vector<Course> courses;

    // Convert time string "HH:MM" to total minutes from midnight
    static int time_to_minutes(const std::string& time_str) {
        int hour = std::stoi(time_str.substr(0, 2));
        int minute = std::stoi(time_str.substr(3, 2));
        return hour * 60 + minute;
    }
};