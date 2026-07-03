#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cstdio>

class Classroom {
public:
    int id;
    std::vector<std::map<std::string, std::string>> courses;

    Classroom(int id) : id(id) {}

    void add_course(const std::map<std::string, std::string>& course) {
        if (std::find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
        }
    }

    void remove_course(const std::map<std::string, std::string>& course) {
        auto it = std::find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
        }
    }

    static int parse_time(const std::string& time_str) {
        int h, m;
        std::sscanf(time_str.c_str(), "%d:%d", &h, &m);
        return h * 60 + m;
    }

    bool is_free_at(const std::string& check_time) {
        int ct = parse_time(check_time);
        for (const auto& course : courses) {
            int start = parse_time(course.at("start_time"));
            int end = parse_time(course.at("end_time"));
            if (start <= ct && ct <= end) {
                return false;
            }
        }
        return true;
    }

    bool check_course_conflict(const std::map<std::string, std::string>& new_course) {
        int new_start = parse_time(new_course.at("start_time"));
        int new_end = parse_time(new_course.at("end_time"));

        bool flag = true;
        for (const auto& course : courses) {
            int start = parse_time(course.at("start_time"));
            int end = parse_time(course.at("end_time"));
            if (start <= new_start && end >= new_start) {
                flag = false;
            }
            if (start <= new_end && end >= new_end) {
                flag = false;
            }
        }
        return flag;
    }
};