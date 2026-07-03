#include <string>
#include <vector>
#include <algorithm>

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
public:
    int id;
    std::vector<Course> courses;

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
        int check_time = parse_time(check_time_str);

        for (const auto& course : courses) {
            int start_time = parse_time(course.start_time);
            int end_time = parse_time(course.end_time);
            if (start_time <= check_time && check_time <= end_time) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(const Course& new_course) {
        int new_start_time = parse_time(new_course.start_time);
        int new_end_time = parse_time(new_course.end_time);

        bool flag = true;
        for (const auto& course : courses) {
            int start_time = parse_time(course.start_time);
            int end_time = parse_time(course.end_time);
            if (start_time <= new_start_time && end_time >= new_start_time) {
                flag = false;
            }
            if (start_time <= new_end_time && end_time >= new_end_time) {
                flag = false;
            }
        }
        return flag;
    }

private:
    int parse_time(const std::string& time_str) {
        size_t colon_pos = time_str.find(':');
        int hour = std::stoi(time_str.substr(0, colon_pos));
        int minute = std::stoi(time_str.substr(colon_pos + 1));
        return hour * 60 + minute;
    }
};